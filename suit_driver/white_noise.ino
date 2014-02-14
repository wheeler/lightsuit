long myRand = 0;
long mask;
long masked;

void whiteNoise()
{
    myRand = random(16777215); //get a 24-bit random number
    mask=1;
    for (int shift = 0 ; shift < 24 ; shift ++)
    {
      //bit mask out each bit into a boolean
      masked = (myRand & mask) >> shift;
      if (masked)
        set_level_on(shift);
      else
        set_level_off(shift);
       mask = mask << 1;
    }
}


/*
void bitwiseRandomTest()
{
    String binString;
    myRand = 16777215;
    binString = String(myRand,BIN);
    Serial.println(myRand);
    Serial.println(binString);
    myRand = random(16777215);
    binString = String(myRand,BIN);
    Serial.println(myRand);
    Serial.println(binString);
    
    long mask=1;
    long masked;
    for (int shift = 0 ; shift < 24 ; shift ++)
    {
      masked = (myRand & mask) >> shift;
      if (masked)
      {
        Serial.print('T');
      }
      else
        Serial.print('.');
       mask = mask << 1;
    
    }
    Serial.println();
    delay(100);
}
*/
