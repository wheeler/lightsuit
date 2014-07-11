/*************************************************** 
 * I2C For Arduino: SCLOCK -> Analog 5, SDATA -> Analog 4
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


//======= ANALOG ========

// CD4051 mappings
#define cd4051_s0_pin 6
#define cd4051_s1_pin 5
#define cd4051_s2_pin 4

#define acc_left_X_chan 0
#define acc_left_Z_chan 1
#define acc_right_Z_chan 2
#define batt_sense_chan 3
#define acc_right_X_chan 4
#define acc_body_X_chan 5
#define acc_body_Y_chan 6
#define acc_body_Z_chan 7

// Analog input pins
#define acc_left_Y_pin A1  // Left arm Y acceleration
#define acc_right_Y_pin A5  // Right arm Y acceleration

#define cd4051_pin A3      // CD4051 multiplexer output pin

uint8_t analog_1_x = 0;
uint8_t analog_1_y = 0;
uint8_t analog_1_z = 0;

// Set up PCA9685 drivers
Adafruit_PWMServoDriver pwmA = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmB = Adafruit_PWMServoDriver(0x45);
Adafruit_PWMServoDriver pwmC = Adafruit_PWMServoDriver(0x46);

// PCA9685 parameters
#define pca_freq 160


/*---------------
 Suit config:
 Mark: 0
 ????: 1
 ---------------*/
uint8_t suit_config = 0;

// Segment maps
uint8_t segs_leg_R[] = {    11, 10,  9,  8, 47, 46, 45, 44, 43, 42   };   // right leg, crotch to foot
uint8_t segs_leg_L[] = {    41, 40, 39, 38, 37, 36, 35, 34, 33, 32   };   //  left leg, crotch to foot
uint8_t len_legs[] = {    10, 0};    // array of settings for length of the legs
uint8_t len_leg = len_legs[suit_config];

uint8_t segs_arm_R[] = {     6,  5,  4,  3,  2,  1,  0    };   // right arm, armpit to hand
uint8_t segs_arm_L[] = {    31, 30, 29, 28, 27, 26, 25    };   // left  arm, armpit to hand
uint8_t len_arms[] = {    7, 0};    // length of the arms, 7 max
uint8_t len_arm =  len_arms[suit_config];

uint8_t segs_waist[] = { 12 };
#define len_waist 1

uint8_t segs_body[] = {  13, 14, 15, 23, 18, 19, 20  };   // body, hips to neck
#define len_body 7                                               // length of the body

uint8_t segs_head[] = {    21, 22, 17, 24};                               // head, collar to crown
uint8_t len_heads[] = {    4, 0};                                       // length of the head, 0-3
uint8_t len_head = len_heads[suit_config];

uint8_t num_levels = len_leg + len_waist + len_body + len_head;    // length of body (arms down)
uint8_t levels_below_body = len_leg + len_waist;
uint8_t levels_below_head = len_leg + len_waist + len_body;



uint16_t pwms[] = {
};

uint8_t pin = 0;
uint8_t pin_min = 0;
uint8_t pin_max = 47;

int step_delay = 50;

//TODO: RE-SCALE USING REAL_PWM
// MARK PWM CALIBRATION


// these were mark's values which were being RE-interpreted by REAL PWM
//short fadeValues[] = {0, 101, 165, 229, 294, 359, 425, 491, 558, 626, 695, 767, 841, 920, 1005, 1097, 1201, 1321, 1462, 1633, 1846, 2118, 2471, 2936, 3559};
// here are the new values, as if they have been run through REAL PWM
// note the max: 3093. there's not much if any visual difference between that and 4095 so we'll save some power
short fadeValues[] = {0,2,6,12,21,31,44,58,76,95,117,143,172,206,246,293,352,426,521,651,832,1095,1491,2105,3093};


uint8_t led_off = 0;
uint8_t num_fades = 25;
uint8_t led_on = fadeValues[num_fades-1];

//MARK VARS
long programNextActionTime = 0;
boolean sequenceNeedsSetup = true;

short rhythm1_10[] = {24,10, 0,10, 18,10, 0,10, 12,10, 0,10, 6,10, 0,400};
short rhythm1[] =    {24,40, 0,40, 18,40, 0,40, 12,40, 0,40, 6,40, 0,40};
short rhythm2[] =    { 6,40, 0,40, 12,40, 0,40, 18,40, 0,40, 24,40, 0,40, 18,40, 0,40, 12,40, 0,40, 6,40, 0,200};
short amenbass[] =  {24,2,0,2,24,2,0,14,24,1,0,1,24,1,0,9,
                     24,2,0,2,24,2,0,14,24,1,0,1,24,1,0,9,
                     24,2,0,2,24,2,0,14,24,2,0,14,
                     /*4*/    24,1,0, 1,24,1,0,13,24,2,0,10};
