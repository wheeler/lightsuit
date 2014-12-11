
void setup()
{              
  Serial.begin(115200);
  Serial.println("boot");

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  // init done
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0); // '1' would allow looking down the arm at the oled (would require various other code changes)
  display.setCursor(0,0);
  display.println("boot");
  
  // Set up rotary encoder 1
  pinMode(rot1_up_pin, INPUT);
  pinMode(rot1_down_pin, INPUT);
  pinMode(rot1_button_pin, INPUT);
    
  digitalWrite(rot1_up_pin, HIGH );
  digitalWrite(rot1_down_pin, HIGH );
  digitalWrite(rot1_button_pin, HIGH );
  
  //int settingsSize = sizeof(settings);
}

