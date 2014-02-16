
// "OFF" program. Turn all levels off once, do nothing else.
void off()
{
  if (sequenceNeedsSetup)
  {
    clearSuit();
    sequenceNeedsSetup = false;
  }
}


/**
 * BRIGHTNESS-AWARE set level methods
 *
 * Overall Suit Brightness is defined as a number between 1 and 10. This is stored in global
 * variable "brightness". Programs use brightness commands with numbers 0 - 24. These methods
 * combine the global brightness and the program brightness to evaluate a correct brightness.
 *
 * Only these three functions should be used by programs to make their effects:
 *
 * set_level(int level, int zeroToTwentyFour)
 *   set a suit level to a program brightness from 0 to 24
 *
 * set_level_on(int level)
 *   readable shorthand for set_level(level,24);
 *
 * set_level_off(int level)
 *   readable shorthand for set_level(level,0)
 *
 **/

// attempt to reduce peak current by PWMing even rows in the front of 
#define timeShare true

void set_level(uint8_t level, int zeroToTwentyFour)
{
    if (timeShare && level%2 == 1)
        set_suit_level(level, 4095 - getBrightness(zeroToTwentyFour), 4095);
    else
        set_suit_level(level, 0, getBrightness(zeroToTwentyFour));
}

void set_level_on(uint8_t level)
{
    set_level(level, 24);
}

void set_level_off(uint8_t level)
{
    set_level(level, 0);
}


//===================================================================================

//step through all each level on all three pwms and turn it on and off
void bootSuit()
{
    // Set all outputs low... is this necessary?
    for (pin=0;pin<16;pin++) {
        pwmA.setPWM(pin, 0, led_on);      
        pwmB.setPWM(pin, 0, led_on);      
        pwmC.setPWM(pin, 0, led_on);
        delay(150);
        pwmA.setPWM(pin, 0, 0);      
        pwmB.setPWM(pin, 0, 0);      
        pwmC.setPWM(pin, 0, 0);
    }
}

// turn all levels off
void clearSuit()
{
    for (pin=0;pin<16;pin++) {
        pwmA.setPWM(pin, 0, 0);      
        pwmB.setPWM(pin, 0, 0);      
        pwmC.setPWM(pin, 0, 0);
    }
}

//===================================================================================



//------------------------------------------------
// INTERNAL FUNCTIONS
//------------------------------------------------

// get actual brghtness combining the program brightness looked up in fadeValues using index 0-24 and
// the global brightness 1-10
int getBrightness(int zeroToTwentyFour)
{
    if (brightness == 10)
        return fadeValues[zeroToTwentyFour];
    return fadeValues[zeroToTwentyFour] * ((float)brightness / 10.0); //TODO can this math be faster?
}


// Set an individual LED Strip by ID (not a whole level, just a strip).
// Strip IDs here are 0-47. 0-15 are on PWM A, 16-31 are on PWM B, and 32-
void set_strip(uint8_t i_strip, int startTime, int endTime) {
  if (i_strip/16 == 0)
    pwmA.setPWM(i_strip%16, startTime, endTime);
  else if (i_strip/16 == 1)
    pwmB.setPWM(i_strip%16, startTime, endTime);
  else if (i_strip/16 == 2)
    pwmC.setPWM(i_strip%16, startTime, endTime);
}


// Pin variables for testing
int level=0;
int level_leg=0;    // level of leg, crotch to foot
int level_waist=0;  // level of body, hips up
int level_body=0;   // level of body, hips to neck
int level_arm=0;    // level of arm, armpit to hand
int level_head=0;   // level of head, collar to crown

boolean debugLevels = false;