short amenSnare[] = {0,8, 24,2, 0,4, 24,2, 0,2, 24,2, 0,4, 24,2, 0,4, 24,2,
                     0,8, 24,2, 0,4, 24,2, 0,2, 24,2, 0,4, 24,2, 0,4, 24,2,
                     0,8, 24,2, 0,4, 24,2, 0,2, 24,2, 0,8, 24,2, 0,4,
                   /*2*/  24,2, 0,4, 24,2, 0,4, 24,2, 0,2, 24,2, 0,8, 24,2, 0,2};
                   
short halfAmenSnare[] = {0,8, 24,2, 0,4, 24,2, 0,2, 24,2, 0,4, 24,2, 0,4, 24,2,
                         0,8, 24,2, 0,4, 24,2, 0,2, 24,2, 0,4, 24,2, 0,4, 24,2};//this sequence is 64 long
short warpRhythm[] = { 8, 20,
                      24, 20,
                      16, 20,
                      12, 20,
                       8, 20,
                       4, 20};
boolean bounceMovingUp[] = {true,false};
short bounceRow[] = {-1, num_levels};

int activeRhythmLength = 0;

uint8_t mode = 3;
uint8_t brightness = 1; //for USB testing I might as well set this to 1



// MSGEQ values
#define eq_reset_pin 10
#define eq_strobe_pin 7
#define eq_output_pin A9
int whichEq = 0;
uint8_t analog_audio = 0;
int spectrumValue[7];


// Tempo values
// TODO: to be accurate about tempo - we may need to go to microseconds
int tempo = 135;
// tempo is bpm. bps = tempo / 60. seconds per beat is 1/(tempo/60). millis per beat is 1000/(tempo/60)
int millisPerBeat;
int programStepsPerBeat = 23; //47 full bounce. 23 for half bounce
int millisPerProgramStep;
boolean tempoChanged = false;
float actualTempo;


uint8_t sequencerType = 0;



//===================================================================================


void tempoChange()
{
    millisPerBeat = 60000 / tempo;
    millisPerProgramStep = ((float)millisPerBeat/programStepsPerBeat) + 0.5 ;
    actualTempo = 60000 / (millisPerProgramStep * programStepsPerBeat);
    
    
    Serial.print("tempo ");
    Serial.println(tempo);
    Serial.print("millisPerBeat ");
    Serial.println(millisPerBeat);
}

int rhythmTotalTime;
int getEndOfRhythmDelay(short rhythm[], short rhythmLength, short multiplier)
{
    rhythmTotalTime = 0;
    for(int i = 1 ; i<rhythmLength ; i+=2)
        rhythmTotalTime += rhythm[i] * multiplier;

    // delay before the next kickoff according to tempo
    if (millisPerBeat > rhythmTotalTime)
    {
//        Serial.print("tempo ");
//        Serial.println(tempo);
//        Serial.print("millis per beat ");
//        Serial.println(millisPerBeat);
//        Serial.print("rhythmtotalmillis ");
//        Serial.println(rhythmTotalTime);
        
        // kick off the next sequence according to tempo
        return millisPerBeat - rhythmTotalTime;
    }
    return 0;
}

//===================================================================================






int get_analog_value(uint8_t channel) {
    uint8_t s0 = (channel >> 0)  & 0x01;
    uint8_t s1 = (channel >> 1)  & 0x01;
    uint8_t s2 = (channel >> 2)  & 0x01;
    digitalWrite(cd4051_s0_pin, s0);
    digitalWrite(cd4051_s1_pin, s1);
    digitalWrite(cd4051_s2_pin, s2);
    return analogRead( cd4051_pin );  // read as input
}

int get_analog_value_s(uint8_t channel, uint8_t samples) {
    uint8_t s0 = (channel >> 0)  & 0x01;
    uint8_t s1 = (channel >> 1)  & 0x01;
    uint8_t s2 = (channel >> 2)  & 0x01;
    digitalWrite(cd4051_s0_pin, s0);
    digitalWrite(cd4051_s1_pin, s1);
    digitalWrite(cd4051_s2_pin, s2);
    int val = 0;
    for (int x=0; x<samples; x++) {
        val += analogRead( cd4051_pin );
    }        
    return val / samples;  // read as input
}
