/* NATMUS
 *  by Stefano Rossi - 28/02/2024
 *  
 *  - Serra idroponica -
 *  questo codice non include la gestione dei sensori di parametri
 *  avanzati dell'acqua (pH, CE, temperatura)
 *  
 */

int sensore = 32; // Sensore
int pompa = 27; // Pompa
int ledV = 12; // LED verde
int ledR = 13; // LED rosso
int potenziometro = 33, pausa = 0, nuovaPausa = 0;

unsigned long vecchioMillis = 0;
unsigned long nuovoMillis = 0;

// Temporizzazioni
int minuto = 60000; // Durata di 1 minuto (default: 60000)

int tPompa = 5; // La pompa si accenderà per questo numero di minuti
int tMin = 10;
int tMax = 60;

void setup() {
  Serial.begin(9600);
  pinMode(sensore, INPUT);
  pinMode(pompa, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);

  digitalWrite(ledV, LOW);
  digitalWrite(ledR, LOW);
  digitalWrite(pompa, LOW);

  Serial.println("Configurazione avvenuta");
  
  pausa = analogRead(potenziometro);
  delay(100); // Delay per ADC
  pausa = map(pausa, 0, 4095, tMin, tMax);
  Serial.println("Tempo: " + String(pausa) + "min");
  
  delay(2000);
}

void loop() {
  nuovaPausa = analogRead(potenziometro);
  delay(100); // Delay per ADC
  nuovaPausa = map(nuovaPausa, 0, 4095, tMin, tMax);

  if(nuovaPausa!=pausa){
    pausa=nuovaPausa;
    Serial.println("Nuovo tempo di attesa: " + String(pausa) + "min");
  }
  
  if(digitalRead(sensore)) { // Se c'è acqua
    nuovoMillis = millis();
    
    digitalWrite(pompa, HIGH);
    digitalWrite(ledV, HIGH);
    Serial.println("Pompa accesa");

    if(nuovoMillis - vecchioMillis >= tPompa*minuto){
      digitalWrite(pompa, LOW);
      digitalWrite(ledV, LOW);
      Serial.println("Pompa spenta");
      
      delay(pausa*minuto);
      nuovoMillis = millis();
      vecchioMillis = nuovoMillis;
    }
    
  } else {
    digitalWrite(pompa, LOW);
    digitalWrite(ledV, LOW);
    
    Serial.println("ATTENZIONE! Riempire serbatoio");
    
    while(!digitalRead(sensore)){ // Se non c'è acqua ripeti all'infinito
    digitalWrite(ledR, HIGH);
    delay(600);
    digitalWrite(ledR, LOW);
    delay(600);
    }
  }
  
  delay(1000);
}
