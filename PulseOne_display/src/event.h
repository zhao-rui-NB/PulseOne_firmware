#ifndef __EVENT_H__
#define __EVENT_H__

#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>


#include "ui/ui.h"
#include "ui/screens.h"
#include "ui/images.h"
#include "sensor_mcu.h"
#include "data.h"
#include "ble.h"

extern objects_t objects;


// make sensor power on or off 
void sensor_power_control(bool on){
    static bool is_sensor_on = false;
    if(is_sensor_on == on){
        return;
    }

    if(on){
        sensor_mcu_send(CMD_MAX30102_1_STARTUP);
        sensor_mcu_send(CMD_MAX30102_2_STARTUP);
    }
    else{
        sensor_mcu_send(CMD_MAX30102_1_SHUTDOWN);
        sensor_mcu_send(CMD_MAX30102_2_SHUTDOWN);
    }
    is_sensor_on = on;
}

void auto_sensor_on_off(){
    // auto get page then if in the list of monitor page, then power on the sensor    
    // now page
    lv_obj_t *now_page = lv_scr_act();
    if(now_page == objects.page_monitor_prepare || now_page == objects.page_monitor_notice || now_page == objects.page_monitor_running){
        sensor_power_control(true);
    }
    else{
        sensor_power_control(false);
    }

}

void change_page_callback(lv_event_t * e) {
    lv_obj_t * page = (lv_obj_t *)lv_event_get_user_data(e);  // 使用這個而不是 lv_obj_get_user_data
    if(page == NULL) {
        Serial.println("page is NULL");
        return;
    }
    lv_screen_load(page);
}

void on_btn_inject_carbs_edit_ok_click(lv_event_t * e){
    char carbs_str[10];
    // get the roller value
    lv_roller_get_selected_str(objects.roller_carbs, carbs_str, sizeof(carbs_str));
    
    // update inject ready page, lb_inject_ready_carbs
    lv_label_set_text(objects.lb_inject_ready_carbs, carbs_str);

    inject_carbs = atof(carbs_str);
    Serial.printf("set inject carbs: %f\n", inject_carbs);

    lv_screen_load(objects.page_inject_ready);
}

void on_btn_inject_insulin_edit_ok_click(lv_event_t * e){
    char insulin_str[10];
    // get the roller value
    lv_roller_get_selected_str(objects.roller_insulin, insulin_str, sizeof(insulin_str));

    // update inject ready page, lb_inject_ready_insulin
    lv_label_set_text(objects.lb_inject_ready_insulin, insulin_str);

    inject_insulin = atof(insulin_str);
    Serial.printf("set inject insulin: %f\n", inject_insulin);

    lv_screen_load(objects.page_inject_ready);
}

void on_user_login(lv_event_t * e){
    // get the user id
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e);
    
    if(btn == objects.btn_user_0)login_user_id = 0;
    else if(btn == objects.btn_user_1)login_user_id = 1;
    else if(btn == objects.btn_user_2)login_user_id = 2;
    else if(btn == objects.btn_user_3)login_user_id = 3;
    else if(btn == objects.btn_user_4)login_user_id = 4;
    else if(btn == objects.btn_user_5)login_user_id = 5;
    else if(btn == objects.btn_user_6)login_user_id = 6;
    else if(btn == objects.btn_user_7)login_user_id = 7;
    else login_user_id = 0;
    
    Serial.printf("login user id: %d\n", login_user_id);
    lv_label_set_text(objects.lb_sel_user_name, user_datas[login_user_id].name);
    lv_screen_load(objects.page_user_home);

    // send to ble 
    ble_update_logined_user(user_datas[login_user_id].name);


}

