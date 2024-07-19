/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-02-19
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_ESP32S3Z_H_
#define _DEV_CONFIG_ESP32S3Z_H_

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

/**
 * data
**/
#define UBYTE_ESP32S3Z   uint8_t
#define UWORD_ESP32S3Z   uint16_t
#define UDOUBLE_ESP32S3Z uint32_t

/**
 * GPIO config
**/
#define EPD_ESP32S3Z_SCK_PIN  12
#define EPD_ESP32S3Z_MOSI_PIN 11
#define EPD_ESP32S3Z_CS_PIN   10
#define EPD_ESP32S3Z_RST_PIN  8
#define EPD_ESP32S3Z_DC_PIN   9
#define EPD_ESP32S3Z_BUSY_PIN 7

#define GPIO_ESP32S3Z_PIN_SET   1
#define GPIO_ESP32S3Z_PIN_RESET 0

/**
 * GPIO read and write
**/
#define DEV_ESP32S3Z_Digital_Write(_pin, _value) digitalWrite(_pin, _value == 0? LOW:HIGH)
#define DEV_ESP32S3Z_Digital_Read(_pin) digitalRead(_pin)

/**
 * delay x ms
**/
#define DEV_ESP32S3Z_Delay_ms(__xms) delay(__xms)

/*------------------------------------------------------------------------------------------------------*/
UBYTE_ESP32S3Z DEV_ESP32S3Z_Module_Init(void);
void GPIO_ESP32S3Z_Mode(UWORD_ESP32S3Z GPIO_Pin, UWORD_ESP32S3Z Mode);
void DEV_ESP32S3Z_SPI_WriteByte(UBYTE_ESP32S3Z data);
UBYTE_ESP32S3Z DEV_ESP32S3Z_SPI_ReadByte();
void DEV_ESP32S3Z_SPI_Write_nByte(UBYTE_ESP32S3Z *pData, UDOUBLE_ESP32S3Z len);

#endif
