#include <Arduino.h>

#include "CST816S.h"



CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq


void setup() {
    
    Serial.begin(115200);
    touch.begin();
}


void loop(){

    if(touch.available()){
        Serial.printf("Gesture: %s, x=%d, y=%d\n", touch.gesture().c_str(), touch.data.x, touch.data.y);
    }

    delay(100);

}