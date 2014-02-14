

void checkInputs()
{
  checkAccelerometers();
  checkAudio();
  checkBattery();
}

//TODO: BODY Bounce BPM

int accelReadSpeed = 100;
long accelNextReadTime = 0;


//accelcenter pointing down = 147
// approx bounce range: 80 - 200 

int analogTemp = 0;

void checkAccelerometers()
{
    if (millis() > accelNextReadTime)
    {
        analog_1_x = (analog_1_x * 3 + get_analog_value(acc_left_X_chan)) / 4;
        analog_1_y = (analog_1_y * 3 + analogRead(acc_left_Y_pin)) / 4;
        analog_1_z = (analog_1_z * 3 + get_analog_value(acc_left_Z_chan)) / 4;
        
//        Serial.print( "x: "); Serial.print(analog_1_x);
//        Serial.print(" y: "); Serial.print(analog_1_y);
//        Serial.print(" z: "); Serial.println(analog_1_z);
        accelNextReadTime = millis() + accelReadSpeed;
    }
}


int audioReadSpeed = 50;
long audioNextReadTime = 0;
int audioSampleCnt;
long nextAudioReportTime = 0;

// MSGEQ7 OUT pin produces values around 50-80
// when there is no input, so use this value to
// filter out a lot of the chaff.
//int filterValue[] = {150,80,80,110,170,225,360};
int filterValue[] = {0,0,0,0,0,0,0};

int eqcnt = 0;
long eqSpeedTestTime = 0;
boolean debugAudio = false;

void checkAudio()
{
    if (millis() > audioNextReadTime)
    {
        audioNextReadTime = millis() + audioReadSpeed;
      
        digitalWrite(eq_reset_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(eq_reset_pin, LOW);
        delayMicroseconds(10);

        // Get all 7 spectrum values from the MSGEQ7
        for (int i = 0; i < 7; i++)
        {
            digitalWrite(eq_strobe_pin, LOW);
            delayMicroseconds(30); // Allow output to settle
         
            analogTemp = analogRead(eq_output_pin);
         
            // Constrain any value above 1023 or below filterValue
            analogTemp = constrain(analogTemp, filterValue[i], 1023);

            //decay
            //spectrumValue[i] = (spectrumValue[i] + analogTemp) / 2;
            
            //no decay
            spectrumValue[i] = analogTemp;
         
            if (debugAudio)
            {
                // Remove serial stuff after debugging
                Serial.print(spectrumValue[i]);
                Serial.print(" ");
            }
         
            digitalWrite(eq_strobe_pin, HIGH);
            delayMicroseconds(10); // Allow output to settle
        }
        if (debugAudio)
        {
            Serial.println();
            audioSampleCnt++;
            if(millis()>nextAudioReportTime)
            {
              nextAudioReportTime = millis()+1000;
              Serial.print("eq sample rate ");Serial.print(audioSampleCnt);Serial.println("Hz");
              audioSampleCnt = 0;
              
            }
        }
      }
}

long nextBatteryCheck = 0;
void checkBattery()
{
    // battery 16.8V full (4.2V per cell), 13.6V low (3.4V/cell), 12.4V (3.1V/cell) cut off
  
    // 0-1023 is the range of our 5V.
 
    // Voltage divider: 470k - 180k
    // Where Z1 is the top resistor...
    // Vout = Vin * ( Z2 / (Z1 + Z2) )
    // Vout = Vin *   
    if (millis() > nextBatteryCheck)
    {
        int batteryAnalog = get_analog_value(batt_sense_chan);
        float battery = ((float)batteryAnalog * 5.0 ) / 1023.0;
        battery *= (65.0/18.0);
        
        battery -= 13.6;
        //now the range is 0 - 3.2
        if (battery < 0)
            battery = 0;
        else if (battery > 3.2)
            battery = 3.2;
        
        battery *= 31.25;

        int batteryPct = (int)battery;

        //Serial.println(battery);
        //Serial.println(batteryAnalog);
        //Serial.println(batteryPct);
        
        Serial.print('%');
        Serial.print(batteryPct);
        Serial.print(';');
        Serial1.print('%');
        Serial1.print(batteryPct);
        Serial1.print(';');

        nextBatteryCheck = millis()+10000;
    }
}
