#include <Arduino.h>
#include <Wire.h>
#include <ESP32Servo.h>

#include "Adafruit_NeoPixel.h"
#include "pin_config.h"
#include "PulseOximeter.h"
#include "command.h"

PulseOximeter pox1(&Wire);
PulseOximeter pox2(&Wire1);
Servo servo;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(8, WS2812_PIN, NEO_GRB + NEO_KHZ800);  

void setup() {
    Serial.begin(115200); // usb serial
    Serial1.begin(115200, SERIAL_8N1, COMMAND_UART_RX_PIN, COMMAND_UART_TX_PIN);  // command uart


    Wire.begin(MAX30102_1_SDA_PIN,MAX30102_1_SCL_PIN);
    Wire1.begin(MAX30102_2_SDA_PIN,MAX30102_2_SCL_PIN);

    // load active low
    digitalWrite(VIBRATION_MOTOR_PIN, HIGH);
    pinMode(VIBRATION_MOTOR_PIN, OUTPUT);

    digitalWrite(SERVO_ON_PIN, HIGH);
    pinMode(SERVO_ON_PIN, OUTPUT);

    pinMode(BOTTLE_DETECT_PIN, INPUT_PULLUP);
    pinMode(INJECT_MODULE_PIN, INPUT_PULLUP);

    servo.setPeriodHertz(50);    // standard 50 hz servo
    servo.attach(SERVO_PWM_PIN, 500, 2400);

    pox1.begin();
    pox2.begin();
    pox1.shutdown();
    pox2.shutdown();

}


void cmd_read_max30102_1(){
    Serial.printf("cmd_read_max30102_1");
    pox1.read(); // 4000ms
    // write a float byte
    float heartRate = pox1.getHeartRate();
    float spO2 = pox1.getSpO2();
    
    Serial.printf("\theartRate: %f, spO2: %f\n", heartRate, spO2);
    
    // ///#################################### test data
    // heartRate = 187.6;
    // spO2 = 69.6;

    uint8_t buf[8];
    memcpy(buf, &heartRate, 4);
    memcpy(buf+4, &spO2, 4);
    Serial1.write(buf, 8);
}

void cmd_read_max30102_2(){
    Serial.printf("cmd_read_max30102_2");
    pox2.read(); // 4000ms
    // write a float byte
    int32_t heartRate = pox2.getHeartRate();
    float spO2 = pox2.getSpO2();
    
    Serial.printf("\theartRate: %d, spO2: %f\n", heartRate, spO2);

    // ///#################################### test data
    // heartRate = 187.6;
    // spO2 = 69.6;

    uint8_t buf[8];
    memcpy(buf, &heartRate, 4);
    memcpy(buf+4, &spO2, 4);
    Serial1.write(buf, 8);


}

void loop() {

    if(Serial1.available()){
        uint8_t cmd = 0;
        cmd = Serial1.read();
        // print the command 
        Serial.printf("cmd: %d\n", cmd);

        touch_value_t t_value;
        switch(cmd){

            case CMD_READ_TOUCH_STATUS:
                t_value = touchRead(TOUCH_PIN);
                Serial.printf("touch value: %d\n", t_value);
                Serial1.write(0x01 ? t_value<30 : 0x00); 
                break;

            case CMD_READ_BOTTLE_STATUS:
                Serial1.write(!digitalRead(BOTTLE_DETECT_PIN));
                break;
            
            case CMD_READ_INJECT_MODULE:
                Serial1.write(!digitalRead(INJECT_MODULE_PIN));
                break;

            case CMD_MAX30102_1_STARTUP: pox1.startup(); Serial.printf("start pox1.startup()"); break;
            case CMD_MAX30102_1_SHUTDOWN:pox1.shutdown();break;
            case CMD_READ_MAX30102_1: cmd_read_max30102_1(); break;
            case CMD_READ_MAX30102_1_FINGER_ON:
                Serial1.write(pox1.check_finger_on());
                break;
            
            case CMD_MAX30102_2_STARTUP: pox2.startup(); break;
            case CMD_MAX30102_2_SHUTDOWN:pox2.shutdown();break;
            case CMD_READ_MAX30102_2: cmd_read_max30102_2(); break;
            case CMD_READ_MAX30102_2_FINGER_ON:
                Serial1.write(pox2.check_finger_on());
                break;

            case CMD_VIBRATION:
                digitalWrite(VIBRATION_MOTOR_PIN, LOW);
                delay(2000);
                digitalWrite(VIBRATION_MOTOR_PIN, HIGH);
                break;

            case CMD_BOTTLE_LOCK:
                digitalWrite(SERVO_ON_PIN, LOW);
                servo.write(120); 
                delay(1000);
                digitalWrite(SERVO_ON_PIN, HIGH);
                break;

            case CMD_BOTTLE_UNLOCK:
                digitalWrite(SERVO_ON_PIN, LOW);
                servo.write(60); 
                delay(1000);
                digitalWrite(SERVO_ON_PIN, HIGH);
                break;

            case CMD_WS2812_SHOW1: pixels.fill(pixels.Color(0, 0, 0)); pixels.show(); break;
            case CMD_WS2812_SHOW2: pixels.fill(pixels.Color(100, 0, 0)); pixels.show(); break;
            case CMD_WS2812_SHOW3: pixels.fill(pixels.Color(0, 100, 0)); pixels.show(); break;
            case CMD_WS2812_SHOW4: pixels.fill(pixels.Color(0, 0, 100)); pixels.show(); break;

            default:
                Serial.printf("Unknown command: %d\n", cmd);
        }
    }

}
