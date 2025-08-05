# 🏎️ 초음파센서를 이용한 장애물 회피 자율주행 RC CAR

## 개요
초음파를 활용하여 전방, 좌우측 30도 가량의 장애물을 탐지하여 회피하는 자율주행 차량 제작

개발기간 : 25. 05. 09 ~ 25. 05. 21

## 프로젝트 핵심 기능
장애물을 초음파로 탐지, 거리측정하여 회피하는 자율주행 차량 제작
FreeRTOS 기반 모듈간 독립적 제어 및 실시간 반응 구현
UART 통신 및 PWM제어를 통한 원격 명령 수신 및 모터 제어

## 하드웨어

### 보드 및 칩 
- STM32F411RE(ARM Cortex-M4)

### 송수신
- 블루투스 모듈(HC-06)

### 센서 및 모터
- 초음파 센서(HC-SR04), DC모터(PP-A438), 모터드라이버(L298N)


## USECASE
<img width="400" alt="image" src="https://github.com/user-attachments/assets/49aa881b-4454-47ba-8f65-8288ef0c8a58" />
<img width="400" alt="image" src="https://github.com/user-attachments/assets/ce7f3654-312f-4934-8982-a006a31f698c" />


## 
