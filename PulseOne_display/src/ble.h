#ifndef _BLE_H_
#define _BLE_H_


#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>


/*

    service and characteristic

    system state 
    |-- page
    |-- logined_user
    user list 
    |-- id
    |-- valid
    |-- name
    |-- image address
    |-- image write
    monitor
    |-- heart rate
    |-- spo2
    |-- blood glucose
    |-- blood pressure sys
    |-- blood pressure dia
    inject
    |-- insulin
    |-- carbs


*/

// 定義服務 UUID (使用自定義 UUID)
#define SYSTEM_STATE_SERVICE_UUID      "d94c1000-58fe-4099-bc79-39a21e540e89"
#define USER_LIST_SERVICE_UUID         "d94c2000-58fe-4099-bc79-39a21e540e89"
#define MONITOR_SERVICE_UUID           "d94c3000-58fe-4099-bc79-39a21e540e89"
#define INJECT_SERVICE_UUID            "d94c4000-58fe-4099-bc79-39a21e540e89"

// System State 特徵值 UUID
#define PAGE_CHAR_UUID                 "d94c1001-58fe-4099-bc79-39a21e540e89"
#define LOGINED_USER_CHAR_UUID         "d94c1002-58fe-4099-bc79-39a21e540e89"

// User List 特徵值 UUID
#define USER_ID_CHAR_UUID              "d94c2001-58fe-4099-bc79-39a21e540e89"
#define USER_VALID_CHAR_UUID           "d94c2002-58fe-4099-bc79-39a21e540e89"
#define USER_NAME_CHAR_UUID            "d94c2003-58fe-4099-bc79-39a21e540e89"
#define USER_IMAGE_ID_UUID             "d94c2e04-58fe-4099-bc79-39a21e540e89"


// Monitor 特徵值 UUID
#define HEART_RATE_CHAR_UUID           "d94c3001-58fe-4099-bc79-39a21e540e89"
#define SPO2_CHAR_UUID                 "d94c3002-58fe-4099-bc79-39a21e540e89"
#define GLUCOSE_CHAR_UUID              "d94c3003-58fe-4099-bc79-39a21e540e89"
#define BP_SYS_CHAR_UUID               "d94c3004-58fe-4099-bc79-39a21e540e89"
#define BP_DIA_CHAR_UUID               "d94c3005-58fe-4099-bc79-39a21e540e89"

// Inject 特徵值 UUID
#define INSULIN_CHAR_UUID              "d94c4001-58fe-4099-bc79-39a21e540e89"
#define CARBS_CHAR_UUID                "d94c4002-58fe-4099-bc79-39a21e540e89"

extern uint8_t ble_setting_user_id;

extern BLEServer* pServer;

extern BLEService* pSystemStateService;
extern BLEService* pUserListService;
extern BLEService* pMonitorService;
extern BLEService* pInjectService;

extern BLECharacteristic* pPageCharacteristic;
extern BLECharacteristic* pLoginedUserCharacteristic;

extern BLECharacteristic* pUserIdCharacteristic;
extern BLECharacteristic* pUserValidCharacteristic;
extern BLECharacteristic* pUserNameCharacteristic;
extern BLECharacteristic* pUserImageIdCharacteristic;

extern BLECharacteristic* pHeartRateCharacteristic;
extern BLECharacteristic* pSpo2Characteristic;
extern BLECharacteristic* pGlucoseCharacteristic;
extern BLECharacteristic* pBpSysCharacteristic;
extern BLECharacteristic* pBpDiaCharacteristic;

extern BLECharacteristic* pInsulinCharacteristic;
extern BLECharacteristic* pCarbsCharacteristic;


class MyServerCallbacks;

class UserIdCharCallbacks;
class UserValidCharCallbacks;
class UserNameCharCallbacks;
class UserImageAddrCharCallbacks;
class UserImageWriteCharCallbacks;


void ble_init();
void ble_update_page(const char *page);
void ble_update_logined_user(const char *user);
void ble_update_heart_rate(const char *heart_rate);
void ble_update_spo2(const char *spo2);
void ble_update_glucose(const char *glucose);
void ble_update_bp_sys(const char *bp_sys);
void ble_update_bp_dia(const char *bp_dia);
void ble_update_insulin(const char *insulin);
void ble_update_carbs(const char *carbs);







#endif // _BLE_H_