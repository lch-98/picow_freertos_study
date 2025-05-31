## 📦 프로젝트 구조
| 프로젝트 폴더(src)      | 설명                            |
|-----------------|---------------------------------|
| freertos     | freertos 기본 활용 공부 |
| blink   | 내장 LED rtos 테스크 기반 제어     |
| wifi_connect | pico W 보드 Wifi 연결       |
| http_get   | pico W 보드 http 테스트 도메인에서 GET 요청 후 Json 데이터 파싱 |
| http_weather | pico W 보드 http로 기상청 API 받아오기, Json 데이터 파싱 및 NTP 동기화  |
| picow_lcd | SPI 설정 후 pico W 보드 LCD 연결 후 화면 출력 |

|프로젝트 폴더(lib)  | 설명                           |
|-----------------|---------------------------------|
| FreeRTOS-Kernel   | FreeRTOS 공식 커널  |
| pico-sdk   | 라즈베리파이 피코 공식 SDK   |

## 🚀 빌드 및 실행 방법
```bash
# 0. 프로젝트 폴더 생성 및 pico-sdk 환경 변수 설정
mkdir pico-freertos
export PICO_SDK_PATH=../../pico-sdk/

# 1. 프로젝트 폴더 안에 Git clone (깃 복사)
git clone https://github.com/lch-98/picow_freertos_study.git

# 2. 빌드 디렉토리 삭제 및 생성
cd pico-freertos
rm -rf build
mkdir build
cd build

# 3. CMake 빌드 설정 (경로는 빌드 폴더에 위치)
cmake -DPICO_BOARD=pico_w ..

# 4. 컴파일 (경로는 빌드 폴더에 위치)
make

# 5. 생성된 .uf2 파일을 Pico W에 복사
```
