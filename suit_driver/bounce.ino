

//sqrt(2/9.8*x*(h/s)) solve for h=1.5, s=23 , x = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23]
//{115, 163, 200, 231, 258, 283, 305, 326, 346, 365, 383, 400, 416, 432, 447, 461, 476, 489, 503, 516, 529, 541, 553}
//{115, 163, 200, 231, 258, 283, 305, 326, 346, 365, 383, 400, 416, 432, 447, 461, 476, 489, 503, 516, 529, 541, 553}
uint8_t gravityTimes[] = {115,  48,  37,  31,  27,  25,  22,  21,  20,  19,  18,  17,  16,  16,  15,  14,  14,  13,  13,  13,  13,  12,  12};


//TODO: N-bounce
//TODO: N-Gravity bounce (position sequencer?)
//TODO: N-bounce with small range

void bounce(uint8_t type, boolean doubleBounce)
{
//    step_delay = 10; //5 is the minimum for this program where it is distinct
    
    if (millis() > programNextActionTime)
    {
        for (int i=0; (doubleBounce && i<2) || i==0 ;i++)
        {
          if (!(doubleBounce && (i == 1 && bounceRow[i-1] == bounceRow[i])))
              set_level_off(bounceRow[i]); //turn off the row we last visited
          if (bounceMovingUp[i])
          {
              bounceRow[i]++;
              if (bounceRow[i] >= num_levels)
              {
                  if (type == GRAVITYUP)
                      bounceRow[i] = 0;
                  else
                  {
                      bounceMovingUp[i] = false;
                      bounceRow[i] -= 2;
                  }
              }
          }
          else
          {
            bounceRow[i]--;
            if (bounceRow[i] < 0)
            {
                if (type == GRAVITYDOWN)
                    bounceRow[i] = num_levels - 1;
                else
                {
                    bounceMovingUp[i] = true;
                    bounceRow[i] += 2;
                }
            }
          }
          set_level_on(bounceRow[i]);
       }
       if (type == GRAVITY || type == GRAVITYDOWN || type == GRAVITYUP)
           programNextActionTime = millis() + gravityTimes[num_levels - 1 - bounceRow[0]];
       else
           programNextActionTime = millis() + millisPerProgramStep;
    }
}


void gradientBounce()
{
    // Gradient fade up & down
    step_delay = 10;
    for (int i=0; i<2; i++) {
        for (level=0; level<num_levels; level++) {
            display_gradient(level);
            delay(step_delay);
        }
        for (level=num_levels-2; level>=0; level--) {
            display_gradient(level);
            delay(step_delay);
        }
    }
}
