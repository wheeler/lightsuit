
//program specific resets
void programResets()
{
    boolean up = (mode == PROGRAM_GRAVITY_UP_ID || mode == PROGRAM_SWEEP_UP_ID || mode == PROGRAM_DOUBLE_UP_ID);
    boolean down = (mode == PROGRAM_GRAVITY_DOWN_ID || mode == PROGRAM_SCATTER_DOWN_ID || mode == PROGRAM_DOUBLE_DOWN_ID);
    boolean upanddown = (mode == PROGRAM_BOUNCE_ID || mode == PROGRAM_GRAVITY_BOUNCE_ID || mode == PROGRAM_DOUBLE_BOUNCE_ID );
    boolean oppositeDouble = (mode == PROGRAM_DOUBLE_BOUNCE_ID);
    boolean sameDouble = (mode == PROGRAM_DOUBLE_UP_ID || mode == PROGRAM_DOUBLE_DOWN_ID);
    boolean fadeTempo = (mode == PROGRAM_PULSE_ID);

	//normal up-down bounces & up-sweeps
    if (up || upanddown)
        bounceMovingUp[0] = true;
        
    //down sweeps
    if (down)
        bounceMovingUp[0] = false;
    
    //doubles moving in opposite direction
    if (oppositeDouble)
    {
        bounceMovingUp[1] = !bounceMovingUp[0];
        bounceRow[0] = -1;
        bounceRow[1] = num_levels;
    }

    //doubles moving in the same direction
    if (sameDouble)
    {
        bounceMovingUp[1] = bounceMovingUp[0];
        bounceRow[0] = -1;
        bounceRow[1] = num_levels/2;
    }
    
    if (mode == PROGRAM_SWEEP_DOWN_ID)
        sequencerType = SWEEPDOWN;    
    if (mode == PROGRAM_SWEEP_UP_ID)
        sequencerType = SWEEPUP;    
    if (mode == PROGRAM_SCATTER_DOWN_ID)
        sequencerType = SCATTERDOWN;    
    if (mode == PROGRAM_WARP_ID)
        sequencerType = WARP;
    
    //might as well always reset the sequencer
    sequenceNeedsSetup = true;
    
    
    if (mode == fadeTempo)
        programStepsPerBeat = num_fades*2 - 1; //full fade up and down   
    else
        programStepsPerBeat = 23; //47 full bounce. 23 for half bounce
        
    tempoChange();
}

