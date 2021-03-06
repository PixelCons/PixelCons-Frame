# PixelCons-Frame
Pixel Art Showcase Frame

![Example](https://raw.githubusercontent.com/PixelCons/PixelCons-Frame/master/doc/img1.jpg)

The PixelCon Frame is small device that displays pixel art (known as PixelCons) from the web. The pixel art is displayed on a bright 8x8 matrix of LEDs and is powered by the inexpensive WiFi enabled esp8266 board. Everything is enclosed in a 2.75in square 3D printed case.

Pixel art displayed on the frame comes from the PixelCon ecosystem on the Ethereum blockchain. Anyone can make and explore PixelCon and using the power of the Ethereum blockchain, each PixelCon can be owned, collected, and traded like a cryptocurrency.

Refer to the User Guide [here](https://github.com/PixelCons/PixelCons-Frame/blob/master/doc/PixelCon%20Frame%20(mini).pdf) for more information on using/setting up the PixelCon Frame once it's been assembled.

## Hardware
The PixelCon Frame consists of two main components, the NodeMCU ESP8266 microcontroller dev board and an 8x8 matrix of WS2812 LEDs. Other smaller passive components needed include an electrolytic capacitor, n-channel transistor and a single resistor.

- NodeMCU ESP8266 ([Amazon](https://www.amazon.com/NodeMCU-ESP8266-Internet-ESP-12E-Development/dp/B074Z2VL6S/ref=sr_1_10?crid=XF6CTQ0Q3GH0&keywords=esp8266+nodemcu&qid=1552268293&s=gateway&sprefix=esp8266+%2Caps%2C774&sr=8-10))
- 8x8 WS2812 LEDs ([Amazon](https://www.amazon.com/Semoic-Matrix-WS2812-Full-Color-Arduino/dp/B07M6D5X34/ref=sr_1_1?keywords=8x8+ws2812&qid=1552268625&s=gateway&sr=8-1))
- 5V 3A Power Supply ([Amazon](https://www.amazon.com/Bestcompu-Converter-Wireless-Switches-Video%EF%BC%885-5mm/dp/B00ME78NSS/ref=sr_1_1?keywords=5v+3+amp+power+supply+5.5&qid=1552270418&s=gateway&sr=8-1))
- NPN Transistor
- DC Barrel Jack
- 8pin Female Headers (x2)
- 1000uF Capacitor
- 2.6kOhm Resistor

![Schematic](https://raw.githubusercontent.com/PixelCons/PixelCons-Frame/master/doc/schematic.png)

## Software
All software for the PixelCon Frame is run on the ESP8266 microcontroller and was designed to use the Arduino IDE for flashing the code. To flash the code to the NodeMCU ESP8266 board, follow these steps:

1. Download and install the arduino IDE [here](https://www.arduino.cc/en/Main/Software).
2. Add the ESP8266 boards to the Arduino IDE by following this [tutorial](https://www.instructables.com/id/Programming-ESP8266-ESP-12E-NodeMCU-Using-Arduino-/).
3. Download the source code [here](https://codeload.github.com/PixelCons/PixelCons-Frame/zip/master) and unzip into a folder labeled ‘PixelCon-Frame’. 
4. Add the WiFi Manager library development branch to the Arduino IDE by downloading it [here](https://codeload.github.com/tzapu/WiFiManager/zip/development) and unzip into a folder labeled ‘WiFiManager’ in the directory ‘Documents\Arduino\libraries’. 
5. Open the PixelCons-Frame.ino file in the Arduino IDE and click the ‘Verify’ button to make sure everything compiles successfully. Refer back to the earlier tutorial [here](https://www.instructables.com/id/Programming-ESP8266-ESP-12E-NodeMCU-Using-Arduino-/) for uploading the code to the ESP8266 on the NodeMCU dev board.

Packed inside of the code is the web interface for configuring the behavior of the PixelCon Frame. Refer to the User Guide [here](https://github.com/PixelCons/PixelCons-Frame/blob/master/doc/PixelCon%20Frame%20(mini).pdf) for an explanation of using the software.

![WebUI](https://raw.githubusercontent.com/PixelCons/PixelCons-Frame/master/doc/webui.png)

## Assembly
The PixelCon Frame body can be 3D printed from the STL files found [here](https://github.com/PixelCons/PixelCons-Frame/tree/master/stl) in the stl folder. To make your own, simply print them out and follow these assembly steps:

1. Place a cut piece of paper in between the 'frame' and the 'front' prints and snap in place.
2. The ESP8266 board should be screwed into into the 'backplate' with the 'buttons' in place. 
3. Super glue the 'bracket' onto the back of the LED matrix with all of the components in place. 
4. Wire and solder the correct components together according to the schematic.
5. Hot glue the LED matrix into the 'frame' so that the DC jack lines up with the hole in the 'frame'. 
6. Push the 'backplate' into place at the back of the 'frame', seating the ESP8266 pins into the female headers.

![Schematic](https://raw.githubusercontent.com/PixelCons/PixelCons-Frame/master/doc/breakdown.jpg)

## What's Next?
Currently, there is only the mini design, but it should be possible to create larger or even smaller versions and add features like an internal battery. Look forward to future software updates and more hardware revisions. 

Remember to check the User Guide [here](https://github.com/PixelCons/PixelCons-Frame/blob/master/doc/PixelCon%20Frame%20(mini).pdf) for more information on how to use the PixelCon Frame.
