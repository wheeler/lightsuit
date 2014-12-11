

void setup() {

    pinMode(eq_reset_pin, OUTPUT);
    pinMode(eq_strobe_pin, OUTPUT);
    digitalWrite(eq_reset_pin, LOW);
    digitalWrite(eq_strobe_pin, HIGH);

    // CD4051
    pinMode(cd4051_s0_pin, OUTPUT);    // s0
    pinMode(cd4051_s1_pin, OUTPUT);    // s1
    pinMode(cd4051_s2_pin, OUTPUT);    // s2
    
    analogReference(DEFAULT); // 5V
  
    randomSeed(analogRead(3));
    Serial.begin(115200);
    Serial1.begin(115200);
    
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("\n48 channel PWM test");

    Serial.print("starting PCA's, frequency: ");
    Serial.println(pca_freq);
    pwmA.begin();
    pwmA.setPWMFreq(pca_freq);  // Maximum PWM frequency = 160
    Serial.println("PCA frequency set");
    pwmB.begin();
    pwmB.setPWMFreq(pca_freq);  // Maximum PWM frequency = 160
    pwmC.begin();
    pwmC.setPWMFreq(pca_freq);  // Maximum PWM frequency = 160
    Serial.println("started PCA output chips");

    // save I2C bitrate... ?
    uint8_t twbrbackup = TWBR;

    // must be changed after calling Wire.begin() (inside pwm.begin())
    TWBR = 12; //  400KHz

    //bootSuit();
    //pulse_old();
    // Set all outputs low... is this necessary?
    clearSuit();

    programResets();

}



//PWM recurve check    
//    Serial.print("fades ");
//    for (int i=0; i<num_fades; i++)
//    {
//        Serial.print(fadeValues[i]);
//        Serial.print(",");
//    }
//    Serial.println();
//    Serial.print("realpwm");
//    for (int i=0; i<num_fades; i++)
//    {
//        Serial.print(realPWM(fadeValues[i]));
//        Serial.print(",");
//    }
//    Serial.println();
