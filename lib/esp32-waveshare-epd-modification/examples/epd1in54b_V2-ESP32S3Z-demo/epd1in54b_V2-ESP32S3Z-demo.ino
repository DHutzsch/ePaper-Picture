/* Includes ------------------------------------------------------------------*/
#include "DEV_Config_ESP32_S3_Zero.h"
#include "EPD_klein.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>

/* Entry point ----------------------------------------------------------------*/
void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial.println("1IN54 B V2 ESP32-S3-Zero Demo");
  DEV_ESP32S3Z_Module_Init();

  Serial.println("e-Paper Init and Clear...");
  EPD_1IN54B_V2_ESP32S3Z_Init();
  EPD_1IN54B_V2_ESP32S3Z_Clear();
  DEV_ESP32S3Z_Delay_ms(500);

  //Create a new image cache
  UBYTE_ESP32S3Z *BlackImage, *RedImage;
  UWORD_ESP32S3Z Imagesize = ((EPD_1IN54B_V2_ESP32S3Z_WIDTH % 8 == 0) ? (EPD_1IN54B_V2_ESP32S3Z_WIDTH / 8 ) : (EPD_1IN54B_V2_ESP32S3Z_WIDTH / 8 + 1)) * EPD_1IN54B_V2_ESP32S3Z_HEIGHT;
  if ((BlackImage = (UBYTE_ESP32S3Z *)malloc(Imagesize)) == NULL) {
    Serial.println("Failed to apply for black memory...");
    while (1);
  }
  if ((RedImage = (UBYTE_ESP32S3Z *)malloc(Imagesize)) == NULL) {
    Serial.println("Failed to apply for red memory...");
    while (1);
  }
  Serial.println("NewImage: BlackImage and RedImage");
  Paint_NewImage(BlackImage, EPD_1IN54B_V2_ESP32S3Z_WIDTH, EPD_1IN54B_V2_ESP32S3Z_HEIGHT, 270, WHITE);
  Paint_NewImage(RedImage, EPD_1IN54B_V2_ESP32S3Z_WIDTH, EPD_1IN54B_V2_ESP32S3Z_HEIGHT, 270, WHITE);

#if 1  //show image for array
  Serial.println("show image for array------------------------");
  Paint_SelectImage(BlackImage);
  Paint_DrawBitMap(gImage_1in54b_Black);

  Paint_SelectImage(RedImage);
  Paint_DrawBitMap(gImage_1in54b_Red);

  EPD_1IN54B_V2_ESP32S3Z_Display(BlackImage, RedImage);
  DEV_ESP32S3Z_Delay_ms(2000);
#endif
#if 1   // Drawing on the image
  Serial.println("Drawing------------------------");
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
  Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
  Paint_DrawLine(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawLine(70, 10, 20, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
  Paint_DrawRectangle(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawCircle(170, 85, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(5, 70, "hello world", &Font16, WHITE, BLACK);
  Paint_DrawString_CN(5, 160, "微雪电子", &Font24CN, WHITE, BLACK);

  Paint_SelectImage(RedImage);
  Paint_Clear(WHITE);
  Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
  Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);
  Paint_DrawLine(170, 15, 170, 55, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawLine(150, 35, 190, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  Paint_DrawRectangle(85, 10, 130, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawCircle(170, 35, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
  Paint_DrawString_EN(5, 90, "waveshare", &Font20, BLACK, WHITE);
  Paint_DrawNum(5, 120, 123456789, &Font20, BLACK, WHITE);
  Paint_DrawString_CN(5, 135, "你好abc", &Font12CN, BLACK, WHITE);

  EPD_1IN54B_V2_ESP32S3Z_Display(BlackImage, RedImage);
  DEV_ESP32S3Z_Delay_ms(2000);
#endif

  Serial.println("Clear...");
  EPD_1IN54B_V2_ESP32S3Z_Clear();

  Serial.println("Goto Sleep...");
  EPD_1IN54B_V2_ESP32S3Z_Sleep();
  free(BlackImage);
  free(RedImage);
  BlackImage = NULL;
  RedImage = NULL;

}

/* The main loop -------------------------------------------------------------*/
void loop()
{
  //
}
