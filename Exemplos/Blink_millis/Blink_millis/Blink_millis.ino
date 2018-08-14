
unsigned long lastTimeLed1 = 0;
unsigned long lastTimeLed2 = 0;

int ledState = LOW;
int led2State = LOW;
void setup() {

  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  
}

void loop() {
  if( millis() - lastTimeLed1 > 1000){
    lastTimeLed1 = millis();
       
    if(ledState == LOW){
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(3, ledState);
  }
  
  if( millis() - lastTimeLed2 > 2000){
    lastTimeLed2 = millis();
    if(led2State == LOW){
      led2State = HIGH;
    } else {
      led2State = LOW;
    }
    digitalWrite(7, led2State);
  }
}


