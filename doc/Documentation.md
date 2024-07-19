## Basic Operation Instruction

The balance has a load-cell to measure the value of weight by putting the weights on the little tray on top of the load cell (HX711 load-cell). The measured values and current values of loads on the tray are shown on the gauge on a LCD display. Also the values of air temperature and humidity close to the load-cell are displayed (values from DHT 22 sensor). 

**Op 1**

lorem ipsum

<img src="../img/1.1.gif" height="180">          

**Op2**

lorem ipsum

## Hardware

The photo frame has been build with the following IoT components:
- ...


**Pinout of the Pico WH and connection of components**

<img src="../img/pinout.JPG" height="170">

**Figure of the electronics setup**

<img src="../img/electronics.JPG" height="220">

**Figure of the controls**

<img src="../figures/controls.JPG" height="105">



## software

The software was developped and uploaded with the Arduino IDE 2.3.2 by Arduino using the following libraries:

- ...

The main code file is iot-si-balance.ino. The loop function implements a finite automate with different behaviour based on the function status (Measurement, Uncertainty, Adjustment 1&2). But basically, it is running updates of the display and checking inputs from the buttons. There is also a flag to set DEBUG mode that provide more data through the serial port. 

The serial port is running on 115200 baude.
