## Basic Operation Instruction

A set of different pictures is stored on the ESP32 microcontroller. They are displayed on the ePaper one after another in a loop. Each image is displayed for 200 seconds (the time can be changes in teh code). The electronics are powered by a LiPo battery. When the charge of the battery becomes low, the display shows a warning. Before the battery is empty, the operation is stopped and the display is cleared.

<img src="../img/default.JPG" height="200">     <img src="../img/control.JPG" height="200">     <img src="../img/1.1.gif" height="200">

**Power on**

There is a power on/off switch on the back of the device. When the switch is turned on, the photo frame starts the loop through the images. When charging the device, it is recommended to turn the power switch off.

          

**Clear display**

The button on the back of the device triggers an interrupt event that clears the display and stops the operation of the photo frame. This function is to clear the display before turning the power off. It is a recommendation of the manufacturer of the ePaper display to clear the display when turning it off for a longer time (more then 24 hours).

**Charge device**
On the side of the photo frame is a micro USB charging port. When charging, a red LED is on. When the battery is fully charged, a green LED is on. When charging, it is recommended to turn the device off with the power switch.

## Hardware

The photo frame has been build with the following IoT components:
- Waveshare 1.54 inch ePaper display B version 2 with colors black, red, white
- Waveshare ESP32-S2-Zero microcontroler
- D1 mini power supply module (3.7 volt LiPo batterycharger and 5 V step-up converter)
- 3.7 V LiPo battery 

**Pinout of the Pico WH and connection of components**

<img src="../img/pinout.png" height="170">

**Figure of the electronics setup**

<img src="../img/electronics.JPG" height="220">

**Figure of the controls**

<img src="../img/control.JPG" height="105">



## software

The software was developped and uploaded with the Arduino IDE 2.3.2 by Arduino using the following libraries:

- ...

The main code file is iot-si-balance.ino. The loop function implements a finite automate with different behaviour based on the function status (Measurement, Uncertainty, Adjustment 1&2). But basically, it is running updates of the display and checking inputs from the buttons. There is also a flag to set DEBUG mode that provide more data through the serial port. 

The serial port is running on 115200 baude.
