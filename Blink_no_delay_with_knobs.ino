    
    unsigned long previousMillis = 0;        // will store last time LED was updated
    unsigned long previousSerialMillis = 0; //create a seperate timer for the serial reporting functions
    const int serialInterval = 500;//reporting to serial 2x a sec.
    int knob1Pin = A0;
    int knob2Pin = A1;  
    const int pwmPin = 3;
    int pwmState = 0;
    
     
    void setup() {
    
      pinMode(pwmPin, OUTPUT);
      pinMode(knob1Pin, INPUT);
      pinMode(knob2Pin, INPUT);
      Serial.begin(9600);
    }
    
    void loop() {

    int knob1 = analogRead(knob1Pin);//Potentiometer 1
    int knob2 = analogRead(knob2Pin);//Potentiometer 2
    int brightness = map(knob1, 0, 1023, 255, 1);//map brightness to 1st potentiometer
    int brightnesspercent = map(knob1, 0, 1023, 1, 100);//I like reading percentages better. For serial reporting only.
    int interval = map(knob2, 0, 1023, 750, 25); //(changing interval to a value based on an analog reading)
    int intervalSecs = map(knob2, 0, 1023, 2.00, 0.00);//I like reading seconds more than milliseconds. For serial reporting only.
     
     //Timer for the LED. 
      unsigned long currentMillis = millis();
       if (currentMillis - previousMillis >= interval) {
           previousMillis = currentMillis;
         //set the pwmPin to desired level, or off, depending on pwmState
        if (pwmState == 0){
        pwmState = brightness;
        }else {
          pwmState = 0;
        }
    
        analogWrite(pwmPin, pwmState);
      }
      unsigned long currentSerialMillis = millis();
        if (currentSerialMillis - previousSerialMillis>= serialInterval){
         previousSerialMillis = currentSerialMillis;
        
           Serial.print("Brightness: ");
           Serial.print(brightnesspercent);
           Serial.print("%");
           Serial.print("   Interval: ");
           Serial.print(intervalSecs);
           Serial.print(" seconds");
           Serial.println();
           Serial.print(brightness);
           Serial.print(" ");
           Serial.print(interval);
           Serial.println();
        }
     }
    
