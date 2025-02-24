#include <unity.h>

#include <Arduino.h>

#include <lvgl.h>
#include <TFT_eSPI.h>

#include <examples/lv_examples.h>
#include <demos/lv_demos.h>


#include <CST816S.h>

#include "ui/ui.h"
#include "ui/screens.h"
#include "event.h"


#include <HardwareSerial.h>

// screen
#define TFT_HOR_RES   240
#define TFT_VER_RES   240
#define TFT_ROTATION  LV_DISPLAY_ROTATION_0

// UI buffer
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq

/*Read the touchpad*/
void my_touchpad_read( lv_indev_t * indev, lv_indev_data_t * data ){

    if(touch.available()){
        data->point.x = touch.data.x;
        data->point.y = touch.data.y;
        data->state = LV_INDEV_STATE_PRESSED;
        Serial.printf("touch x=%d, y=%d\n", data->point.x, data->point.y);
    }
    else{
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void){
    return millis();
}



void setup(){
    ble_init();
    ble_update_page("main page");

    touch.begin();

    String LVGL_ver = String("LVGL V") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    Serial.println( LVGL_ver );

    Serial.begin( 115200 );
    sensor_mcu_init();

    lv_init();

    lv_tick_set_cb(my_tick);

    lv_display_t * disp;
    disp = lv_tft_espi_create(TFT_HOR_RES, TFT_VER_RES, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, TFT_ROTATION);

    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); /*Touchpad should have POINTER type*/
    lv_indev_set_read_cb(indev, my_touchpad_read);



    ui_init();
    add_all_event();

    user_datas_init();

    system_state_timer_init();

    
}

void loop(){
    lv_timer_handler(); /* let the GUI do its work */
    delay(5); /* let this time pass */
    // print the free ram 
    Serial.printf("free ram: %d\n", ESP.getFreeHeap());
}


