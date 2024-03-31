#include "DHT.h"

#define DHTPIN D2      // pino de conexão
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const int ledVerde = D5;
const int ledAmarelo = D6;
const int ledVermelho = D7;

void setup() {
  Serial.begin(9600);
  Serial.println("Teste se sensor DHT!");
  dht.begin();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

void loop() {
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) {
    Serial.println("Sensor com defeito");
  } 
  else if (t >= 30) {
    digitalWrite(ledVermelho, HIGH); // Indica a temperatura Alta
    //digitalWrite(ledVerde, LOW);
    //digitalWrite(ledAmarelo, LOW);
  } 
  else if (t >= 10) {
    digitalWrite(ledVerde, HIGH); // Indica a temperatura Normal
    //digitalWrite(ledVermelho, LOW);
    //digitalWrite(ledAmarelo, LOW);
  } 
  else if (t < 10) {
    digitalWrite(ledAmarelo, HIGH); // Indica a temperatura Baixo
    //digitalWrite(ledVermelho, LOW);
    //digitalWrite(ledVerde, LOW);
  } 
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");

  delay(2000);
}