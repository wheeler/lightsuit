long lastRotaryTurn = 0;
int recentRotaryCount = 0;
boolean lastRotaryTurnWasUp = true;

void checkInputs()
{
    //speed_test();
  
    // Adjust Rotary 1
    updateRotaryValue();


    //new value
    if (rotaryValue != rotaryLast)
    {  
        handleRotaryAcceleration(rotaryValue > rotaryLast);

        //Serial.print("v ");
        //Serial.println(rotaryValue);
        //Serial.println(rotaryCap);
        //Serial.println(rotaryLast);
        
        //SCROLLING LIST HANDLING
        if (interfaceState == INTERFACE_LIST_PROGRAMS && (rotaryValue > programModeScroll + ROWS_OF_TEXT - 1 || rotaryValue < programModeScroll))
        {
            if (rotaryValue < programModeScroll)
                programModeScroll = rotaryValue;
            else
                programModeScroll = rotaryValue - (ROWS_OF_TEXT-1);
            if (programModeScroll < 0)
                programModeScroll = 0;
            //Serial.print("scroll ");Serial.println(programModeScroll);
            //Serial.print("sizeof(programNames) ");            Serial.println(sizeof(programNames));
        }

        rotaryLast = rotaryValue;
        displayInvalid = true;
    }

    if (digitalRead(rot1_button_pin) == LOW && millis() > nextButtonCheck)
    {
        rotaryButtonPress = true;
        //Serial.println("button");
        nextButtonCheck = millis() + buttonDebounce;
        //TODO: process "click" on button RELEASE
    }

    if (rotaryButtonPress)
    {
        handleButtonPress();
        rotaryButtonPress = false;
        displayInvalid = true;
    }
    
}

void handleRotaryAcceleration(boolean thisTurnWasUp)
{
    long now = millis();
    
    if (thisTurnWasUp != lastRotaryTurnWasUp)
    {
        lastRotaryTurn = 0;
        resetRotaryAccleration(thisTurnWasUp);
        Serial.println('d');

    }
    else if ((lastRotaryTurn + 1000) > now)
    {
        lastRotaryTurn = now;
        recentRotaryCount++;
        rotaryIncrement++;
        Serial.println('+');
    }
    else
    {
        lastRotaryTurn = now;
        resetRotaryAccleration(thisTurnWasUp);
        Serial.println('t');
    }
    
}

void resetRotaryAccleration(boolean thisTurnWasUp)
{
    recentRotaryCount = 0;
    lastRotaryTurnWasUp = thisTurnWasUp;
    rotaryIncrement = 1;
}

char serialRead;
int serialTemp;
void checkBattery() //from the serial
{
    //keep the serial flushed
    if (Serial.available())
    {
        serialRead = Serial.read();
        if (serialRead == '%')
        {
            serialTemp = Serial.parseInt();
            if (serialTemp > 100) serialTemp = 100;
            if (serialTemp < 0) serialTemp = 0;
            if (batteryLife != serialTemp)
            {
                batteryLife = serialTemp;
                displayInvalid = true; 
            }
        }
    }
}

// BUTTON based STATE TRANSITIONS
void handleButtonPress()
{
    // EDIT VALUE ==> PROPERTIES LIST
    if (interfaceState == INTERFACE_CUSTOMIZE_PROGRAM_EDIT)
    {
      interfaceState = INTERFACE_CUSTOMIZE_PROGRAM;
      propertyValues[propertyModeRotary] = rotaryValue;
      
      rotaryValue = propertyModeRotary;
      rotaryLast = rotaryValue;
      rotaryCap = number_of_properties - 1;
      rotaryIncrement = 1;
    }
    // "SAVE" PROPERTIES LIST == > PROGRAMS LIST
    else if (interfaceState == INTERFACE_CUSTOMIZE_PROGRAM && rotaryValue == 0)
    {
      interfaceState = INTERFACE_LIST_PROGRAMS;
      propertyModeRotary = rotaryValue;
      
      rotaryValue = program;
      rotaryLast = rotaryValue;
      rotaryCap = number_of_programs - 1;
      rotaryIncrement = 1;
      
      //Send the "save"
      Serial.print('P');Serial.print(program);Serial.print(';');
      Serial.print('B');Serial.print(propertyValues[PROPERTY_BRIGHTNESS]);Serial.print(';');
      Serial.print('T');Serial.print(propertyValues[PROPERTY_TEMPO]);Serial.print(';');
      Serial.print('E');Serial.print(propertyValues[PROPERTY_EQ_BAND]);Serial.print(';');
      
    }
    // PROPERTIES LIST == > EDIT VALUE
    else if (interfaceState == INTERFACE_CUSTOMIZE_PROGRAM)
    {
      interfaceState = INTERFACE_CUSTOMIZE_PROGRAM_EDIT;
      propertyModeRotary = rotaryValue;
      
      rotaryValue = propertyValues[propertyModeRotary];
      rotaryLast = rotaryValue;
      if (propertyModeRotary == PROPERTY_TEMPO)
      {
        rotaryCap = 200;
        rotaryIncrement = 1;
      }
//      else if (propertyModeRotary == PROPERTY_DUTY)
//      {
//        rotaryCap = 100;
//        rotaryIncrement = 10;
//      }
      else if (propertyModeRotary == PROPERTY_BRIGHTNESS)
      {
        rotaryCap = 10;
        rotaryIncrement = 1;
      }
      else
      {
        rotaryCap = 10;
        rotaryIncrement = 1;
      }
    }
    // PROGRAM LIST ==> PROPERTIES LIST
    else if (program == rotaryValue && interfaceState == INTERFACE_LIST_PROGRAMS && rotaryValue != 0)
    {
      interfaceState = INTERFACE_CUSTOMIZE_PROGRAM;
      programModeRotary = rotaryValue;
      
      rotaryValue = PROPERTY_TEMPO;
      rotaryLast = rotaryValue;
      rotaryCap = number_of_properties - 1;
      rotaryIncrement = 1;
    }
    else //SELECT A PROGRAM
    {
      program = rotaryValue;
      Serial.print('P');Serial.print(program);Serial.print(';');
    }
}



//======================================================================================================



void updateRotaryValue()
{
    if ( millis() < nextRotaryCheck )
        return;

    rot1_down = digitalRead(rot1_down_pin);
    if ( rot1_down == LOW && rot1_down_last == HIGH )
    {
        if (digitalRead(rot1_up_pin) == HIGH)
            rotaryValue -= rotaryIncrement;
        else
            rotaryValue += rotaryIncrement;

        nextRotaryCheck = millis() + rotaryDebounce;

        if ( rotaryValue > rotaryCap || rotaryValue < 0 )
        {
            rotaryValue = rotaryLast;
            return;
        }
            
        if (rotaryValue != rotaryLast)
        {  
            handleRotaryAcceleration(rotaryValue > rotaryLast);
        }        
    }
    rot1_down_last = rot1_down;

} 


long speed_next_test_time = 0; //tuning note: using a next var instead of repeating the math adds 127 Hz to the loop
long speed_counter = 0;      // speed test counter: cycles/sec
void speed_test() {
  speed_counter ++;
  if (millis() >= speed_next_test_time) {
    Serial.print(speed_counter);
    Serial.println(" Hz");
    speed_counter = 0;
    speed_next_test_time = millis()+1000;
  }
}
