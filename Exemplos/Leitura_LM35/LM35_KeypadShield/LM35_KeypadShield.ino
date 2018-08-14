#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define BUFFERSIZE 100


int bufferCircular[BUFFERSIZE];
int posicao = 0;
int led = 20;

int ledState = LOW;
unsigned long lastTimeLed = 0;
int value;
float temperatura;

float mediaBuffer(){
  unsigned long somatorio = 0;
  for(int i = 0; i < BUFFERSIZE; i++)
    somatorio = somatorio + bufferCircular[i];
   
  
  return (double) somatorio / BUFFERSIZE;
}


float mapLM(){
  int millivolts;
  float tempC;
  double media;
  media = mediaBuffer(); 
  
  //millivolts = (media / 1024.0) * 5000)
  //tempC = millivolts / 10;
  millivolts = map(media, 0, 1024.0, 0, 5000);  //Retorna millivolts mandados pelo LM35
  tempC = millivolts / 10.0;
  return tempC;
}


void setup() {
  
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ARDUINO DAY 2018");
  lcd.setCursor(0,1);
  lcd.print("IDEIA PUCRS 2018");
}

void loop() {
   bufferCircular[posicao] = analogRead(A12);
   posicao = (posicao +1) % BUFFERSIZE; //Retorna sempre um valor
                                        // entre 0 e BUFFERSIZE
  
    //mediaBuffer();
    temperatura = mapLM();
    //temperatura = mediaBuff;
    Serial.print("Temperatura:  ");
    Serial.println(temperatura); 
    lcd.setCursor(0,1);
    lcd.print("Temperatura: ");
    lcd.print(temperatura); 
     
   if(temperatura > 30){
    digitalWrite(led, HIGH);
    /*if( millis() - lastTimeLed > 1000){
        lastTimeLed = millis();
           
        if(ledState == LOW){
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
        digitalWrite(led, ledState);
      }*/
   } else digitalWrite(led, LOW);
}
