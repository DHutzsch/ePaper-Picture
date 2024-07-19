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
  *
  * Serial on baud 115200
  */

void setupEPD()
{
  DEV_ESP32S3Z_Module_Init();
  initEPD();

  //Create a new image cache
  UWORD_ESP32S3Z Imagesize = ((EPD_1IN54B_V2_ESP32S3Z_WIDTH % 8 == 0) ? (EPD_1IN54B_V2_ESP32S3Z_WIDTH / 8 ) : (EPD_1IN54B_V2_ESP32S3Z_WIDTH / 8 + 1)) * EPD_1IN54B_V2_ESP32S3Z_HEIGHT;
  if ((BlackImage = (UBYTE_ESP32S3Z *)malloc(Imagesize)) == NULL) {
    printSerial("Failed to apply for black memory...");
    while (1);
  }
  if ((RedImage = (UBYTE_ESP32S3Z *)malloc(Imagesize)) == NULL) {
    printSerial("Failed to apply for red memory...");
    while (1);
  }
  //free(BlackImage);
  //free(RedImage);
  //BlackImage = NULL;
  //RedImage = NULL;
}

void initEPD()
{
  EPD_1IN54B_V2_ESP32S3Z_Init();
  EPD_1IN54B_V2_ESP32S3Z_Clear();
  DEV_ESP32S3Z_Delay_ms(500);
}

void printPicture(int pictureNumber)
{
  printSerial("..print next picture");
  // 1. init EPD
  initEPD();
  
  // 2. set default picture data
  printSerial("..init picture");
  Paint_NewImage(BlackImage, EPD_1IN54B_V2_ESP32S3Z_WIDTH, EPD_1IN54B_V2_ESP32S3Z_HEIGHT, 270, WHITE);
  Paint_NewImage(RedImage, EPD_1IN54B_V2_ESP32S3Z_WIDTH, EPD_1IN54B_V2_ESP32S3Z_HEIGHT, 270, WHITE);

  // 3. draw picture
  printSerial("..draw picture");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawBitMap(epd_bitmap_allArray[pictureNumber*2]);
  
  Paint_SelectImage(RedImage);
  Paint_Clear(WHITE);
  Paint_DrawBitMap(epd_bitmap_allArray[pictureNumber*2+1]);
  // temporary: add voltage value to red picture
  //Paint_DrawNum(5, 20, vVc, &Font20, BLACK, WHITE);
  //char cstr[16];
  //sprintf (cstr, "%f", vVc);
  //Paint_DrawString_EN(5, 20, cstr, &Font20, BLACK, WHITE);

  EPD_1IN54B_V2_ESP32S3Z_Display(BlackImage, RedImage);

  // 4. go to sleep or power off
  printSerial("..sleep");
  EPD_1IN54B_V2_ESP32S3Z_Sleep();
}

void printChargePicture()
{
  printSerial("..print charge request picture");
  // 1. init ePaper
  initEPD();
  EPD_1IN54B_V2_ESP32S3Z_Clear();

  // 2. set default picture data
  printSerial("..init picture");
  Paint_NewImage(BlackImage, EPD_1IN54B_V2_ESP32S3Z_WIDTH, EPD_1IN54B_V2_ESP32S3Z_HEIGHT, 270, WHITE);
  Paint_NewImage(RedImage, EPD_1IN54B_V2_ESP32S3Z_WIDTH, EPD_1IN54B_V2_ESP32S3Z_HEIGHT, 270, WHITE);

  // 3. draw load image (only red image)
  printSerial("..draw charge picture");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);

  Paint_SelectImage(RedImage);
  Paint_Clear(WHITE);
  Paint_SetRotate(ROTATE_180);
  Paint_DrawRectangle(70, 40, 130, 140, BLACK, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
  Paint_DrawRectangle(75, 115, 125, 135, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(27, 160, "LOW BATTERY", &Font20, WHITE, BLACK);
  
  EPD_1IN54B_V2_ESP32S3Z_Display(BlackImage, RedImage);

  // 4. go to sleep or power off
  printSerial("..sleep");
  EPD_1IN54B_V2_ESP32S3Z_Sleep();
}

void stopEPD()
{
  printSerial("..stop module");
  initEPD();
  //EPD_1IN54B_V2_ESP32S3Z_Clear();
  EPD_1IN54B_V2_ESP32S3Z_Sleep();
  free(BlackImage);
  free(RedImage);
  BlackImage = NULL;
  RedImage = NULL;
  printSerial(">>>END OF OPERATION<<<");
}

void updatePictureCount()
{
  pictureCount += 1;
  if (pictureCount >= MAX_PICTURE_NUMBER)
  {
    pictureCount = 0;
  }
}