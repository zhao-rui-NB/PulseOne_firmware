#include <Arduino.h>
#include "sensor_mcu.h"


void setup(){
    Serial.begin(115200);
    // print hello
    Serial.println("Hello, this is test_sensor_mcu.cpp");

    

    sensor_mcu_init();
    // while(1){
    //     SENSOR_MCU_SERIAL.printf("Hello, this is test_sensor_mcu.cpp command serial port\n");
    //     delay(300);
    // }
    // sensor_mcu_clear_buffer();
    // sensor_mcu_send(CMD_READ_TOUCH_STATUS);

} 

void loop(){
    uint8_t data;

    Serial.println("send CMD_READ_TOUCH_STATUS");
    sensor_mcu_send(CMD_READ_TOUCH_STATUS);

    if(sensor_mcu_read_uint8(&data)){
        Serial.println(data);
    } else {
        Serial.println("no data");
    }
    
    // delay(1000);


}