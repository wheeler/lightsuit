

//accelcenter pointing down = 147
// approx bounce range: 80 - 200 (120 range)
uint8_t rangePerLevel = 120/(num_levels-1);

uint8_t inputBounceLvl     = 12;
uint8_t inputBounceLvlPrev = inputBounceLvl;

long next_accel_bounce_time = 0;

void accel_bounce()
{
    if (millis() > next_accel_bounce_time)
    {
        next_accel_bounce_time = millis() + accelReadSpeed;
        inputBounceLvlPrev = inputBounceLvl;
        
        inputBounceLvl = analog_1_y - 80;
        
        if (inputBounceLvl < 0)
            inputBounceLvl = 0;
        else        
            inputBounceLvl /= rangePerLevel;
        
        if (inputBounceLvl > num_levels-1)
            inputBounceLvl = num_levels-1;
        
        //flip: higher reading = down... so lower level
        inputBounceLvl = -(inputBounceLvl - num_levels+1);
        
        set_level_off(inputBounceLvlPrev);
        set_level_on(inputBounceLvl);
    }
}

int fillBelow = false;
long swaptimer = 0;

void audio_bounce()
{
    if (millis() > next_accel_bounce_time)
    {
        next_accel_bounce_time = millis() + audioReadSpeed;
      
        if (false && millis() > swaptimer)
        {
            fillBelow = !fillBelow;
            swaptimer = millis()+2000;
            clearSuit();
            Serial.println("--------------------");
        }
        
        

        inputBounceLvlPrev = inputBounceLvl;

        // Remap the value to a number between 0 and 24
        inputBounceLvl = map(spectrumValue[whichEq], filterValue[whichEq], 1023, 0, 24);
        
        Serial.print(spectrumValue[whichEq]);
        Serial.print("-");
        Serial.print(filterValue[whichEq]);
        Serial.print("-");
        Serial.println(inputBounceLvl);

        if (fillBelow == 1)
        {
            for (int i = 0 ; i < 24 ; i++)
            {
                if (i <= inputBounceLvl)
                    set_level_on(i);
                else
                    set_level_off(i);
            }
        }
        else
        {
            set_level_off(inputBounceLvlPrev);
            set_level_on(inputBounceLvl);
        }
    }
}
