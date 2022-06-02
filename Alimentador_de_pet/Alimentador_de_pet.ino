#include <Servo.h>  //incluir a biblioteca de servo
#include "HX711.h"  
#define DT A1
#define SCK A0 
HX711 bau;             // instancia Balança HX711
float calibration_factor = 34730;     // fator de calibração aferido na Calibração 
Servo myservo;  //Inclusao do servo

char n;  //Entradas seriais
int pos = 0;  //Posição zero para o servop

void setup()
{
  Serial.begin(9600);  //Ativando a porta serial
  myservo.attach(2);  //Pino do servo+arduino
  myservo.write(0);  //Servo setado com valor zero
  bau.begin(DT, SCK);      // inicializa a balança
  bau.set_scale(calibration_factor);             // ajusta fator de calibração
  bau.tare();                                    // zera a Balança
  
  Serial.println("Digite: s para ativar");  //criação de um cabeçalho no serial
}

void loop(){
  if(Serial.available()>0){  //Teste se porta serial esta recebendo dados
    n = Serial.read();  //leitura de dados
    //Serial.print("Valor lido: ");  
    //Serial.println(n);  //Printa o valor teclado

    if(n == 's' ||'S'){  //girar 90
      for(pos = 0; pos <= 90; pos++) {
        myservo.write(pos);
        //Serial.println(pos);
        delay(30);  
    }
     for(pos = 90; pos>=0; pos--) {
       myservo.write(pos);
       //Serial.println(pos);
       delay(50);
    }
    }
    delay (500);
  Serial.print("Peso: ");                            
  Serial.print(bau.get_units(), 3);         // imprime peso na balança com duas casas decimais 
  Serial.println(" kg");                             // imprime no monitor serial 
  delay(100) ;                                       
  if (Serial.available())                            // se a serial estiver disponivel
  {
    char temp = Serial.read();                       // le carcter da serial 
    if (temp == 't' || temp == 'T')                  // se pressionar t ou T
    {
      bau.tare();                                // zera a balança
      Serial.println(" Balança zerada");             // imprime no monitor serial
    }
  } 
    Serial.println("Digite: s para ativar novamente");  //criação de um cabeçalho no serial 
  }
}
