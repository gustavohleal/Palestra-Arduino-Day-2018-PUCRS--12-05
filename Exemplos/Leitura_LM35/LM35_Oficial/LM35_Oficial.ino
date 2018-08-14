/*  ARDUINO DAY 2018
 *   IDEIA / PUCRS / TECNOPUC
 *   @author: Gustavo H. Leal

*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //Define os pinos para o display LCD(Não necessário)
#define BUFFERSIZE 50 //Define o tamanho do buffer circular

//############################ Define o buffer circular e a variável de index
int bufferCircular[BUFFERSIZE];
int posicao = 0;

//############################ Define variáveis para uso do led;
int led = 20; //Pino para o LED
int ledState = LOW; //Estado da saída digital para o LED: HIGH ou LOW
unsigned long lastTimeLed = 0; // Variável para utilização com millis;

//############################ REALIZA A MÉDIA DO BUFFER CIRCULAR
float mediaBuffer(){
  unsigned long somatorio = 0;
  for(int i = 0; i < BUFFERSIZE; i++)
    somatorio = somatorio + bufferCircular[i];
     
  return (double) somatorio / BUFFERSIZE;
}

//############################ MAP PARA A LEITURA DE TEMPERATURA
float mapLM(){
  int millivolts;
  float tempC;
  double media;
  media = mediaBuffer(); 
  //######################### Tirar comentário para não usar função map()
  //millivolts = (media / 1024.0) * 5000)
  //tempC = millivolts / 10;
  millivolts = map(media, 0, 1024.0, 0, 5000);  //Retorna millivolts mandados pelo LM35
  tempC = millivolts / 10.0; //Converte o valor de millivolts para graus celcius;
  return tempC;
}

float mapLMSemBuffer(){
  int millivolts;
  float tempC;
  double value;
  value = analogRead(A12);
  //######################### Tirar comentário para não usar função map()
  millivolts = (value / 1024.0) * 5000;
  tempC = millivolts / 10;
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
  delay(2000);
  lcd.clear();
}

void loop() {
  
   float temperatura;
   float temperaturaSemBuffer;
   //########################## Realiza preenchimento do buffer
   bufferCircular[posicao] = analogRead(A12); // Buffer circular
   posicao = (posicao +1) % BUFFERSIZE; // Altera o index do buffer. O calculo resulta 
   /////////////////////////////////////// sempre em um valor de 1 até BUFFERSIZE
   
   mediaBuffer(); // Faz a media do buffer
   temperatura = mapLM(); // Faz o mapeamento da leitura de temperatura
   
   // Tirar comentário para usar sem buffer em paralelo
   temperaturaSemBuffer = mapLMSemBuffer();
   //Serial.print("Temperatura sem buffer:  ");
   //Serial.print(temperaturaSemBuffer);
   //Serial.print ("\t");
   //Serial.print("Temperatura:  ");
   Serial.println(temperatura);

   //############################ Imprime do display o valor da temperatura
   lcd.setCursor(0,0);
   lcd.print("ARDUINO DAY 2018"); 
   lcd.setCursor(0,1);
   lcd.print("Temp: ");
   lcd.print(temperatura); 
   lcd.print("C");

   //########################### Controle do LED
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
