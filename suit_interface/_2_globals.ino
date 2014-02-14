
unsigned char interfaceState = 0; //start with the program list



//ROTARY encoder /w button inputs
boolean rot1_down = HIGH;
boolean rot1_down_last = HIGH;
long nextRotaryCheck = 0;    // next time we should check the rotary
short rotaryValue = 0;    // value to test dial
short rotaryLast = 0;  // last value
short rotaryCap = number_of_programs - 1;
short rotaryIncrement = 1;
boolean rotaryButtonPress = false;
long nextButtonCheck = 0;



//STORED INTERFACE DATA
short programModeRotary = 0;
short programModeScroll = 0;
short propertyModeRotary = 1;

boolean displayInvalid = true;



int batteryLife = 100;

int program=0;