void on_monitor_complete_tab_btn(lv_event_t * e){
    // get the user id
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e);
    
    
    lv_obj_remove_state(objects.btn_monitor_complete_glucose, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.btn_monitor_complete_pressure, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.btn_monitor_complete_spo2, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.btn_monitor_complete_heart_rate, LV_STATE_CHECKED);

    lv_obj_add_state(btn, LV_STATE_CHECKED);

    //btn_monitor_complete_glucose
    //btn_monitor_complete_pressure
    //btn_monitor_complete_spo2
    //btn_monitor_complete_heart_rate

    // set the tab page

    if(btn == objects.btn_monitor_complete_glucose){
        lv_tabview_set_active(objects.tabview_monitor_complete, 0, LV_ANIM_ON);
        // lb_monitor_complete_type
        lv_label_set_text(objects.lb_monitor_complete_type, "Glucose");
    }
    else if(btn == objects.btn_monitor_complete_pressure){
        lv_tabview_set_active(objects.tabview_monitor_complete, 1, LV_ANIM_ON);
        lv_label_set_text(objects.lb_monitor_complete_type, "Pressure");
    }
    else if(btn == objects.btn_monitor_complete_spo2){
        lv_tabview_set_active(objects.tabview_monitor_complete, 2, LV_ANIM_ON);
        lv_label_set_text(objects.lb_monitor_complete_type, "SpO2");
    }
    else if(btn == objects.btn_monitor_complete_heart_rate){
        lv_tabview_set_active(objects.tabview_monitor_complete, 3, LV_ANIM_ON);
        lv_label_set_text(objects.lb_monitor_complete_type, "Heart Rate");
    }

    //btn_monitor_complete_glucose
    //btn_monitor_complete_pressure
    //btn_monitor_complete_spo2
    //btn_monitor_complete_heart_rate
    // set all btn un checked

}
// update user login page (main)

void on_tabviwer_change(lv_event_t * e){
    lv_obj_t * tabview = (lv_obj_t *)lv_event_get_target(e);
    int tab_index = lv_tabview_get_tab_active(tabview);

    lv_obj_remove_state(objects.btn_monitor_complete_glucose, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.btn_monitor_complete_pressure, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.btn_monitor_complete_spo2, LV_STATE_CHECKED);
    lv_obj_remove_state(objects.btn_monitor_complete_heart_rate, LV_STATE_CHECKED);

    if(tab_index == 0){
        lv_label_set_text(objects.lb_monitor_complete_type, "Glucose");
        lv_obj_add_state(objects.btn_monitor_complete_glucose, LV_STATE_CHECKED);
    }
    else if(tab_index == 1){
        lv_label_set_text(objects.lb_monitor_complete_type, "Pressure");
        lv_obj_add_state(objects.btn_monitor_complete_pressure, LV_STATE_CHECKED);
    }
    else if(tab_index == 2){
        lv_label_set_text(objects.lb_monitor_complete_type, "SpO2");
        lv_obj_add_state(objects.btn_monitor_complete_spo2, LV_STATE_CHECKED);
    }
    else if(tab_index == 3){
        lv_label_set_text(objects.lb_monitor_complete_type, "Heart Rate");
        lv_obj_add_state(objects.btn_monitor_complete_heart_rate, LV_STATE_CHECKED);
    }



}    

