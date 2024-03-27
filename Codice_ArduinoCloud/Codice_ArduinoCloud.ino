#include "thingProperties.h"

int sensore = 32; // Sensore
int pompa = 27; // Pompa
int ledV = 12; // LED verde
int ledR = 13; // LED rosso
int potenziometro = 33, pausa = 0, nuovaPausa = 0;
bool halt;

unsigned long vecchioMillis, nuovoMillis, nuovoMillisHalt, vecchioMillisHalt;

// Temporizzazioni
int minuto = 60000; // Durata di 1 minuto (default: 60000)

// int tPompa = 5; // La pompa si accenderà per questo numero di minuti
int tMin = 10;
int tMax = 60;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  
  pinMode(sensore, INPUT);
  pinMode(pompa, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);

  digitalWrite(ledV, LOW);
  digitalWrite(ledR, LOW);
  digitalWrite(pompa, LOW);
  
  pausa = analogRead(potenziometro);
  delay(100); // Delay per ADC
  pausa = map(pausa, 0, 4095, tMin, tMax);
  tempoRimanenteHalt = pausa;
  
  delay(2000);
  
  vecchioMillis=millis();
  tPompa = 5;
}

void loop() {
  ArduinoCloud.update();
  
  nuovaPausa = analogRead(potenziometro);
  delay(100); // Delay per ADC
  nuovaPausa = map(nuovaPausa, 0, 4095, tMin, tMax);

  if(nuovaPausa!=pausa){
    pausa=nuovaPausa;
    tempoRimanenteHalt = pausa;
  }
  
  if(digitalRead(sensore)) { // Se c'è acqua
      presenzaAcqua=true;
      
      if(!halt)
        controlloPompa();
    
  } else { // Se non c'è acqua
    vecchioMillis = millis();
    halt=false;
    timerPompa = 0;
    digitalWrite(pompa, LOW);
    digitalWrite(ledV, LOW);
    statoPompa=false;
    presenzaAcqua=false;
    
    
    digitalWrite(ledR, HIGH);
    delay(600);
    digitalWrite(ledR, LOW);
    delay(600);
  }
  
  delay(1000);
  
  if(halt){
    nuovoMillisHalt=millis();
    tempoRimanenteHalt = pausa - (nuovoMillisHalt - vecchioMillisHalt)/minuto;
    if(nuovoMillisHalt - vecchioMillisHalt >= pausa*minuto){
      halt=false;
      tempoRimanenteHalt = pausa;
      vecchioMillis = millis(); 
    }
  }
  
}


void controlloPompa(){
  nuovoMillis = millis();
  digitalWrite(pompa, HIGH);
  digitalWrite(ledV, HIGH);
  timerPompa = tPompa - (nuovoMillis - vecchioMillis)/minuto; // Tempo attività pompa rimanente
  statoPompa=true;

  if(nuovoMillis - vecchioMillis >= tPompa*minuto){ // Se è finito il tempo di attività della pompa
    digitalWrite(pompa, LOW);
    digitalWrite(ledV, LOW);
    timerPompa = 0;
    statoPompa = false;
    halt = true;
    vecchioMillisHalt=millis();
  }
}



/*
  Since TPompa is READ_WRITE variable, onTPompaChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTPompaChange()  {
  // Add your code here to act upon TPompa change
}
