/*
MIT License

Copyright (c) 2020 lewis he

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//#include <mbed.h>
#include <Wire.h>
#include "MAX30208.h"

MAX30208_Class sensor;


uint8_t samplesTaken = 0;
float t;

void setup()
{
    Serial.begin(115200);
    Wire.begin(0x50);
    Serial.println("Initializing...");

    sensor.begin(Wire, I2C_SPEED_FAST);

    if (!sensor.begin(Wire, I2C_SPEED_FAST )) //Use default I2C port, 400kHz speed
   {
    Serial.println("MAX30208 was not found. Please check wiring/power. ");
    while (1);
   }
    Serial.println("Data is obtaining");
   // sensor.begin(Wire, slave_address);
    sensor.enableDATARDY();
    sensor.startConvert();
}

void loop()
{
    uint8_t mask = sensor.getINT();
    if (mask & MAX30208_INT_STATUS_TEMP_RDY) {
        
        int che=sensor.check();
       // Serial.println("check");
       // Serial.println(che);
        int id = sensor.readPartID();
        
        //Serial.println(id);
        t = sensor.readTemperature();
       // float f= readRegister8()
        DBG("RDY = samples:%u Temperature:%.2f", samplesTaken, t);
        sensor.startConvert();
       
    }
   // Serial.println("Temp=\n");
    Serial.println(t); 
    

    delay(100);
}
