/*********************************************************************
 * I2C For Arduino: SCLOCK -> Analog 5, SDATA -> Analog 4
*********************************************************************/

#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#define OLED_RESET 4
// PCB w/ arduino pro mini pins
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);

/*
#define rot1_up_pin 6        // rot encoder 1 up pin
#define rot1_down_pin 7      // rot encoder 1 down pin
#define rot1_button_pin 3      // rot encoder 1 down pin
*/

// PCB w/ arduino pro mini pins
#define rot1_up_pin 9        // rot encoder 1 up pin
#define rot1_down_pin 11      // rot encoder 1 down pin
#define rot1_button_pin 10      // rot encoder 1 down pin
#define left_button_pin 7      // rot encoder 1 down pin
#define right_button_pin 8      // rot encoder 1 down pin









//LED LEVELS DATA
const int numberLevels = 21;
short levels[numberLevels];







