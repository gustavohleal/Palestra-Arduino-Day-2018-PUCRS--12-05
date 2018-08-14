
#define BUFFERSIZE 100
int bufferCircular[BUFFERSIZE];

int posicao = 0;

float mediaDoBuffer(){
  unsigned long somatorio = 0;
  for (int i = 0; i < BUFFERSIZE; i++)
    somatorio = somatorio + bufferCircular[i];
    
    //Serial.println(somatorio);
      return (double) somatorio / BUFFERSIZE;
}

void setup(){
  Serial.begin(9600);
  for (int i = 0; i < BUFFERSIZE; i++)
    bufferCircular[i] = 0;
}

void loop(){
 
  bufferCircular[posicao] = analogRead(A5);
  posicao = (posicao + 1) % BUFFERSIZE;
  mediaDoBuffer();
  Serial.println(mediaDoBuffer(), 4);
}
