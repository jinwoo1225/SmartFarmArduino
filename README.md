# SmartFarmArduino
아두이노로 저렴한 가격의 스마트팜을 만드는 것이 목적인 프로젝트입니다. 
## 회로도
![회로도 진짜](https://user-images.githubusercontent.com/3052898/119228054-14743200-bb4c-11eb-8995-77a646097dea.PNG)
![회로도 개념](https://user-images.githubusercontent.com/3052898/119256549-20b7c800-bbfc-11eb-8ba7-67e8362fa624.png)


### 실행 방법
1. Firmware폴더의 Firware.ino를 아두이노 IDE에서 연뒤, 컴파일해서 아두이노에 업로드한다. 
2. USB로 연결한다면 9600 baud를 사용해서 접속
3. Bluetooth로 연결한다면 HC05를 찾아서 비밀번호 1234입력


### 특징
- 블루투스로 현재 관개중인 작물의 상태를 파악
- LCD모듈이 연결되어있다면 LCD로도 출력

### 결과
- 거치되어서 24시간동안 빛을 주었음

![결과](https://user-images.githubusercontent.com/3052898/119228391-c3653d80-bb4d-11eb-895b-8d1b709e3075.png)

- 토양습도가 일정 이하이면 펌프로 물을 공급

![펌프](https://media.giphy.com/media/9LgPYr5UGtgXKHFTlP/giphy.gif)


- ( 24시간 빛을 주거나 vs 20시간 동안 ) or ( 토양을 항습하게 유지 vs 사람이 직접 정해진 시간에 물을 줌)

![그림1](https://user-images.githubusercontent.com/3052898/119256639-9328a800-bbfc-11eb-9178-02cb62328486.png)

### 개선사항
- 라즈베리파이를 통해서 데이터 수집 및 작동 제어
