# 🏎️ 초음파센서를 이용한 장애물 회피 자율주행 RC CAR


## 시연영상
유튜브 링크 : https://youtu.be/q8EeekVraoU
![RC_CAR_Readme용](https://github.com/user-attachments/assets/23df698f-1f17-4005-b41a-89681b96f771)


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
<img width="400" alt="image" src="https://github.com/user-attachments/assets/c2674417-928c-4db5-8255-1341174fc670" />
<img width="400" alt="image" src="https://github.com/user-attachments/assets/57944843-db22-465c-af2c-c3ba5d16d44e" />

## 동작방식
### 수동 주행
<img width="600" alt="image" src="https://github.com/user-attachments/assets/e8eb32df-34fa-43cb-9fa9-98d408faae25" />


### 자율 주행
<img width="600" alt="자율주행" src="https://github.com/user-attachments/assets/0fd30a98-01f2-4ce7-8ba1-3b95ebd4c1a5" />


## Flow Chart
<img width="1000" alt="image" src="https://github.com/user-attachments/assets/8f541300-db77-436e-a6fa-abdc5dd7790a" />