void add_all_event(){
    // page_main (login user)
    lv_obj_add_event_cb(objects.btn_user_0, on_user_login, LV_EVENT_CLICKED, NULL); 
    lv_obj_add_event_cb(objects.btn_user_1, on_user_login, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_user_2, on_user_login, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_user_3, on_user_login, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_user_4, on_user_login, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_user_5, on_user_login, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_user_6, on_user_login, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_user_7, on_user_login, LV_EVENT_CLICKED, NULL);

    // page_user_home
    lv_obj_add_event_cb(objects.btn_user_home_back, change_page_callback, LV_EVENT_CLICKED, objects.main);
    lv_obj_add_event_cb(objects.btn_user_home_monitor, change_page_callback, LV_EVENT_CLICKED, objects.page_monitor_prepare);

    lv_obj_add_event_cb(objects.btn_user_home_inject, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_insert_vial);
    // page_inject_insert_vial
    lv_obj_add_event_cb(objects.btn_inject_insert_vial_back, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    // page_inject_ready
    lv_obj_add_event_cb(objects.btn_inject_back, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    lv_obj_add_event_cb(objects.btn_insulin, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_insulin);
    lv_obj_add_event_cb(objects.btn_carbs, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_carbs);
    lv_obj_add_event_cb(objects.btn_inject_run, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_prepare);
    // page_inject_carbs
    lv_obj_add_event_cb(objects.btn_inject_carbs_back, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_ready);
    // lv_obj_add_event_cb(objects.btn_inject_carbs_edit_ok, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_ready);
    lv_obj_add_event_cb(objects.btn_inject_carbs_edit_ok, on_btn_inject_carbs_edit_ok_click, LV_EVENT_CLICKED, objects.page_inject_ready);
    
    // page_inject_insulin
    lv_obj_add_event_cb(objects.btn_inject_insulin_back, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_ready);
    // lv_obj_add_event_cb(objects.btn_inject_insulin_edit_ok, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_ready);
    lv_obj_add_event_cb(objects.btn_inject_insulin_edit_ok, on_btn_inject_insulin_edit_ok_click, LV_EVENT_CLICKED, objects.page_inject_ready);
    
    // page_inject_prepare
    lv_obj_add_event_cb(objects.btn_inject_prepare_back, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_ready);
    lv_obj_add_event_cb(objects.btn_inject_prepare_ok, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_injecting);
    // page_inject_injecting
    lv_obj_add_event_cb(objects.btn_inject_ingecting_back, change_page_callback, LV_EVENT_CLICKED, objects.page_inject_complete); // just for test
    // page_inject_complete
    lv_obj_add_event_cb(objects.btn_inject_complete_ok, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);



    // page_monitor_prepare
    lv_obj_add_event_cb(objects.btn_monitor_prepare_back, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    // page_monitor_notice
    lv_obj_add_event_cb(objects.btn_monitor_notice_back, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    // page_monitor_complete
    lv_obj_add_event_cb(objects.btn_monitor_complete_back, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    lv_obj_add_event_cb(objects.tabview_monitor_complete, on_tabviwer_change, LV_EVENT_VALUE_CHANGED, NULL);



    // //page_inject_carbs
    // lv_obj_add_event_cb(objects.page_inject_carbs, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    // //page_inject_insulin
    // lv_obj_add_event_cb(objects.page_inject_insulin, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);

    // page_monitor_complete
    lv_obj_add_event_cb(objects.btn_monitor_complete_ok, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    lv_obj_add_event_cb(objects.btn_monitor_complete_glucose, on_monitor_complete_tab_btn, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_monitor_complete_pressure, on_monitor_complete_tab_btn, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_monitor_complete_spo2, on_monitor_complete_tab_btn, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.btn_monitor_complete_heart_rate, on_monitor_complete_tab_btn, LV_EVENT_CLICKED, NULL);
    // page_monitor_running
    // lv_obj_add_event_cb(objects.btn_monitor_running_back, change_page_callback, LV_EVENT_CLICKED, objects.page_user_home);
    
}

 

void system_state_update(lv_timer_t * timer){
    static uint32_t page_start_time = 0;
    static lv_obj_t *last_page = NULL;
    
    static uint8_t data_count = 0;
    static float heart_rate[3];
    static float spo2[3];
    static bool bottle_locked = false;

    //get now page
    lv_obj_t *now_page = lv_scr_act();
    bool is_new_page = (now_page != last_page);


    auto_sensor_on_off();

    // if page is different from last page, reset the page_start_time
    if (now_page != last_page){
        Serial.println("page change");
        page_start_time = millis();

        if(now_page == objects.main) ble_update_page("login");
        else if(now_page == objects.page_user_home) ble_update_page("user_home");
        else if(now_page == objects.page_inject_ready) ble_update_page("inject_ready");
        else if(now_page == objects.page_inject_carbs) ble_update_page("inject_carbs");
        else if(now_page == objects.page_inject_insulin) ble_update_page("inject_insulin");
        else if(now_page == objects.page_inject_insert_vial) ble_update_page("inject_insert_vial");
        else if(now_page == objects.page_inject_prepare) ble_update_page("inject_prepare");
        else if(now_page == objects.page_inject_injecting) ble_update_page("inject_injecting");
        else if(now_page == objects.page_inject_complete) ble_update_page("inject_complete");
        else if(now_page == objects.page_monitor_notice) ble_update_page("monitor_notice");
        else if(now_page == objects.page_monitor_prepare) ble_update_page("monitor_prepare");
        else if(now_page == objects.page_monitor_running) ble_update_page("monitor_running");
        else if(now_page == objects.page_monitor_complete) ble_update_page("monitor_complete");

    }

    if (now_page == objects.page_user_home){
        // if bottle locked , unlock it
        if(bottle_locked){
            sensor_mcu_send(CMD_BOTTLE_UNLOCK);
            bottle_locked = false;
        }

        // read if CMD_READ_INJECT_MODULE is 1, then show the inject button
        uint8_t inject_module;
        sensor_mcu_send(CMD_READ_INJECT_MODULE);
        bool succ = sensor_mcu_read_uint8(&inject_module);
        if(succ && inject_module){
            lv_obj_remove_flag(objects.btn_user_home_inject, LV_OBJ_FLAG_HIDDEN);
        }
        else{
            lv_obj_add_flag(objects.btn_user_home_inject, LV_OBJ_FLAG_HIDDEN);
        }
    }

    else if(now_page == objects.page_inject_insert_vial){
        uint8_t vial_inserted;
        sensor_mcu_send(CMD_READ_BOTTLE_STATUS);
        bool succ = sensor_mcu_read_uint8(&vial_inserted);
        if(succ && vial_inserted){
            // send the command to lock the vial
            sensor_mcu_send(CMD_BOTTLE_LOCK);
            bottle_locked = true;
            lv_screen_load(objects.page_inject_ready);
        }
    }
    else if(now_page == objects.page_inject_prepare){
        //if this page pass 2 second 
        if(millis() - page_start_time > 2000){
            // read the mcu touch status
            uint8_t touch_status;
            sensor_mcu_send(CMD_READ_TOUCH_STATUS);
            bool succ = sensor_mcu_read_uint8(&touch_status);
            if(succ && touch_status){
                lv_screen_load(objects.page_inject_injecting);
            }
        }
    }

    // check until the finger is on the sensor
    else if(now_page == objects.page_monitor_prepare || now_page == objects.page_monitor_notice){
        // sensor_power_control(true);
        Serial.println("page_monitor_prepare");

        uint8_t fg_on1, fg_on2 = true;
        sensor_mcu_send(CMD_READ_MAX30102_1_FINGER_ON);
        sensor_mcu_send(CMD_READ_MAX30102_2_FINGER_ON);
        bool succ1 = sensor_mcu_read_uint8(&fg_on1);
        bool succ2 = sensor_mcu_read_uint8(&fg_on2);
        if(succ1 && succ2 && fg_on1 && fg_on2){
            // clear data cnt
            data_count = 0; 
            lv_screen_load(objects.page_monitor_running);
            Serial.println("finger on check success");
        }
        else if(now_page == objects.page_monitor_prepare && millis() - page_start_time > 5000){
            lv_screen_load(objects.page_monitor_notice);
            Serial.println("finger on check fail go in to notice page");
        }
        else{
            Serial.println("wait for finger on");
        }
    }
    
    // start read heart rate and spo2
    else if(now_page == objects.page_monitor_running){
        static uint8_t monitor_running_state = 0; // 

        // setp 0: send sensor 1 read command
        // step 1: if have data in buffer, read and go to next step
        // step 2: send sensor 2 read command
        // step 3: if have data in buffer, read and go to next step
        // step 4: if data collect ok 
        
        float tmp_float[2];

        switch(monitor_running_state){
            case 0:
                sensor_mcu_send(CMD_READ_MAX30102_1);
                monitor_running_state = 1;
                break;
            case 1:
                if(SENSOR_MCU_SERIAL.available() >= sizeof(float)*2){
                    sensor_mcu_read_float(&tmp_float[0]);
                    sensor_mcu_read_float(&tmp_float[1]);
                    Serial.printf("read sensor 1 data, heart rate: %f, spo2: %f\n", tmp_float[0], tmp_float[1]);
                    if(tmp_float[0]>0 && tmp_float[1]>0){
                        heart_rate[data_count] = tmp_float[0];
                        spo2[data_count] = tmp_float[1];
                        data_count++;

                        // show on ui 
                        lv_label_set_text_fmt(objects.lb_monitor_running_heart_rate, "%.0f", tmp_float[0]);
                    }
                    else{
                        // set --
                        lv_label_set_text(objects.lb_monitor_running_heart_rate, "--");
                    }
                    // check data collect ok
                    if(data_count >= 3){
                        monitor_running_state = 4; // collect ok
                    }
                    else{
                        monitor_running_state = 0; 
                    }
                }
                break;
            // case 2:
            //     sensor_mcu_send(CMD_READ_MAX30102_2);
            //     monitor_running_state = 3;
            //     break;
            // case 3:
            //     if(SENSOR_MCU_SERIAL.available() >= sizeof(float)*2){
            //         sensor_mcu_read_float(&tmp_float[0]);
            //         sensor_mcu_read_float(&tmp_float[1]);
            //         Serial.printf("read sensor 2 data, heart rate: %f, spo2: %f\n", tmp_float[0], tmp_float[1]);
            //         if(tmp_float[0]>0 && tmp_float[1]>0){
            //             heart_rate[data_count] = tmp_float[0];
            //             spo2[data_count] = tmp_float[1];
            //             data_count++;
            //         }
                    
            //         if(data_count >= 3){
            //             monitor_running_state = 4; // collect ok
            //         }
            //         else{
            //             monitor_running_state = 0; 
            //         }
            //     }
            //     break;

            case 4:
                // save the data
                monitor_running_state = 0;

                user_datas[login_user_id].heart_rate = (heart_rate[0] + heart_rate[1] + heart_rate[2]) / 3;
                user_datas[login_user_id].spo2 = (spo2[0] + spo2[1] + spo2[2]) / 3;
                
                // make fake data for no sensor data
                user_datas[login_user_id].blood_glucose = random(90, 180);
                user_datas[login_user_id].blood_pressure_sys = random(90, 120);
                user_datas[login_user_id].blood_pressure_dia = random(60, 80);
                
                lv_screen_load(objects.page_monitor_complete);
                break;
        }
    }
    
    // only show user result in the complete page
    else if(now_page == objects.page_monitor_complete){
        if(now_page != last_page){
            
            // show the data
            lv_label_set_text_fmt(objects.lb_monitor_complete_heart_rate, "%.0f", user_datas[login_user_id].heart_rate);
            lv_label_set_text_fmt(objects.lb_monitor_complete_spo2, "%.1f", user_datas[login_user_id].spo2);
            
            lv_label_set_text_fmt(objects.lb_monitor_complete_blood_gucose, "%.0f", user_datas[login_user_id].blood_glucose);
            lv_label_set_text_fmt(objects.lb_monitor_complete_blood_pressure_sys, "%.0f", user_datas[login_user_id].blood_pressure_sys);
            lv_label_set_text_fmt(objects.lb_monitor_complete_blood_pressure_dia, "%.0f", user_datas[login_user_id].blood_pressure_dia);
            
            Serial.printf("user data heart rate: %.2f, spo2: %.2f\n", user_datas[login_user_id].heart_rate, user_datas[login_user_id].spo2);

            // send data to ble .1f
            ble_update_heart_rate(String(user_datas[login_user_id].heart_rate,1).c_str());
            ble_update_spo2(String(user_datas[login_user_id].spo2,1).c_str());
            ble_update_glucose(String(user_datas[login_user_id].blood_glucose,1).c_str());
            ble_update_bp_sys(String(user_datas[login_user_id].blood_pressure_sys,1).c_str());
            ble_update_bp_dia(String(user_datas[login_user_id].blood_pressure_dia,1).c_str());
            
        }
            
    }

    else if(now_page == objects.main){
        // check how many user, hide the no user button
        if(is_new_page){
            Serial.println("main page is new");
        }

        if(is_new_page || user_datas_has_new_data){
            lv_obj_t *user_arr[MAX_USER] = {
                objects.btn_user_0, objects.btn_user_1, objects.btn_user_2, objects.btn_user_3,
                objects.btn_user_4, objects.btn_user_5, objects.btn_user_6, objects.btn_user_7
            };

            for(int i=0; i<MAX_USER; i++){
                // add hidden flag or clear 
                if(user_datas[i].available){
                    lv_obj_remove_flag(user_arr[i], LV_OBJ_FLAG_HIDDEN);
                    
                    // set name 
                    lv_obj_t *label = lv_obj_get_child(user_arr[i], 1); // 0 is img container , 1 is label
                    lv_label_set_text(label, user_datas[i].name);
                    

                    // get image dsc from user data
                    const lv_image_dsc_t *img_dsc;
                    if(user_datas[i].image_id == 0) img_dsc = &img_person;
                    //img_avatar
                    else if(user_datas[i].image_id == 1) img_dsc = &img_avatar;
                    else if(user_datas[i].image_id == 2) img_dsc = &img_avatar1;
                    else img_dsc = &img_person;

                    // set image
                    lv_obj_t *round_container = lv_obj_get_child(user_arr[i], 0); // 0 is img container , 1 is label
                    lv_obj_t *img = lv_obj_get_child(round_container, 0); // 0 is img, 1 is label
                    lv_image_set_src(img, img_dsc);
             
                }
                else{
                    lv_obj_add_flag(user_arr[i], LV_OBJ_FLAG_HIDDEN);
                }

            }
        }
        
    }
    
    else if(now_page == objects.page_inject_injecting){
        
        if(is_new_page){
            sensor_mcu_send(CMD_WS2812_SHOW2);
            // send to ble
            ble_update_insulin(String(inject_insulin,1).c_str());
            ble_update_carbs(String(inject_carbs,1).c_str());

            // send mcu motor
            sensor_mcu_send(CMD_VIBRATION);
        }
        
        // 5 second to inject finish , 0-100%
        // set inject_injecting_process_bar top value to show progress
        // bar is made by a floating container setting the top px value to disypaly the progress
        float inject_process_percent = 0;
        inject_process_percent = (millis() - page_start_time) / 2000.0 * 100;
        if(inject_process_percent >= 100){
            sensor_mcu_send(CMD_WS2812_SHOW1);
            lv_screen_load(objects.page_inject_complete);
        }
        else{
            lv_obj_set_pos(objects.inject_injecting_process_bar, 0, 240 * inject_process_percent / 100);
            // lb_inject_injecting_precent
            lv_label_set_text_fmt(objects.lb_inject_injecting_precent, "%.1f", inject_process_percent);
            lv_label_set_text_fmt(objects.lb_inject_injecting_remaining, "%.1f IU remaining", inject_insulin - inject_insulin * inject_process_percent / 100);
            
        }



    }
    
    else if(now_page == objects.page_inject_complete){
        if(is_new_page){
            // unlock vial
            sensor_mcu_send(CMD_BOTTLE_UNLOCK);
            bottle_locked = false;
        }
    }
    
    last_page = now_page;
}

void system_state_timer_init(){
    lv_timer_create(system_state_update, 100, NULL);
}





#endif