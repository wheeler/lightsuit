
//    
//    int test = 0x11111111;
//    Serial.println(test);
    
    


void testProgram()
{
    for (int i = 0;i<23;i++)
    {
        int start = 800+(100*i);
        int endd = 1800+(100*i);
        if (i==22)
        {
          start = 0;
          endd = 1000;
        }
        set_suit_level(i,start,endd);
        Serial.print(i);Serial.print('-');Serial.print(start);Serial.print('-');Serial.println(endd);
    }
    delay(2000);
}    
    

void testGradiant()
{

    
//    Serial.print("linear");
//    Serial.print(":  { ");
//    for (int i=0; i<=num_levels; i++)
//    {
//      int value = ((long)fullon*i)/num_levels;
//      Serial.print(value);
//      Serial.print(", ");
//      set_suit_level(i, 0, value); 
//    }
//    Serial.println(" }");
//    delay(5000);

//    Serial.print("jeff linear");
//    int lvl = 23;
//    Serial.print(lvl);
//    Serial.print(":  { ");
//    // Compute brightnesses
//    for (uint8_t i=0; i<num_levels; i++) {
//        long b = 0;
//        if (i<=23)
//            b = (4095 * (long(i)+1)) / (lvl+1);
//        else
//            b = 4096 * (6*(num_levels-long(i))) / (6*(num_levels-long(lvl)));
//        Serial.print(int(b));
//        Serial.print(", ");
//        set_suit_level(i, 0, b);
//    }
//    Serial.println(" }");
//    delay(5000);

    
    
//    
//    Serial.print("2^x");
//    Serial.print(":  { ");
//    for (int i=0; i<=num_levels; i++)
//    {
//      int value = pow (2 , i/1.9166   ) - 1;
//      Serial.print(value);
//      Serial.print(", ");
//      set_suit_level(i, 0, value); 
//    }
//    Serial.println(" }");
//    delay(5000);
    
    // 2 ^ (x/2.0352) + (128*x) + 100
    float factorfor4095 = 2.0352;
    float factorfor3560 = 2.0991;
    
    Serial.print("2^x + 64x + 100 [3560]");
    Serial.print(":  { ");
    for (int i=0; i<=num_levels; i++)
    {
      int value = pow (2 , i/factorfor3560) + (64*i) + 100;
      Serial.print(value);
      Serial.print(", ");
      set_suit_level(i, 0, value); 
    }
    Serial.println(" }");
    delay(5000);
    
    
//    Serial.print("2^x + 64x + 100 [4095]");
//    Serial.print(":  { ");
//    for (int i=0; i<=num_levels; i++)
//    {
//      int value = pow (2 , i/factorfor4095) + (64*i) + 100;
//      Serial.print(value);
//      Serial.print(", ");
//      set_suit_level(i, 0, value); 
//    }
//    Serial.println(" }");
//    delay(5000);
    
//    
//    Serial.print("x^(3/13)");
//    Serial.print(":  { ");
//    for (int i=0; i<=num_levels; i++)
//    {//2956.2* (x^(3/13)) - 2000
//      int value = (2956* (pow(i,(0.23077)))) - 2000 ;
//      Serial.print(value);
//      Serial.print(", ");
//      set_suit_level(i, 0, value); 
//    }
//    Serial.println(" }");
//    delay(5000);
//    
    
    
    
//    Serial.print("log x");
//    Serial.print(":  { ");
//    for (int i=0; i<=num_levels; i++)
//    {
//      int value = 1288.5 * log(i+1) ;
//      Serial.print(value);
//      Serial.print(", ");
//      set_suit_level(i, 0, value); 
//    }
//    Serial.println(" }");
//    delay(5000);
}