//TODO: rename to test for useages - TODO: i think this is done?
// Set a whole suit level. Resolves which strips belong in the level and sets them.
void set_suit_level(uint8_t level, int startTime, int endTime) {
    if (level > num_levels) return;
    // Calculate levels of different body sections
    level_leg = len_leg - (level + 1);
    level_waist = level - len_leg;
    level_body = level - len_leg - 1;
    level_head = level - (len_leg + len_waist + len_body);
    level_arm = 7 - (level + 1 - len_waist - len_leg);
    
    if (debugLevels)
    {    
        Serial.print("level ");
        Serial.print(level);
        Serial.print(":");
    }

    // Convert PWM value
    //endTime = realPWM(endTime);

    // Display levels
    if (level_leg >= 0 && level_leg < len_leg) {
        if (debugLevels)
        {    
            Serial.print("   leg[");
            Serial.print(level_leg);
            Serial.print("]");
        }
        set_strip(segs_leg_L[level_leg], startTime, endTime);
        set_strip(segs_leg_R[level_leg], startTime, endTime);
    }
    if (level_waist >= 0 && level_waist < len_waist) {
        if (debugLevels)
        {    
            Serial.print("  waist[");
            Serial.print(level_waist);
            Serial.print("]");
        }
        set_strip(segs_waist[level_waist], startTime, endTime);
    }
    if (level_body >= 0 && level_body < len_body) {
        if (debugLevels)
        {    
            Serial.print("  body[");
            Serial.print(level_body);
            Serial.print("]");
        }
        set_strip(segs_body[level_body], startTime, endTime);
    }
    if (level_head >= 0 && level_head < len_head) {
        if (debugLevels)
        {    
            Serial.print("  head[");
            Serial.print(level_head);
            Serial.print("]");
        }
        set_strip(segs_head[level_head], startTime, endTime);
    }
    if (level_arm >= 0 && level_arm < len_arm) {
        if (debugLevels)
        {    
            Serial.print("  arm[");
            Serial.print(level_arm);
            Serial.print("]");
        }
        set_strip(segs_arm_R[level_arm], startTime, endTime);
        set_strip(segs_arm_L[level_arm], startTime, endTime);
    }
    if (debugLevels)
        Serial.println();

}

//===================================================================================
// Brightness level conversion
float bright_exp = 2.0;  // exponent for simulating gamma

int realPWM(int pwm) {
    float x = pwm * 1.0 / 4095;
    x = pow(x, bright_exp);
    x = x * 4095;
    return int(x);
}


//===================================================================================


#define fade1_step 32
void fade_in_1() {
    for (pin=pin_min; pin<=pin_max; pin++) {
        for (int i=0; i<4096; i += fade1_step) { 
            set_strip(pin, 0, i); 
            delay(1); 
        }
    }
    for (pin=pin_min; pin<=pin_max; pin++) {
        for (int i=4095; i>0; i -= fade1_step) { 
            set_strip(pin, 0, i); 
            delay(1); 
        }
        set_strip(pin, 0, 0);           // turn them off!
    }
}



#define flash_step 64
void flash(uint8_t reps) {
    for (uint8_t rep=0; rep<reps; rep++) {

        for (int i=0; i<4096; i += flash_step) { 
            for (pin=pin_min; pin<=pin_max; pin++) {
                set_strip(pin, 0, i); 
            }
            delay(1);
        }
        for (int i=4095; i>0; i -= flash_step) { 
            for (pin=pin_min; pin<=pin_max; pin++) {
                set_strip(pin, 0, i); 
            }
            delay(1); 
        }
        // turn them off!
        for (pin=pin_min; pin<=pin_max; pin++) {
            set_strip(pin, 0, 0); 
        }
    }
}



void display_gradient(uint8_t lvl) {

    // Gradient fade
    //Serial.print(lvl);
    //Serial.print(":  { ");
    // Compute brightnesses
    for (uint8_t i=0; i<num_levels; i++) {
        long b = 0;
        if (i<=level)
            b = (4095 * (long(i)+1)) / (lvl+1);
        else
            b = 4096 * (6*(num_levels-long(i))) / (6*(num_levels-long(lvl)));
        //Serial.print(int(b));
        //Serial.print(", ");
        set_suit_level(i, 0, b);
    }
    //Serial.println(" }");
    delay(step_delay);

}

