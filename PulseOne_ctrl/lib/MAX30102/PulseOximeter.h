#ifndef _PULSEOXIMETER_H_
#define _PULSEOXIMETER_H_


#include <Wire.h>  

#include "max30102.h"
#include "algorithm_by_RF.h"


class PulseOximeter{
    
    TwoWire *i2c;
    uint32_t ir_led_buffer[BUFFER_SIZE]; //infrared LED sensor data
    uint32_t red_led_buffer[BUFFER_SIZE];  //red LED sensor data

    float spo2;
    int8_t spo2_valid;

    int32_t heart_rate;
    int8_t heart_rate_valid;

    public:
        PulseOximeter(TwoWire *i2c);
        void begin();
        void read();

        float getSpO2();
        int32_t getHeartRate();

        void shutdown();
        void startup();

        bool check_finger_on();

};



#endif // _PULSEOXIMETER_H_
