#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/ip4_addr.h"
#include "lwip/dns.h"

#include "json/jsmn.h"

#define WIFI_SSID "WiFI ID" // your wifi ID
#define WIFI_PASS "WIFI PASSWORD" // your wifi PASSWORD

#define HTTP_SERVER "httpbin.org"
#define HTTP_PORT 80
#define HTTP_REQUEST "GET /get HTTP/1.1\r\nHost: httpbin.org\r\nConnection: close\r\n\r\n"

#define MAX_JSON_TOKENS 64
#define MAX_RESPONSE_LEN 1024

static char http_response_buf[MAX_RESPONSE_LEN];
static int http_response_len = 0;

static err_t on_connected(void *arg, struct tcp_pcb *tpcb, err_t err);
static err_t on_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void dns_found_cb(const char *name, const ip_addr_t *ipaddr, void *arg);

void connect_to_http_server(const ip_addr_t *ipaddr) {
    struct tcp_pcb *pcb = tcp_new();
    tcp_connect(pcb, ipaddr, HTTP_PORT, on_connected);
    tcp_recv(pcb, on_recv);
}

// helper to compare JSON key string
int jsmn_eq(const char *json, jsmntok_t *tok, const char *s) {
    return (tok->type == JSMN_STRING &&
            (int)strlen(s) == tok->end - tok->start &&
            strncmp(json + tok->start, s, tok->end - tok->start) == 0);
}

static void parse_json_response(const char *json, int len) {
    jsmn_parser parser;
    jsmntok_t tokens[MAX_JSON_TOKENS];

    jsmn_init(&parser);
    int token_count = jsmn_parse(&parser, json, len, tokens, MAX_JSON_TOKENS);

    if (token_count < 0) {
        printf("Failed to parse JSON: %d\n", token_count);
        return;
    }

    for (int i = 0; i < token_count - 1; i++) {
        if (tokens[i].type == JSMN_STRING &&
            jsmn_eq(json, &tokens[i], "origin")) {
            int start = tokens[i + 1].start;
            int end = tokens[i + 1].end;
            printf("Your IP (from JSON): %.*s\n", end - start, json + start);
            break;
        }
    }
}

static err_t on_connected(void *arg, struct tcp_pcb *tpcb, err_t err) {
    if (err != ERR_OK) {
        printf("Connection error: %d\n", err);
        return err;
    }

    printf("Connected to server, sending HTTP GET request...\n");
    tcp_write(tpcb, HTTP_REQUEST, strlen(HTTP_REQUEST), TCP_WRITE_FLAG_COPY);
    return ERR_OK;
}

static err_t on_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (!p) { // this mean p == NULL 서버가 연결을 닫았다는 뜻
        printf("Connection closed by server.\n");

        http_response_buf[http_response_len] = '\0';
        printf("Full HTTP response:\n%s\n", http_response_buf);

        // Find start of JSON body
        const char *json_start = strstr(http_response_buf, "\r\n\r\n");
        if (json_start) {
            json_start += 4;  // skip past \r\n\r\n
            parse_json_response(json_start, strlen(json_start));
        }

        tcp_close(tpcb);
        return ERR_OK;
    }

    if (http_response_len + p->len < MAX_RESPONSE_LEN) {
        memcpy(http_response_buf + http_response_len, p->payload, p->len);
        http_response_len += p->len;
    }

    pbuf_free(p);
    return ERR_OK;
}

static void dns_found_cb(const char *name, const ip_addr_t *ipaddr, void *arg) {
    if (ipaddr) {
        printf("Resolved %s to: %s\n", name, ipaddr_ntoa(ipaddr));
        connect_to_http_server(ipaddr);
    } else {
        printf("DNS resolution failed.\n");
    }
}

int main() {
    stdio_init_all();
    sleep_ms(3000); // wait for USB serial connection

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 10000)) {
        printf("Failed to connect to Wi-Fi\n");
        return 1;
    }

    printf("Connected to Wi-Fi.\n");
    struct netif *netif = &cyw43_state.netif[CYW43_ITF_STA];
    printf("IP address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif)));

    // DNS lookup and connect
    ip_addr_t ipaddr;
    err_t err = dns_gethostbyname(HTTP_SERVER, &ipaddr, dns_found_cb, NULL);
    if (err == ERR_OK) {
        connect_to_http_server(&ipaddr);
    } else if (err != ERR_INPROGRESS) {
        printf("DNS error: %d\n", err);
    }

    while (true) {
        cyw43_arch_poll();
        sleep_ms(10);
    }

    return 0;
}