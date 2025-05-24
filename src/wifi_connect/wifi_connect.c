#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/netif.h"

int main() {
    stdio_init_all();
    sleep_ms(10000); // USB serial 초기화 시간
    
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }
    // CYW43 칩은 STA, AP, OFF가 존재
    // if you want to use AP Mode -> cyw43_arch_enable_ap_mode();
    cyw43_arch_enable_sta_mode();  // CYW43 Wi-Fi Client mode Activate
    
    const char *ssid = "WIFI ID";             // 정확히 확인
    const char *pass = "WIFI PASSWORD";         // 비번을 단순화해서 테스트

    printf("Connecting to Wi-Fi...\n");

    int result = cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, 15000);
    if (result) {
        printf("Failed to connect. Error: %d\n", result);
        printf("Wi-Fi link status: %d\n", cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA));
    } else {
        printf("Connected!\n");
        struct netif *netif = &cyw43_state.netif[CYW43_ITF_STA];
        printf("IP address: %s\n", ip4addr_ntoa(netif_ip4_addr(netif)));
    }

    while (true) {
        sleep_ms(1000);
    }

    return 0;
}