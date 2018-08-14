#include <LiquidCrystal.h>

#define RPMSAMPLES 20

unsigned long counter = 0;
unsigned long lastRotationTime = 0;
unsigned long lastTestTime = 0;

unsigned int  rotation  = 0;
unsigned int rotationAVG  = 0;
unsigned int somatorio = 0;
byte posicao = 0; //(max = 255)
byte tamanhoMedia = 0; //(max = 255)
byte setPoint = 6;
byte valorPWM = 70;

unsigned int  rotationArray[RPMSAMPLES];

void countRPM(){
  counter++;
}

byte pwmPin = 10;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
  attachInterrupt(2, countRPM, RISING);  // increase counter when speed sensor pin goes High
  pinMode(pwmPin, OUTPUT);  
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.begin(9600);
  for (int i = 0; i < RPMSAMPLES; i++)
    rotationArray[i] = 0;
}

void calcRotation(){
  if (counter > 60 || lastRotationTime == 0){
    rotation = ((counter / 20.)/(millis()-lastRotationTime) * 600);  
    if (lastRotationTime) counter = 0;    
    lastRotationTime = millis();
    rotationArray[posicao] = rotation;
    posicao = (posicao + 1) % RPMSAMPLES;    
    somatorio = 0;
    tamanhoMedia = 0;
    for (int i = 0; i < RPMSAMPLES; i++){
      if (rotationArray[i]){
        somatorio = somatorio + rotationArray[i];
        tamanhoMedia++;        
      }
    }
    rotationAVG = somatorio / tamanhoMedia;    
  }
  analogWrite(pwmPin, valorPWM);
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print("Rotacao: ");
  calcRotation();
  
  if ((posicao == RPMSAMPLES - 1) && (millis() - lastTestTime > 500)){
    lastTestTime = millis();
    if (rotationAVG > setPoint) valorPWM--;
    if (rotationAVG < setPoint) valorPWM++; 
    /*Serial.print( millis());
    Serial.print(", ");    
    Serial.print( lastTestTime);
    Serial.print(", ");    
    Serial.println( millis()-lastTestTime);*/
    //Tentaiva de controle proporcional
    //if (rotationAVG > setPoint) valorPWM -= (rotationAVG - setPoint) * 10;
    //if (rotationAVG < setPoint) valorPWM += (setPoint - rotationAVG) * 10;       
       
  }
  lcd.print(rotationAVG * 100);
  lcd.print("    ");
  lcd.setCursor(0,1);
  lcd.print(counter);
  lcd.print(" ");
  //lcd.print(valor_pwm);  
  
  Serial.print( setPoint);
  Serial.print(", ");    
  Serial.print( valorPWM/10);
  Serial.print(", ");    
  Serial.print( rotation);
  Serial.print(", ");
  Serial.println( rotationAVG);  
}
