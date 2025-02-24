
#include "ble.h"
#include "data.h"

uint8_t ble_setting_user_id = 0;

BLEServer* pServer = nullptr;

BLEService* pSystemStateService = nullptr;
BLEService* pUserListService = nullptr;
BLEService* pMonitorService = nullptr;
BLEService* pInjectService = nullptr;

// System State 特徵值
BLECharacteristic* pPageCharacteristic = nullptr;
BLECharacteristic* pLoginedUserCharacteristic = nullptr;

// User List 特徵值
BLECharacteristic* pUserIdCharacteristic = nullptr;
BLECharacteristic* pUserValidCharacteristic = nullptr;
BLECharacteristic* pUserNameCharacteristic = nullptr;
BLECharacteristic* pUserImageIdCharacteristic = nullptr;

// Monitor 特徵值
BLECharacteristic* pHeartRateCharacteristic = nullptr;
BLECharacteristic* pSpo2Characteristic = nullptr;
BLECharacteristic* pGlucoseCharacteristic = nullptr;
BLECharacteristic* pBpSysCharacteristic = nullptr;
BLECharacteristic* pBpDiaCharacteristic = nullptr;

// Inject 特徵值
BLECharacteristic* pInsulinCharacteristic = nullptr;
BLECharacteristic* pCarbsCharacteristic = nullptr;



class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
    }

    void onDisconnect(BLEServer* pServer) {
      BLEDevice::startAdvertising();
    }
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// User List 
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++

// User ID 特徵值
class UserIdCharCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        // try to int 0-7
        int user_id = std::stoi(value);
        if(user_id >= 0 && user_id < MAX_USER){
            ble_setting_user_id = user_id;
            Serial.printf("[ble] now set setting user id to %d\n", user_id);
        }
        user_datas_has_new_data = true;

    }
    void onRead(BLECharacteristic *pCharacteristic){
        pCharacteristic->setValue(std::to_string(ble_setting_user_id));
    }

};

// User Valid 特徵值
class UserValidCharCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic){
        // a true or false value: this user data is available or not
        std::string value = pCharacteristic->getValue();
        if(value == "1"){
            user_datas[ble_setting_user_id].available = true;
            Serial.printf("[ble] user %d is available\n", ble_setting_user_id);
        }
        else{
            user_datas[ble_setting_user_id].available = false;
            Serial.printf("[ble] user %d is not available\n", ble_setting_user_id);
        }
        user_datas_has_new_data = true;

    }
    void onRead(BLECharacteristic *pCharacteristic){
        pCharacteristic->setValue(user_datas[ble_setting_user_id].available ? "1" : "0");
    }
};

// User Name 特徵值
class UserNameCharCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic){
        std::string value = pCharacteristic->getValue();
        // on length 20
        if (value.length() > 20-1){
            value = value.substr(0, 20-1);
        }
        strcpy(user_datas[ble_setting_user_id].name, value.c_str());

        Serial.printf("[ble] user %d name is set to %s\n", ble_setting_user_id, value.c_str());
        user_datas_has_new_data = true;

    }
    void onRead(BLECharacteristic *pCharacteristic){
        pCharacteristic->setValue(user_datas[ble_setting_user_id].name);
    }
};

// User Image Write 特徵值
class UserImageIdCharCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic){
        // get int value for string 
        std::string value = pCharacteristic->getValue();
        int image_id = std::stoi(value);
        if(image_id >= 0 && image_id < 3){
            user_datas[ble_setting_user_id].image_id = image_id;
            Serial.printf("[ble] user %d image id is set to %d\n", ble_setting_user_id, image_id);
        }
        user_datas_has_new_data = true;
    }
    void onRead(BLECharacteristic *pCharacteristic){
        pCharacteristic->setValue(std::to_string(user_datas[ble_setting_user_id].image_id));
    }
};


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++



