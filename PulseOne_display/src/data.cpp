#include "data.h"


UserData user_datas[8];
bool user_datas_has_new_data = false;
uint8_t login_user_id = 0;

// inject carbs
float inject_carbs = 10;
// inject insulin
float inject_insulin = 10;


void user_datas_init(){
    user_datas[0].available = true;
    strcpy(user_datas[0].name, "Guest");


    strcpy(user_datas[1].name, "zhao rui");
    strcpy(user_datas[2].name, "hans");
    strcpy(user_datas[3].name, "user 3");
    strcpy(user_datas[4].name, "user 4");
    strcpy(user_datas[5].name, "user 5");
    strcpy(user_datas[6].name, "user 6");
    strcpy(user_datas[7].name, "user 7");


    user_datas[1].available = true;
    user_datas[2].available = true;
    // user_datas[3].available = true;

    user_datas[1].image_id = 1;
    user_datas[2].image_id = 2;


}