/*****************************************************************************
* | File      	:   EPD_1in54b_V2.h
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper b V2
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-04-02
* | Info        :
* -----------------------------------------------------------------------------
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
#include "EPD_1in54b_V2_ESP32_S3_Zero.h"
#include "Debug.h"

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_1IN54B_V2_ESP32S3Z_Reset(void)
{
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_RST_PIN, 1);
    DEV_ESP32S3Z_Delay_ms(100);
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_RST_PIN, 0);
    DEV_ESP32S3Z_Delay_ms(10);
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_RST_PIN, 1);
    DEV_ESP32S3Z_Delay_ms(100);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_1IN54B_V2_ESP32S3Z_SendCommand(UBYTE_ESP32S3Z Reg)
{
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_DC_PIN, 0);
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_CS_PIN, 0);
    DEV_ESP32S3Z_SPI_WriteByte(Reg);
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_1IN54B_V2_ESP32S3Z_SendData(UBYTE_ESP32S3Z Data)
{
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_DC_PIN, 1);
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_CS_PIN, 0);
    DEV_ESP32S3Z_SPI_WriteByte(Data);
    DEV_ESP32S3Z_Digital_Write(EPD_ESP32S3Z_CS_PIN, 1);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
static void EPD_1IN54B_V2_ESP32S3Z_ReadBusy(void)
{
    //Debug("e-Paper busy\r\n");
    while(1) {
        if(DEV_ESP32S3Z_Digital_Read(EPD_ESP32S3Z_BUSY_PIN) == 0)
            break;
    }
    DEV_ESP32S3Z_Delay_ms(200);
    //Debug("e-Paper busy release\r\n");
}


/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_1IN54B_V2_ESP32S3Z_Init(void)
{
    EPD_1IN54B_V2_ESP32S3Z_Reset();

    EPD_1IN54B_V2_ESP32S3Z_ReadBusy();   
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x12);  //SWRESET
    EPD_1IN54B_V2_ESP32S3Z_ReadBusy();   

    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x01); //Driver output control      
    EPD_1IN54B_V2_ESP32S3Z_SendData(0xC7);
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x00);
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x01);

    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x11); //data entry mode       
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x01);

    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x44); //set Ram-X address start/end position   
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x00);
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x18);    //0x18-->(24+1)*8=200

    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x45); //set Ram-Y address start/end position          
    EPD_1IN54B_V2_ESP32S3Z_SendData(0xC7);    //0xC7-->(199+1)=200
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x00);
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x00);
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x00); 

    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x3C); //BorderWavefrom
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x05);

    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x18); //Read built-in temperature sensor
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x80);

    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x4E);   // set RAM x address count to 0;
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x00);
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x4F);   // set RAM y address count to 0X199;    
    EPD_1IN54B_V2_ESP32S3Z_SendData(0xC7);
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x00);
    EPD_1IN54B_V2_ESP32S3Z_ReadBusy();
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_1IN54B_V2_ESP32S3Z_Clear(void)
{
    
    unsigned int i;	
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x24);   //write RAM for black(0)/white (1)
    for(i=0;i<5000;i++)
    {               
        EPD_1IN54B_V2_ESP32S3Z_SendData(0xff);
    }
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x26);   //write RAM for black(0)/white (1)
    for(i=0;i<5000;i++)
    {               
        EPD_1IN54B_V2_ESP32S3Z_SendData(0x00);
    }
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x22); //Display Update Control
    EPD_1IN54B_V2_ESP32S3Z_SendData(0xF7);   
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x20);  //Activate Display Update Sequence
    EPD_1IN54B_V2_ESP32S3Z_ReadBusy();   
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_1IN54B_V2_ESP32S3Z_Display(const UBYTE_ESP32S3Z *blackimage, const UBYTE_ESP32S3Z *redimage)
{
    UWORD_ESP32S3Z Width, Height;
    Width = (EPD_1IN54B_V2_ESP32S3Z_WIDTH % 8 == 0)? (EPD_1IN54B_V2_ESP32S3Z_WIDTH / 8 ): (EPD_1IN54B_V2_ESP32S3Z_WIDTH / 8 + 1);
    Height = EPD_1IN54B_V2_ESP32S3Z_HEIGHT;

     unsigned int i;	
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x24);   //write RAM for black(0)/white (1)
    for(i=0;i<Width*Height;i++)
    {               
        EPD_1IN54B_V2_ESP32S3Z_SendData(blackimage[i]);
    }
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x26);   //write RAM for black(0)/white (1)
    for(i=0;i<Width*Height;i++)
    {               
        EPD_1IN54B_V2_ESP32S3Z_SendData(~redimage[i]);
    }
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x22); //Display Update Control
    EPD_1IN54B_V2_ESP32S3Z_SendData(0xF7);   
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x20);  //Activate Display Update Sequence
    EPD_1IN54B_V2_ESP32S3Z_ReadBusy();   
}

/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_1IN54B_V2_ESP32S3Z_Sleep(void)
{
    EPD_1IN54B_V2_ESP32S3Z_SendCommand(0x10); //enter deep sleep
    EPD_1IN54B_V2_ESP32S3Z_SendData(0x01); 
    DEV_ESP32S3Z_Delay_ms(100);
}
