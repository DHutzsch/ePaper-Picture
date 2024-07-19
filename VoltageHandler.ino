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

void checkVoltage()
{
  // we have three readings and build the arithmetic mean for more stable result
  int v1 = analogRead(VOLT_VCC_PIN);
  delay(100);
  int v2 = analogRead(VOLT_VCC_PIN);
  delay(100);
  int v3 = analogRead(VOLT_VCC_PIN);
  // arithmetic mean
  vVc = (int) (v1 + v2 + v3) / 3.;

  printSerial("..voltage adc value ");
  printSerial(vVc);
  // wenn vVc unter 2000 sinkt, dann ist Akku leer
  // daher bei 2050 Ausschalten und bei 2100 Akku Warnung anzeigen
}