void ble_init(){
    // 初始化 BLE 設備
    BLEDevice::init("PulseOne");
    
    // 創建 BLE 服務器
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // 創建系統狀態服務
    pSystemStateService = pServer->createService(SYSTEM_STATE_SERVICE_UUID);
    pPageCharacteristic = pSystemStateService->createCharacteristic(PAGE_CHAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pLoginedUserCharacteristic = pSystemStateService->createCharacteristic(LOGINED_USER_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

    // 創建用戶列表服務
    pUserListService = pServer->createService(USER_LIST_SERVICE_UUID);
    pUserIdCharacteristic = pUserListService->createCharacteristic(USER_ID_CHAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    pUserValidCharacteristic = pUserListService->createCharacteristic(USER_VALID_CHAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    pUserNameCharacteristic = pUserListService->createCharacteristic(USER_NAME_CHAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    pUserImageIdCharacteristic = pUserListService->createCharacteristic(USER_IMAGE_ID_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);


    // 添加用戶列表服務的回調函數
    pUserIdCharacteristic->setCallbacks(new UserIdCharCallbacks());
    pUserValidCharacteristic->setCallbacks(new UserValidCharCallbacks());
    pUserNameCharacteristic->setCallbacks(new UserNameCharCallbacks());
    pUserImageIdCharacteristic->setCallbacks(new UserImageIdCharCallbacks());


    // 創建監測服務
    pMonitorService = pServer->createService(BLEUUID(MONITOR_SERVICE_UUID), 30, 0);
    pHeartRateCharacteristic = pMonitorService->createCharacteristic(HEART_RATE_CHAR_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pSpo2Characteristic = pMonitorService->createCharacteristic(SPO2_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pGlucoseCharacteristic = pMonitorService->createCharacteristic(GLUCOSE_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pBpSysCharacteristic = pMonitorService->createCharacteristic(BP_SYS_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pBpDiaCharacteristic = pMonitorService->createCharacteristic(BP_DIA_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

    // 創建注射服務
    pInjectService = pServer->createService(INJECT_SERVICE_UUID);
    pInsulinCharacteristic = pInjectService->createCharacteristic(INSULIN_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    pCarbsCharacteristic = pInjectService->createCharacteristic(CARBS_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

    // 為所有支持通知的特徵值添加描述符
    pPageCharacteristic->addDescriptor(new BLE2902());
    pLoginedUserCharacteristic->addDescriptor(new BLE2902());

    pHeartRateCharacteristic->addDescriptor(new BLE2902());
    pSpo2Characteristic->addDescriptor(new BLE2902());
    pGlucoseCharacteristic->addDescriptor(new BLE2902());
    pBpSysCharacteristic->addDescriptor(new BLE2902());
    pBpDiaCharacteristic->addDescriptor(new BLE2902());

    pInsulinCharacteristic->addDescriptor(new BLE2902());
    pCarbsCharacteristic->addDescriptor(new BLE2902());
    

    // 啟動所有服務
    pSystemStateService->start();
    pUserListService->start();
    pMonitorService->start();
    pInjectService->start();

    // 開始廣播
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SYSTEM_STATE_SERVICE_UUID);
    pAdvertising->addServiceUUID(USER_LIST_SERVICE_UUID);
    pAdvertising->addServiceUUID(MONITOR_SERVICE_UUID);
    pAdvertising->addServiceUUID(INJECT_SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    // pAdvertising->setMinPreferred(0x06);  
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();

    Serial.println("BLE device ready");
}

void ble_update_page(const char *page){
    pPageCharacteristic->setValue(page);
    pPageCharacteristic->notify();
}

void ble_update_logined_user(const char *user){
    pLoginedUserCharacteristic->setValue(user);
    pLoginedUserCharacteristic->notify();
}

// Monitor
void ble_update_heart_rate(const char *heart_rate){
    pHeartRateCharacteristic->setValue(heart_rate);
    pHeartRateCharacteristic->notify();
}

void ble_update_spo2(const char *spo2){
    pSpo2Characteristic->setValue(spo2);
    pSpo2Characteristic->notify();
}

void ble_update_glucose(const char *glucose){
    pGlucoseCharacteristic->setValue(glucose);
    pGlucoseCharacteristic->notify();
}

void ble_update_bp_sys(const char *bp_sys){
    pBpSysCharacteristic->setValue(bp_sys);
    pBpSysCharacteristic->notify();
}

void ble_update_bp_dia(const char *bp_dia){
    pBpDiaCharacteristic->setValue(bp_dia);
    pBpDiaCharacteristic->notify();
}

// Inject

void ble_update_insulin(const char *insulin){
    pInsulinCharacteristic->setValue(insulin);
    pInsulinCharacteristic->notify();
}

void ble_update_carbs(const char *carbs){
    pCarbsCharacteristic->setValue(carbs);
    pCarbsCharacteristic->notify();
}











