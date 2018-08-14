#include <Ultrasonic.h>

#define BUFFERSIZE 500
#define TRIGGER_PIN 12
#define ECHO_PIN 13
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

unsigned long bufferCircular[BUFFERSIZE];
int posicao = 0;

float mediaDoBuffer(){
  unsigned long somatorio = 0;
  for (int i = 0; i < BUFFERSIZE; i++)
    somatorio = somatorio + bufferCircular[i];

  //Serial.println(somatorio/BUFFERSIZE);
  return (double) somatorio / BUFFERSIZE;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  
  bufferCircular[posicao] = ultrasonic.convert(microsec, Ultrasonic::CM);
  posicao = (posicao + 1) % BUFFERSIZE;
  mediaDoBuffer();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  

  Serial.print(mediaDoBuffer()/100.0);
  Serial.print("\t");
  Serial.println(cmMsec/100.0);
 
}
