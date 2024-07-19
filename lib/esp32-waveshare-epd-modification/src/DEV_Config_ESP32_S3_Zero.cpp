/*****************************************************************************
* | File      	:   DEV_Config.c
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
#include "DEV_Config_ESP32_S3_Zero.h"

void GPIO_ESP32S3Z_Config(void)
{
    pinMode(EPD_ESP32S3Z_BUSY_PIN,  INPUT);
    pinMode(EPD_ESP32S3Z_RST_PIN , OUTPUT);
    pinMode(EPD_ESP32S3Z_DC_PIN  , OUTPUT);
    
    pinMode(EPD_ESP32S3Z_SCK_PIN, OUTPUT);
    pinMode(EPD_ESP32S3Z_MOSI_PIN, OUTPUT);
    pinMode(EPD_ESP32S3Z_CS_PIN , OUTPUT);

    digitalWrite(EPD_ESP32S3Z_CS_PIN , HIGH);
    digitalWrite(EPD_ESP32S3Z_SCK_PIN, LOW);
}

void GPIO_ESP32S3Z_Mode(UWORD_ESP32S3Z GPIO_Pin, UWORD_ESP32S3Z Mode)
{
    if(Mode == 0) {
        pinMode(GPIO_Pin , INPUT);
	} else {
		pinMode(GPIO_Pin , OUTPUT);
	}
}
/******************************************************************************
function:	Module Initialize, the BCM2835 library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE_ESP32S3Z DEV_ESP32S3Z_Module_Init(void)
{
	//gpio
	GPIO_ESP32S3Z_Config();

	//serial printf
	Serial.begin(115200);

	// spi
	// SPI.setDataMode(SPI_MODE0);
	// SPI.setBitOrder(MSBFIRST);
	// SPI.setClockDivider(SPI_CLOCK_DIV4);
	// SPI.begin();

	return 0;
}

/******************************************************************************
function:
			SPI read and write
******************************************************************************/
void DEV_ESP32S3Z_SPI_WriteByte(UBYTE_ESP32S3Z data)
{
    //SPI.beginTransaction(spi_settings);
    digitalWrite(EPD_ESP32S3Z_CS_PIN, GPIO_ESP32S3Z_PIN_RESET);

    for (int i = 0; i < 8; i++)
    {
        if ((data & 0x80) == 0) digitalWrite(EPD_ESP32S3Z_MOSI_PIN, GPIO_ESP32S3Z_PIN_RESET); 
        else                    digitalWrite(EPD_ESP32S3Z_MOSI_PIN, GPIO_ESP32S3Z_PIN_SET);

        data <<= 1;
        digitalWrite(EPD_ESP32S3Z_SCK_PIN, GPIO_ESP32S3Z_PIN_SET);     
        digitalWrite(EPD_ESP32S3Z_SCK_PIN, GPIO_ESP32S3Z_PIN_RESET);
    }

    //SPI.transfer(data);
    digitalWrite(EPD_ESP32S3Z_CS_PIN, GPIO_ESP32S3Z_PIN_SET);
    //SPI.endTransaction();	
}

UBYTE_ESP32S3Z DEV_ESP32S3Z_SPI_ReadByte()
{
    UBYTE_ESP32S3Z j=0xff;
    GPIO_ESP32S3Z_Mode(EPD_ESP32S3Z_MOSI_PIN, 0);
    digitalWrite(EPD_ESP32S3Z_CS_PIN, GPIO_ESP32S3Z_PIN_RESET);
    for (int i = 0; i < 8; i++)
    {
        j = j << 1;
        if (digitalRead(EPD_ESP32S3Z_MOSI_PIN))  j = j | 0x01;
        else                            j = j & 0xfe;
        
        digitalWrite(EPD_ESP32S3Z_SCK_PIN, GPIO_ESP32S3Z_PIN_SET);     
        digitalWrite(EPD_ESP32S3Z_SCK_PIN, GPIO_ESP32S3Z_PIN_RESET);
    }
    digitalWrite(EPD_ESP32S3Z_CS_PIN, GPIO_ESP32S3Z_PIN_SET);
    GPIO_ESP32S3Z_Mode(EPD_ESP32S3Z_MOSI_PIN, 1);
    return j;
}

void DEV_ESP32S3Z_SPI_Write_nByte(UBYTE_ESP32S3Z *pData, UDOUBLE_ESP32S3Z len)
{
    for (int i = 0; i < len; i++)
        DEV_ESP32S3Z_SPI_WriteByte(pData[i]);
}
