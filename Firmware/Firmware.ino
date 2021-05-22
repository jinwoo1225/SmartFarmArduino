// Include Libraries
#include <Wire.h>

#include "Arduino.h"
#include "BTHC05.h"
#include "DHT.h"
#include "LiquidCrystal_I2C.h"
#include "Relay.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "SoilMoisture.h"

// Pin Definitions
#define BTHC05_PIN_TXD 11
#define BTHC05_PIN_RXD 10
#define DHT_PIN_DATA 2
#define RELAY_PIN 3
#define SOILMOISTURE_5V1_1_PIN_SIG A0
#define SOILMOISTURE_5V2_2_PIN_SIG A1

// Global variables and defines

// object initialization
BTHC05 bthc05(BTHC05_PIN_RXD, BTHC05_PIN_TXD);
DHT dht(DHT_PIN_DATA);

// define vars for testing menu
const int timeout = 10000;  // define timeout of 10 sec
char menuOption = 0;
long time0 = 0;

// Setup the essentials for your circuit to work. It runs first every time your
// circuit is powered with electricity.
void setup() {
    Serial.begin(9600);
    bthc05.begin(9600);
    bthc05.println("Bluetooth On....");
    dht.begin();
    lcd.init();       // LCD 초기화
    lcd.backlight();  // 백라이트 켜기

    pinMode(RELAY_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
    // A0번에 토양수분센서 1번 장착
    int soil1 = analogRead(0);
    // A1번에 토양수분센서 2번 장착
    int soil2 = analogRead(1);
    // DHT22 습도와 온도 받아옴
    float dhtHumidity = dht.readHumidity();
    float dhtTempC = dht.readTempC();
    //시리얼과 블루투스에 값 출력
    printSerialBluetooth(soil1, soil2, dhtHumidity, dhtTempC);
    // LCD장치가 있다면 출력
    printLCD(soil1, soil2, dhtHumidity, dhtTempC);
    //만약 10분이 됬다면?
    if (time0 > 30) {
        //토양수분센서의 값이 500을 초과한다면?(건조하다면)
        if (soil1 > 500) {
            Serial.print("물펌프 작동");
            digitalWrite(RELAY_PIN, LOW);
            delay(2000);
            digitalWrite(RELAY_PIN, HIGH);
        }
        time0 = 0;
    }

    // 5초마다 새로고침 하는 코드
    delay(5000);
    time0 += 5;
}

void printLCD(int soil1, int soil2, float dhtHumidity, float dhtTemp) {
    lcd.setCursor(0, 0);  // 1번째, 1라인
    lcd.print("H :");
    lcd.print(int(dhtHumidity));
    lcd.print("%");
    lcd.setCursor(7, 0);
    lcd.print("T :");
    lcd.print(int(dhtTemp));
    lcd.print("C");

    lcd.setCursor(0, 1);  // 1번째, 2라인
    lcd.print("S1:");
    lcd.print(soil1);
    lcd.setCursor(7, 1);
    lcd.print("S2:");
    lcd.print(soil2);
}

void printSerialBluetooth(int soil1, int soil2, float dhtHumidity,
                          float dhtTemp) {
    Serial.print("current time : ");
    Serial.println(time0);
    Serial.print("Soil 1 : ");
    Serial.println(soil1);
    Serial.print("Soil 2 : ");
    Serial.println(soil2);

    Serial.print(F("Humidity : "));
    Serial.println(dhtHumidity);
    Serial.print(F("Temp     : "));
    Serial.println(dhtTemp);

    bthc05.print("Soil 1 : ");
    bthc05.println(soil1);
    bthc05.print("Soil 2 : ");
    bthc05.println(soil2);

    bthc05.print(F("Humidity : "));
    bthc05.println(dhtHumidity);
    bthc05.print(F("Temp     : "));
    bthc05.println(dhtTemp);
}
