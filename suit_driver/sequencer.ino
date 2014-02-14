
//==== Sequencer Stuff =================
long levelNextActionTimes[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //num_levels of them
//todo: encode motion? encode triggering? I need to get dynamic assignment of arrays!
uint8_t levelRhythmIndex[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //num_levels of them
int sequenceDelay = 100;
short scatterModulus = 2;
short endOfSequenceDelay;
long now;
int i;
int sequencerDelayMultiplier = 10;
//======================================

void sequencer(short rhythm[], short rhythmLength)
{
    
  
    if (sequenceNeedsSetup) //setup the sequence
        sequencerSetup(rhythm, rhythmLength);

    now = millis();
    boolean action = false;
    for (i=0 ; i < num_levels ; i++)
    {
        if (now > levelNextActionTimes[i])
        {
            //Serial.print(now); Serial.print(" action on level "); Serial.print(i);
            if (levelRhythmIndex[i] >= rhythmLength)  //rhythm has run out
            {
                //Serial.println(" end of rhythm");
                if (sequencerType == WARP)
                    //set_suit_level(i, 0, fadeValues[2]);
                    set_level(i, 2);
                else
                    //set_suit_level(i, 0, 0);
                    set_level(i, 0);
                levelRhythmIndex[i] = 0;
                levelNextActionTimes[i] += endOfSequenceDelay; //note: does not query millis to maintain syncronization of levels
            }
            else
            {
                //Serial.print(" rhythm idx "); Serial.println(levelRhythmIndex[i]);
                //set_suit_level(i, 0, rhythm[levelRhythmIndex[i]]);
                set_level(i, rhythm[levelRhythmIndex[i]]);
                levelRhythmIndex[i]++;
                levelNextActionTimes[i] += rhythm[levelRhythmIndex[i]] * sequencerDelayMultiplier;  //note: does not query millis to maintain syncronization of levels
                levelRhythmIndex[i]++;
            }
        }
    }

}


void sequencerSetup(short rhythm[], short rhythmLength)
{
    //Serial.println("sequence setup");
    step_delay = 0;
    now = millis();
    
    if (sequencerType == WARP)
    {
        step_delay = 200;
        for (i=0 ; i < num_levels ; i++)
        {
            if (i <= num_levels/2)
                levelNextActionTimes[i] = now + ((num_levels/2 - i)/2) * step_delay;
            else
                levelNextActionTimes[i] = now + ((i - num_levels/2 )/2) * step_delay;
            //Serial.print(i); Serial.print('-');Serial.println(levelNextActionTimes[i]);
        }
        //endOfSequenceDelay = num_levels/4 * step_delay; //the amount of time it takes for the rest of the levels to complete the sequence
        endOfSequenceDelay = getEndOfRhythmDelay(rhythm, rhythmLength, sequencerDelayMultiplier);
        //i had a good glitch sequence when when endOfSequenceDelay was 120 and rhythm steps were 10ms (and we were doing only one row)?
    }
    else if (sequencerType == SWEEPDOWN || sequencerType == GRAVITYDOWN || sequencerType == SCATTERDOWN)
    {
        for (i=0 ; i < num_levels ; i++)
        {
            if (sequencerType == SCATTERDOWN)              
                levelNextActionTimes[num_levels - (i + 1)] = now + ((i / scatterModulus + scatterModulus - (i % scatterModulus)) * sequenceDelay); // progressive start time slightly scattered
            else
                levelNextActionTimes[num_levels - (i + 1)] = now + (i * sequenceDelay); // progressive start time
        }
        endOfSequenceDelay = 640*2;
    }
    else // UP
    {
        for (i=0 ; i < num_levels ; i++)
            levelNextActionTimes[i] = now + (i * sequenceDelay); // progressive start time
        endOfSequenceDelay = step_delay*8;
    }

    for (i=0 ; i < num_levels ; i++)
        levelRhythmIndex[num_levels - (i + 1)] = 0;
        
    if (step_delay == 0)
        step_delay = 120;

    sequenceNeedsSetup = false;
}
