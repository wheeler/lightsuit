int serialTemp = 0;

//SERIAL COMMANDS:
// P - program
// B - brightness
// E - equalizer channel
// T - tempo

boolean readingSerialOne = false;
char command;

byte SerialRead()
{
    if (readingSerialOne)
        return Serial1.read();
    else
        return Serial.read();
}

int SerialParseInt()
{
    if (readingSerialOne)
        return Serial1.parseInt();
    else
        return Serial.parseInt();
}

void checkSerial()
{
    // there is data to read and the buffer contains a full instruction
    if (Serial.available() || Serial1.available())
    {
        readingSerialOne = Serial1.available();
            
        command = SerialRead();
      
        //READ A PROGRAM INSTRUCTION
        if (command == 'P')
        {
            // read the incoming integer
            mode = SerialParseInt();
      
            // say what you got:
            Serial.print("Mode: ");
            Serial.println(mode);
  
            clearSuit();
            programResets();
        }
        else if (command == 'B')
        {
            // read the incoming integer
            serialTemp = SerialParseInt();
            if (serialTemp > 0 && serialTemp <= 10)
            {
                brightness = serialTemp;
                Serial.print("Brightness: ");
                Serial.println(brightness);
            }
            else
            {
                Serial.println("invalid brightness command");
            }
        }
        else if (command == 'E')
        {
            whichEq = SerialParseInt();
            Serial.print("EQ: ");
            Serial.println(whichEq);
        }
        else if (command == 'T')
        {
            tempo = SerialParseInt();
            tempoChange();
            Serial.print("Tempo: ");
            Serial.println(tempo);
            Serial.print("Actual Tempo: ");
            Serial.println(actualTempo);
            Serial.print("Millis Per Step: ");
            Serial.println(millisPerProgramStep);
        }
    }
}
