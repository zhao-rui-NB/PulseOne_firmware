#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *page_user_home;
    lv_obj_t *page_inject_ready;
    lv_obj_t *page_inject_carbs;
    lv_obj_t *page_inject_insulin;
    lv_obj_t *page_inject_insert_vial;
    lv_obj_t *page_inject_prepare;
    lv_obj_t *page_inject_injecting;
    lv_obj_t *page_inject_complete;
    lv_obj_t *page_test_sensor;
    lv_obj_t *page_monitor_notice;
    lv_obj_t *page_monitor_prepare;
    lv_obj_t *page_monitor_running;
    lv_obj_t *page_monitor_complete;
    lv_obj_t *btn_user_0;
    lv_obj_t *btn_user_1;
    lv_obj_t *btn_user_2;
    lv_obj_t *btn_user_3;
    lv_obj_t *btn_user_4;
    lv_obj_t *btn_user_5;
    lv_obj_t *btn_user_6;
    lv_obj_t *btn_user_7;
    lv_obj_t *btn_user_home_back;
    lv_obj_t *lb_sel_user_name;
    lv_obj_t *btn_user_home_monitor;
    lv_obj_t *btn_user_home_inject;
    lv_obj_t *lb_last_time;
    lv_obj_t *btn_inject_back;
    lv_obj_t *btn_insulin;
    lv_obj_t *lb_inject_ready_insulin;
    lv_obj_t *btn_carbs;
    lv_obj_t *lb_inject_ready_carbs;
    lv_obj_t *btn_inject_run;
    lv_obj_t *btn_inject_carbs_back;
    lv_obj_t *border_1;
    lv_obj_t *roller_carbs;
    lv_obj_t *btn_inject_carbs_edit_ok;
    lv_obj_t *btn_inject_insulin_back;
    lv_obj_t *border;
    lv_obj_t *roller_insulin;
    lv_obj_t *btn_inject_insulin_edit_ok;
    lv_obj_t *btn_inject_insert_vial_back;
    lv_obj_t *btn_inject_prepare_back;
    lv_obj_t *btn_inject_prepare_ok;
    lv_obj_t *inject_injecting_process_bar;
    lv_obj_t *btn_inject_ingecting_back;
    lv_obj_t *lb_inject_injecting_precent;
    lv_obj_t *lb_inject_injecting_remaining;
    lv_obj_t *btn_inject_back_6;
    lv_obj_t *btn_inject_complete_ok;
    lv_obj_t *btn_test_sensor_back;
    lv_obj_t *lb_test1;
    lv_obj_t *lb_test2;
    lv_obj_t *btn_test_test;
    lv_obj_t *btn_test_next;
    lv_obj_t *btn_monitor_prepare_back;
    lv_obj_t *btn_monitor_notice_back;
    lv_obj_t *btn_monitor_complete_back_1;
    lv_obj_t *lb_monitor_running_heart_rate;
    lv_obj_t *btn_monitor_complete_back;
    lv_obj_t *lb_monitor_complete_type;
    lv_obj_t *btns;
    lv_obj_t *btn_monitor_complete_glucose;
    lv_obj_t *btn_monitor_complete_pressure;
    lv_obj_t *btn_monitor_complete_spo2;
    lv_obj_t *btn_monitor_complete_heart_rate;
    lv_obj_t *tabview_monitor_complete;
    lv_obj_t *tab_blood_gucose;
    lv_obj_t *lb_monitor_complete_blood_gucose;
    lv_obj_t *tab_pressure;
    lv_obj_t *lb_monitor_complete_blood_pressure_sys;
    lv_obj_t *lb_monitor_complete_blood_pressure_dia;
    lv_obj_t *tab_spo2;
    lv_obj_t *lb_monitor_complete_spo2;
    lv_obj_t *tab_heart_rate;
    lv_obj_t *lb_monitor_complete_heart_rate;
    lv_obj_t *btn_monitor_complete_ok;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_PAGE_USER_HOME = 2,
    SCREEN_ID_PAGE_INJECT_READY = 3,
    SCREEN_ID_PAGE_INJECT_CARBS = 4,
    SCREEN_ID_PAGE_INJECT_INSULIN = 5,
    SCREEN_ID_PAGE_INJECT_INSERT_VIAL = 6,
    SCREEN_ID_PAGE_INJECT_PREPARE = 7,
    SCREEN_ID_PAGE_INJECT_INJECTING = 8,
    SCREEN_ID_PAGE_INJECT_COMPLETE = 9,
    SCREEN_ID_PAGE_TEST_SENSOR = 10,
    SCREEN_ID_PAGE_MONITOR_NOTICE = 11,
    SCREEN_ID_PAGE_MONITOR_PREPARE = 12,
    SCREEN_ID_PAGE_MONITOR_RUNNING = 13,
    SCREEN_ID_PAGE_MONITOR_COMPLETE = 14,
};

void create_screen_main();
void tick_screen_main();

void create_screen_page_user_home();
void tick_screen_page_user_home();

void create_screen_page_inject_ready();
void tick_screen_page_inject_ready();

void create_screen_page_inject_carbs();
void tick_screen_page_inject_carbs();

void create_screen_page_inject_insulin();
void tick_screen_page_inject_insulin();

void create_screen_page_inject_insert_vial();
void tick_screen_page_inject_insert_vial();

void create_screen_page_inject_prepare();
void tick_screen_page_inject_prepare();

void create_screen_page_inject_injecting();
void tick_screen_page_inject_injecting();

void create_screen_page_inject_complete();
void tick_screen_page_inject_complete();

void create_screen_page_test_sensor();
void tick_screen_page_test_sensor();

void create_screen_page_monitor_notice();
void tick_screen_page_monitor_notice();

void create_screen_page_monitor_prepare();
void tick_screen_page_monitor_prepare();

void create_screen_page_monitor_running();
void tick_screen_page_monitor_running();

void create_screen_page_monitor_complete();
void tick_screen_page_monitor_complete();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/