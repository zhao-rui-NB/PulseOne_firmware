#include "PulseOximeter.h"


PulseOximeter::PulseOximeter(TwoWire *i2c){
    this->i2c = i2c;
    this->spo2 = 0;
    this->spo2_valid = 0;
    this->heart_rate = 0;
    this->heart_rate_valid = 0;
}


void PulseOximeter::begin(){
    Serial.println("PulseOximeter begin");    

    uint8_t res =  maxim_max30102_init(this->i2c);
    if(res){
        Serial.println("MAX30102 init success");
    }
    else{
        Serial.println("MAX30102 init failed");
    }
}



void PulseOximeter::read(){

    uint32_t start_time = millis();
    for(int i=0; i<BUFFER_SIZE; i++){
        uint8_t int_status1;
        do{
            maxim_max30102_read_reg(this->i2c,REG_INTR_STATUS_1, &int_status1);
            // Serial.println("Waiting for data...");
        }while(!(int_status1 & 0xC0)); // interrupt status 1, bit 6: A_FULL, bit 7: PPG_RDY

        maxim_max30102_read_fifo(this->i2c,&red_led_buffer[i], &ir_led_buffer[i]);
        // Serial.print("i=");Serial.print(i);Serial.print(" red=");Serial.print(red_led_buffer[i]);Serial.print(" ir=");Serial.println(ir_led_buffer[i]);
    }
    // Serial.print("Time taken to read data: ");Serial.println(millis()-start_time);

    // trush values
    float ratio, correl;
    rf_heart_rate_and_oxygen_saturation(ir_led_buffer, BUFFER_SIZE, red_led_buffer, &spo2, &spo2_valid, &heart_rate, &heart_rate_valid, &ratio, &correl);

}

float PulseOximeter::getSpO2(){
    return spo2;
}

int32_t PulseOximeter::getHeartRate(){
    return heart_rate;
}

void PulseOximeter::shutdown(){
    maxim_max30102_shut_down(this->i2c);
}

void PulseOximeter::startup(){
    maxim_max30102_startup(this->i2c);
}

bool PulseOximeter::check_finger_on(){

    uint32_t red_data = 0;
    uint32_t ir_data = 0;

    uint8_t int_status1;

    
    
    // clear the fifo first
    while(1){
        maxim_max30102_read_reg(this->i2c,REG_INTR_STATUS_1, &int_status1);
        if(!(int_status1 & 0xC0)){
            break;
        }
        maxim_max30102_read_fifo(this->i2c, &red_data, &ir_data);
    }

    
    // start read data
    do{
        maxim_max30102_read_reg(this->i2c,REG_INTR_STATUS_1, &int_status1);
        // Serial.println("Waiting for data...");
    }while(!(int_status1 & 0xC0)); // interrupt status 1, bit 6: A_FULL, bit 7: PPG_RDY


    maxim_max30102_read_fifo(this->i2c, &red_data, &ir_data);
    Serial.print("red=");Serial.print(red_data);Serial.print(" ir=");Serial.println(ir_data);

    // Serial.printf("return : %d\n", (red_data > 5000 && ir_data > 5000));
    return (red_data > 5000 && ir_data > 5000);
}
    
