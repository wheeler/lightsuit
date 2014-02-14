void loop() {

  checkSerial();
  checkInputs();
  
  switch (mode)
  {
      case PROGRAM_OFF_ID:
          off();
          break;
      case PROGRAM_FLICKER_ID:
          flicker();
          break;
      case PROGRAM_WHITENOISE_ID:
          whiteNoise();
          break;
      case PROGRAM_PULSE_ID:
          pulse();
          break;
      case PROGRAM_SPARKLE_ID:
          sparkle();
          break;
      case PROGRAM_GRADIENT_BOUNCE_ID:
          gradientBounce();
          break;
      case PROGRAM_BOUNCE_ID:
          bounce(NORMAL, SINGLE_BOUNCE);
          break;
      case PROGRAM_GRAVITY_DOWN_ID:
          bounce(GRAVITYDOWN, SINGLE_BOUNCE);
          break;
      case PROGRAM_GRAVITY_BOUNCE_ID:
          bounce(GRAVITY, SINGLE_BOUNCE);
          break;
      case PROGRAM_GRAVITY_UP_ID:
          bounce(GRAVITYUP, SINGLE_BOUNCE);
          break;

      case PROGRAM_SWEEP_DOWN_ID:
          sequencer(halfAmenSnare, sizeof(halfAmenSnare)/sizeof(short));
          break;
      case PROGRAM_SWEEP_UP_ID:
          sequencer(halfAmenSnare, sizeof(halfAmenSnare)/sizeof(short));
          break;
      case PROGRAM_SCATTER_DOWN_ID:
          sequencer(halfAmenSnare, sizeof(halfAmenSnare)/sizeof(short));
          break;
      case PROGRAM_WARP_ID:
          sequencer(warpRhythm, sizeof(warpRhythm)/sizeof(short));
          break;

      case PROGRAM_DOUBLE_BOUNCE_ID:
          bounce(NORMAL, DOUBLE_BOUNCE);
          break;          
      case PROGRAM_DOUBLE_UP_ID:
          bounce(SWEEPUP, DOUBLE_BOUNCE);
          break;    
      case PROGRAM_DOUBLE_DOWN_ID:
          bounce(SWEEPDOWN, DOUBLE_BOUNCE);
          break;
          
      case PROGRAM_BOOT_ID:
          bootSuit();
          break;
          
          
      case PROGRAM_ACCEL_BOUNCE_ID:
          accel_bounce();
          break;
      case PROGRAM_VU_METER_ID:
          audio_bounce();
          break;
          
      case 99:
          testProgram();
          break;
  }
  


    
    // Turn all off   
    //for (level=0; level<num_levels; level++) set_suit_level(level, 0, 0);

}
