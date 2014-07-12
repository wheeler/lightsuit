lightsuit
=========

Arduino for driving and controlling a custom LED lightsuit.

The suit has two Arduino units, a Leonardo which drives the LEDs and a mini which drives the OLED-based user interface. They talk serial to each other. This is repository is two Arduino Projects, one set of code for each Arduino.

**suit_driver** is the code to drive the LEDs. All the programming which controls the visuals is here. It is written for Leonardo (which has some different pins & has two serial ports, one hardware and one software).

    requires Adafruit_PWMServoDriver library

**suit_interface** is the code to run the oled / rotary encoder interface Arduino.

    requires Adafruit_GFX and Adafruit_SSD1306 libraries
    
[![Light Suit](http://img.youtube.com/vi/DWLvp8Tb-pU/0.jpg)](http://www.youtube.com/watch?v=DWLvp8Tb-pU)
