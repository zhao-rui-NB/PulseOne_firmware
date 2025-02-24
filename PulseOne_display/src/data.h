#ifndef _DATA_H_
#define _DATA_H_

#include <Arduino.h>
#include <lvgl.h>

#define MAX_USER 8
#define PROFILE_PHOTO_WIDTH 40
#define PROFILE_PHOTO_HEIGHT 40

class UserData{
    public:
        bool available = false;
        char name[20] = {0};
        uint8_t image_id = 0;
                
        float heart_rate = 0;
        float spo2 = 0;
        float blood_glucose = 0;
        float blood_pressure_sys = 0;
        float blood_pressure_dia = 0;
};

extern UserData user_datas[MAX_USER];
extern bool user_datas_has_new_data;
extern uint8_t login_user_id;

extern float inject_carbs;
extern float inject_insulin;


void user_datas_init();

#endif // _DATA_H_