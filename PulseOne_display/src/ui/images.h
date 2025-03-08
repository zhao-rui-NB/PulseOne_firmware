#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_avatar;
extern const lv_img_dsc_t img_avatar1;
extern const lv_img_dsc_t img_arrow_forward;
extern const lv_img_dsc_t img_arrow_forward1;
extern const lv_img_dsc_t img_chevron_left;
extern const lv_img_dsc_t img_chevron_right;
extern const lv_img_dsc_t img_ecg_heart;
extern const lv_img_dsc_t img_history;
extern const lv_img_dsc_t img_person;
extern const lv_img_dsc_t img_red_body;
extern const lv_img_dsc_t img_syringe;
extern const lv_img_dsc_t img_hold_sensor;
extern const lv_img_dsc_t img_ecg_heart_1;
extern const lv_img_dsc_t img_spo2_1;
extern const lv_img_dsc_t img_glucose_1;
extern const lv_img_dsc_t img_blood_pressure_1;
extern const lv_img_dsc_t img_ryg4040;
extern const lv_img_dsc_t img_check;
extern const lv_img_dsc_t img_check1;
extern const lv_img_dsc_t img_measuring;
extern const lv_img_dsc_t img_favorite;
extern const lv_img_dsc_t img_favorite_dis;
extern const lv_img_dsc_t img_favorite_en;
extern const lv_img_dsc_t img_humidity_high_dis;
extern const lv_img_dsc_t img_humidity_high_en;
extern const lv_img_dsc_t img_nest_secure_alarm_dis;
extern const lv_img_dsc_t img_nest_secure_alarm_en;
extern const lv_img_dsc_t img_total_dissolved_solids_dis;
extern const lv_img_dsc_t img_total_dissolved_solids_en;
extern const lv_img_dsc_t img_eject;
extern const lv_img_dsc_t img_pf1;
extern const lv_img_dsc_t img_pf2;
extern const lv_img_dsc_t img_pf3;
extern const lv_img_dsc_t img_pf4;
extern const lv_img_dsc_t img_pf5;
extern const lv_img_dsc_t img_pf6;
extern const lv_img_dsc_t img_pf7;
extern const lv_img_dsc_t img_pf8;
extern const lv_img_dsc_t img_pf9;
extern const lv_img_dsc_t img_pf10;
extern const lv_img_dsc_t img_check_green;
extern const lv_img_dsc_t img_insert_pod;
extern const lv_img_dsc_t img_inject_insert;
extern const lv_img_dsc_t img_monitor_prepare;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[44];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/