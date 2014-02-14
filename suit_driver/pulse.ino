
int pulsestep = 1;
boolean pulse_increase = true;

void pulse() {

    if (millis() > programNextActionTime)
    {
        programNextActionTime = millis() + millisPerProgramStep;
  
        //prepare
        if (pulse_increase)
        {
            pulsestep++;
            if (pulsestep >= num_fades)
            {
                pulsestep = num_fades-2;
                pulse_increase = false;
            }
        }
        else
        {
            pulsestep--;
            if (pulsestep < 0)
            {
                pulsestep = 1;
                pulse_increase = true;
            }
        }
        
        //set all the levels
        for (pin=0 ; pin <= num_levels ; pin++)
          set_level(pin, pulsestep);
    }
}


void pulse_also_old() {
    for (int i=1; i < num_fades; i ++)
        for (pin=0; pin<=num_levels; pin++)
            set_level(pin, i); 
    for (int i=num_fades-2; i>0; i --)
        for (pin=0; pin<=num_levels; pin++)
            set_level(pin, i); 
}


#define pulse_step 148
void pulse_old() {
  for (int i=0; i<3552; i += pulse_step)
      for (pin=0; pin<=num_levels; pin++)
          set_suit_level(pin, 0, i);
  for (int i=3552; i>0; i -= pulse_step)
      for (pin=0; pin<=num_levels; pin++)
          set_suit_level(pin, 0, i);
  clearSuit();
}


//#define pulse_step 148
//void pulse_old() {
//  for (int i=0; i<4096; i += pulse_step)
//  { 
//    for (pin=0; pin<=num_levels; pin++)
//    {
//      set_suit_level(pin, 0, i); 
//    }
//  }
//  for (int i=4095; i>0; i -= pulse_step)
//  { 
//    for (pin=0; pin<=num_levels; pin++)
//    {
//      set_suit_level(pin, 0, i); 
//    }
//  }
//  for (pin=0; pin<=num_levels; pin++)
//    {
//      set_suit_level(pin, 0, 0);           // turn them off!
//    } 
//}

