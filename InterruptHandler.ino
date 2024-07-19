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

/**
 *  Method called when interrupt
 */
void IRAM_ATTR isr() {
 interruptDetected = true;
}

void deactivateInterrupt()
{
  detachInterrupt(InterruptPin);
}

void activateInterrupt()
{
  attachInterrupt(InterruptPin, isr, RISING);
}

/**
 * Method stopping operation of device
 */
void clearInterrupt()
{
  if (interruptDetected){
    // deactivate interrupt to prevent button bouncing ;-)
    deactivateInterrupt();

    printSerial("..stop interrupt");
    interruptDetected = false;

    // change state to STOP mode and stop device
    mode = STOPED;
    stopEPD();
    // workaround to test charge mode
    //mode = CHARGE;
    //printChargePicture();
    //activateInterrupt();

    delay(100);

    // acivate interrupt again
    //activateInterrupt();
  }
}

void devDelay(int seconds)
{
  for (int j=0; j < seconds; j++)
  {
    if (mode == ACTIVE || mode == CHARGE)
    {
      // wait one second
      printSerial("..");
      printSerial(seconds-j);
      delay(1000);
     
      // interrupt handling
      clearInterrupt();
    }
    else
    {
      delay(1000);
      return;
    }
  }
}