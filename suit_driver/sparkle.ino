


uint8_t rhythmIndex = 0;

uint8_t sparkleRow = 0;
uint8_t minimumMotion = 2;
int rhythmLength;

void sparkle()
{
    if (millis() > programNextActionTime)
    {
        rhythmLength = sizeof(rhythm1)/sizeof(short);
        if (rhythmIndex >= rhythmLength)
        {
            //unset the last sparkle row in case it hasn't been
            set_level_off(sparkleRow);
            
            // pick a new row to use
            int nextRow = -1;
            do {
                nextRow = random(num_levels-1); // keep getting randoms until random is new
            } while (nextRow > sparkleRow-minimumMotion && nextRow < sparkleRow+minimumMotion);
    
            sparkleRow = nextRow;
            rhythmIndex = 0;
            
            int nextDelay = getEndOfRhythmDelay(rhythm1, rhythmLength, 1);
            if (nextDelay > 0)
            {
                // kick off the next sequence according to tempo
                programNextActionTime = millis() + nextDelay;
                return;
            }
            //else tempo is to fast for the rhythm - just keep going.
        }
        
        //set the brightness according to the rhythm
        set_level(sparkleRow, rhythm1[rhythmIndex]);
        rhythmIndex++;
        //set the next action according to the rhythm
        programNextActionTime = millis() + ((rhythm1[rhythmIndex]));
        rhythmIndex++;
    }
}

