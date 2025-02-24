#include "sensor_mcu.h"



void sensor_mcu_init(){
    SENSOR_MCU_SERIAL.begin(115200, SERIAL_8N1, COMMAND_RX_PIN, COMMAND_TX_PIN);
}

void sensor_mcu_clear_buffer(){
    while(SENSOR_MCU_SERIAL.available()){
        SENSOR_MCU_SERIAL.read();
    }
}


void sensor_mcu_send(uint8_t cmd){
    SENSOR_MCU_SERIAL.write(cmd);
}    


bool sensor_mcu_read_float_available(){
    return SENSOR_MCU_SERIAL.available() >= sizeof(float);
}

bool sensor_mcu_read_float(float *data){
    // 5 second timeout, return false if no data is available
    uint32_t start = millis();
    while(SENSOR_MCU_SERIAL.available() < sizeof(float)){

        if(millis() - start > 5000){
            return false;
        } 
        delay(1);
    }
    SENSOR_MCU_SERIAL.readBytes((char *)data, sizeof(float));
    return true;
}

bool sensor_mcu_read_uint16_available(){
    return SENSOR_MCU_SERIAL.available() >= sizeof(uint16_t);
}

bool sensor_mcu_read_uint16(uint16_t *data){
    // 5 second timeout, return false if no data is available
    uint32_t start = millis();
    while(SENSOR_MCU_SERIAL.available() < sizeof(uint16_t)){
        if(millis() - start > 5000){
            return false;
        } 
        delay(1);
    }
    SENSOR_MCU_SERIAL.readBytes((char *)data, sizeof(uint16_t));
    return true;
}

bool sensor_mcu_read_uint8_available(){
    return SENSOR_MCU_SERIAL.available() >= sizeof(uint8_t);
}

bool sensor_mcu_read_uint8(uint8_t *data){
    // 5 second timeout, return false if no data is available
    uint32_t start = millis();
    while(SENSOR_MCU_SERIAL.available() < sizeof(uint8_t)){
        if(millis() - start > 5000){
            return false;
        } 
        delay(1);
    }
    SENSOR_MCU_SERIAL.readBytes((char *)data, sizeof(uint8_t));
    return true;
}



