
#define batteryOriginX 100
#define batteryOriginY 53
#define interfaceOriginX 0
#define interfaceOriginY 0 //currently must be 0

void runFullDisplay()
{
  if (displayInvalid && millis() > nextDisplayTime)
  {
    display.clearDisplay();
    //drawManOutline();
    checkInputs();

    drawInterface();
    checkInputs();

    drawBattery();
    checkInputs();

    display.display();

    displayInvalid = false;
    nextDisplayTime = millis() + displaySpeed;
  }
}


void drawInterface()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
  
    if (interfaceState == INTERFACE_CUSTOMIZE_PROGRAM || interfaceState == INTERFACE_CUSTOMIZE_PROGRAM_EDIT)
    {
        display.setCursor(interfaceOriginX, interfaceOriginY);  display.print("Edit ");display.print(programNames[program]);
        
        for (int i = 0 ; i < number_of_properties ; i++)
        {
            if (interfaceState == INTERFACE_CUSTOMIZE_PROGRAM && rotaryValue == i)
                display.setTextColor(BLACK, WHITE);
            else
                display.setTextColor(WHITE, BLACK);
            display.setCursor(interfaceOriginX, interfaceOriginY + 8 + (i*8));  display.print(propertyNames[i]);
    
            if (i!=0) //zero is "save" which has no values
            {
                display.setTextColor(WHITE, BLACK);
                display.print(" ");
        
                if (interfaceState == INTERFACE_CUSTOMIZE_PROGRAM_EDIT && propertyModeRotary == i)
                {
                    display.setTextColor(BLACK, WHITE);
                    display.print(rotaryValue);
                }
                else
                {
                    display.setTextColor(WHITE, BLACK);
                    display.print(propertyValues[i]);
                }
            }
        }
    }
    else //INTERFACE_SELECT_PROGRAM
    {
      
        if (program == rotaryValue && program != 0)
        {
            display.setCursor(interfaceOriginX, (program-programModeScroll)*8);
            display.print("E>");
        }
        else
        {
            display.setCursor(interfaceOriginX + 2, (program-programModeScroll)*8);
            display.print(">");
        }
        
        for (int i = programModeScroll ; i < programModeScroll + ROWS_OF_TEXT && i < sizeof(programNames) ; i++)
        {
            if (rotaryValue == i)
                display.setTextColor(BLACK, WHITE);
            else
                display.setTextColor(WHITE, BLACK);
            display.setCursor(interfaceOriginX + 11, (i-programModeScroll)*8);  display.print(programNames[i]);
        }
    }

}

//void drawManOutline()
//{
//    display.drawFastHLine(9,0,10,WHITE); //top of head
//    display.drawFastVLine( 8,1,9,WHITE); //left side of head
//    display.drawFastVLine(19,1,9,WHITE); //right side of head
//    
//    display.drawFastHLine( 1,10,8,WHITE); //left shoulder top
//    display.drawFastHLine(19,10,8,WHITE); //right shoulder top
//    
//    display.drawFastVLine( 0,11,21,WHITE); //left arm outside
//    display.drawFastHLine( 1,32, 4,WHITE); //left hand
//    display.drawFastVLine( 5,16,34,WHITE); //left body side
//    display.drawFastVLine(27,11,21,WHITE); //right arm outside
//    display.drawFastHLine(22,32, 5,WHITE); //right hand
//    display.drawFastVLine(22,16,34,WHITE); //right body side
//    
//    display.drawFastHLine(13,32, 2,WHITE); //crotch
//    display.drawFastVLine(12,33,17,WHITE); //left inseam
//    display.drawFastHLine( 6,50, 6,WHITE); //left foot
//    display.drawFastVLine(15,33,17,WHITE); //right inseam
//    display.drawFastHLine(16,50, 6,WHITE); //right foot
//}


void drawBattery()
{
    //Draw a battery
    display.drawRect(batteryOriginX, batteryOriginY, 26, 11, WHITE);
    display.drawRect(batteryOriginX + 25, batteryOriginY + 2, 3, 7, WHITE);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    
    //adjust cursor position to make the text centered
    if (batteryLife >= 100) 
        display.setCursor(batteryOriginX + 1, batteryOriginY + 2); //position for 4 chars
    else if (batteryLife >= 10 || batteryLife < 0) 
        display.setCursor(batteryOriginX + 4, batteryOriginY + 2); //position for 3 chars
    else
        display.setCursor(batteryOriginX + 8, batteryOriginY + 2); //position for 2 chars

    //print the battery value
    display.print(batteryLife);
    display.print("%");
}


