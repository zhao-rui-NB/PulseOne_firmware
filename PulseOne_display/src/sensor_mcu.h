#ifndef _SENSOR_MCU_H_
#define _SENSOR_MCU_H_

#include <Arduino.h>


#define CMD_READ_TOUCH_STATUS 1
#define CMD_READ_BOTTLE_STATUS 2

#define CMD_READ_MAX30102_1 3
#define CMD_READ_MAX30102_1_FINGER_ON 4
#define CMD_MAX30102_1_STARTUP 5
#define CMD_MAX30102_1_SHUTDOWN 6

#define CMD_READ_MAX30102_2 7
#define CMD_READ_MAX30102_2_FINGER_ON 8
#define CMD_MAX30102_2_STARTUP 9
#define CMD_MAX30102_2_SHUTDOWN 10

#define CMD_VIBRATION 11
#define CMD_BOTTLE_LOCK 12
#define CMD_BOTTLE_UNLOCK 13

#define CMD_WS2812_SHOW1 14
#define CMD_WS2812_SHOW2 15
#define CMD_WS2812_SHOW3 16
#define CMD_WS2812_SHOW4 17

#define CMD_READ_INJECT_MODULE 18


// pin configuration
#define COMMAND_RX_PIN 15
#define COMMAND_TX_PIN 16
#define SENSOR_MCU_SERIAL Serial1


void sensor_mcu_init();
void sensor_mcu_clear_buffer();
void sensor_mcu_send(uint8_t cmd);

bool sensor_mcu_read_float_available();
bool sensor_mcu_read_float(float *data);

bool sensor_mcu_read_uint16_available();
bool sensor_mcu_read_uint16(uint16_t *data);

bool sensor_mcu_read_uint8_available();
bool sensor_mcu_read_uint8(uint8_t *data);



#endif // _SENSOR_MCU_H_