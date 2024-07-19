/**
  * Copyright (c) 2024 Daniel Hutzschenreuter (ORCID: 0000-0002-9095-0063)
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy 
  * of this software and associated documentation files (the “Software”), to deal 
  * in the Software without restriction, including without limitation the rights to 
  * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
  * the Software, and to permit persons to whom the Software is furnished to do so, 
  * subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in all copies 
  * or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
  * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
  * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
  * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
  * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
  
  * Serial on baud 115200
  */
#include "DEV_Config_ESP32_S3_Zero.h"
#include "EPD_klein.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>

bool DEBUG_MODE = false;      // false, if serial print disabled

const int ACTIVE = 0;   // state active = loop to display pictures
const int CHARGE = 1;   // state charge = picture requesting charging
const int STOPED = 2;   // state stopped device = end of operation of device

int mode = ACTIVE;

#define VOLT_VCC_PIN 2    // 3.3 to 4.2 volt input of device battery, reference to detect need of charging
int vVc;                  // ADC value of voltage pin: < 2000 if battery empty, 2050 to stop device, 2100 to go to charge mode

UBYTE_ESP32S3Z *BlackImage;               // storage of black picture part 
UBYTE_ESP32S3Z *RedImage;                 // storage of red picture part
const int MAX_PICTURE_NUMBER = 3;         // number of pictures on the device
int pictureCount = 0;                     // counter for actual picture displayed, range [0,MAX_PICTURE_NUMBER -1]
const int secondsUntilNextPicture = 200;  // time until picture update, minimum 180 seconds for waveshare display!

const uint8_t InterruptPin = 6;           // pin of button to stop device operation, activated by pull to ground
bool interruptDetected = false;           // state of interrupt, if true, then interrupt was triggered with Interrupt pin


void setup()
{
  if (DEBUG_MODE)
  {
    delay(1000);
    Serial.begin(115200);
    delay(500);
    printSerial("Startup ESP32-S2 ePaper");
  }

  // init voltage reading and set initial mode
  pinMode(VOLT_VCC_PIN,INPUT);
  checkVoltage();

  // if voltage sufficient to operate ePaper
  if (vVc >= 2050)
  {
    // startup ePaper
    printSerial("..init ePaper");
    setupEPD();
    // init interrupt event to stop device
    printSerial("..init stop interrupt");
    pinMode(InterruptPin, INPUT_PULLUP);
    activateInterrupt();
    // init active mode
    printSerial("..set active mode startup");
    mode = ACTIVE;

    // check if device needs charging
    if (vVc < 2100) {
      printSerial("..set charge mode (startup)");
      mode = CHARGE;
      //EPD print charge screen
      printChargePicture();
    }
  }
  // if device is out of power
  else
  {
    printSerial("..set stop mode (startup)");
    mode = STOPED;
    printSerial(">>>END OF OPERATION<<<");
  }  
}

/* The main loop -------------------------------------------------------------*/
void loop()
{
  // get voltage battery
    checkVoltage();

  // depending on the mode, picture diplay, charge display or stop action is done
  if (mode == ACTIVE)
  { 
    // if voltage sufficiten (> 2100)
    if (vVc >= 2100)
    {
      // then paint picture
      printPicture(pictureCount);
      // update picture index
      updatePictureCount();
      // delay, each second interrupt is checked
      devDelay(secondsUntilNextPicture);
    }
    // if voltage (power low)
    else if (vVc >= 2050)
    {
      Serial.println("..set charge mode");
      mode = CHARGE;
      //EPD print charge screen
      printChargePicture();
      delay(500);
    }
    // voltage too low, stop operation of device
    else
    {
      Serial.println("..set stop mode");
      mode = STOPED;
      stopEPD();
      delay(500);
    }  
  }
  else if (mode == CHARGE)
  {
    // delay 5 minutes and check if device is stopped
    devDelay(300);
    // power too low, stop device
    if (vVc < 2050)
    {
      Serial.println("..set stop mode");
      mode = STOPED;
      stopEPD();
      delay(500);
    }

  }
  else if (mode == STOPED)
  {
    // do nothing, but delay
    delay(1000000);
  }
}

void printSerial(const char* text)
{
  if (DEBUG_MODE)
  {
    Serial.println(text);
  }
}

void printSerial(int number)
{
  if (DEBUG_MODE)
  {
    Serial.println(number);
  }
}









