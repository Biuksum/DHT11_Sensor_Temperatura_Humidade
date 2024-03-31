#include "DHT.h"

#define DHTPIN D2      // pino de conexão
#define DHTTYPE DHT11  // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const int pinoRelay_1 = D0; //clima frio
const int pinoRelay_2 = D1; //clima quente

void setup() {
  Serial.begin(9600);
  Serial.println("Teste se sensor DHT!");
  dht.begin();

  pinMode(pinoRelay_1, OUTPUT);
  pinMode(pinoRelay_2, OUTPUT);
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
    digitalWrite(pinoRelay_1, HIGH); // Indica a temperatura Alta, ligar clima frio
    digitalWrite(pinoRelay_2, LOW);
    Serial.println("Temperatura alta, Ligar arcondicionado, resfriador");
  } 
  else if (t >= 15) {
    digitalWrite(pinoRelay_2, LOW); // Indica a temperatura Normal, desligar clima quente e frio
    digitalWrite(pinoRelay_1, LOW);
    Serial.println("Temperatura normal, Ligar aquecidor");
  } 
  else if (t < 15) {
    digitalWrite(pinoRelay_2, HIGH); // Indica a temperatura Baixo, ligar clima quente
    digitalWrite(pinoRelay_1, LOW);
    Serial.println("Temperatura baixa, ligar aquecidor");
  } 
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");

  delay(2000);
}