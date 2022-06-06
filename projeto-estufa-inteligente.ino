#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <Ticker.h>
#include "DHT.h"

// Coletando dados para conexão com servidor e internet.
#define FIREBASE_HOST "https://projeto-estufa-inteligente.firebaseio.com"
#define FIREBASE_AUTH "dYnmJGW4EZtUTuyX5jZw5o6VB9Gt73B8qS805T0m"
#define WIFI_SSID "Vits"
#define WIFI_PASSWORD "aquinaonene"
FirebaseData firebaseData; //Define FirebaseESP8266 data object

#define DHT_DATA_PIN 2
#define DHTTYPE DHT11

// Publique a cada 10 min
#define PUBLISH_INTERVAL 1000*60*10

//Váriaveis de controle do sistema
float tempMin = 15;
float tempMax = 25;
float humArMin = 70;
float humArMax = 85;
float humSoloMin = 25;
float humSoloMax = 80;

//portas digitais dos componentes
int cooler1 = 0;
int cooler2 = 4;
int lamp = 5;
int valv = 14;

//variaveis de valores dos sensores
int humidadeSolo = 0;
int humidadeAr = 0;
int temperatura = 0;

DHT dht(DHT_DATA_PIN, DHTTYPE);
Ticker ticker;
bool publishNewState = true;

void publish() {
    publishNewState = true;
}

void setupPins() {
  
    pinMode(cooler1, OUTPUT);
    pinMode(cooler2, OUTPUT);
    pinMode(lamp, OUTPUT);
    pinMode(valv, OUTPUT);
    
    digitalWrite(cooler1, HIGH);
    digitalWrite(cooler2, HIGH);
    digitalWrite(lamp, HIGH);
    digitalWrite(valv, HIGH);
    
    dht.begin();

}

void setupWifi() {

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Conectando");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.print("Conectado na rede: ");
    Serial.println(WIFI_SSID);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

void setupFirebase() {

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void setup() {
    Serial.begin(9600);

    setupPins();
    setupWifi();

    setupFirebase();

    // Registra o ticker para publicar de tempos em tempos
    ticker.attach_ms(PUBLISH_INTERVAL, publish);
}

void loop() {

    // Obtem os dados do sensor DHT e sensor humidade do solo
    humidadeAr = dht.readHumidity();
    temperatura = dht.readTemperature();
    humidadeSolo = analogRead(0);
    humidadeSolo = map(humidadeSolo, 1023, 0, 0, 200);
    //Logs na porta serial
    Serial.println("-------------------------");
    Serial.print("Temperatura: ");
    Serial.println(temperatura);
    Serial.print(" Umidade: ");
    Serial.println(humidadeAr);
    Serial.print(" Umidade Solo: ");
    Serial.println(humidadeSolo);

    ligaCooler();
    ligaLamp();
    ligaValv();

    if (WiFi.status() != WL_CONNECTED) {
        setupWifi(); //Configura o firebase
    };

    // Apenas publique quando passar o tempo determinado
    if (publishNewState) {

        Serial.println("Publicando novo estado!");

        if (!isnan(humidadeAr) && !isnan(temperatura)) {
            // Manda para o firebase
            Firebase.pushInt(firebaseData, "temperatura", temperatura);
            Firebase.pushInt(firebaseData, "humidadeAr", humidadeAr);
            Firebase.pushInt(firebaseData, "humidadeSolo", humidadeSolo);

            publishNewState = false;
        } else {
            Serial.println("Erro de Publicação");
        }
    }

    delay(200);

}

void ligaCooler() {
    if (humidadeAr > humArMax) {
        Firebase.setBool(firebaseData, "ativaCooler", true);
        digitalWrite(cooler1, LOW);
        digitalWrite(cooler2, LOW);
    } else if (humidadeAr < humArMin) {
        Firebase.setBool(firebaseData, "ativaCooler", false);
        digitalWrite(cooler1, HIGH);
        digitalWrite(cooler2, HIGH);
    }
}

void ligaLamp() {
    if (temperatura < tempMin) {
        Firebase.setBool(firebaseData, "ativaLampada", true);
        digitalWrite(lamp, LOW);
    } else if (temperatura > tempMax) {
        Firebase.setBool(firebaseData, "ativaLampada", false);
        digitalWrite(lamp, HIGH);
    }
}

void ligaValv() {
    if (humidadeSolo < humSoloMin) {
        Firebase.setBool(firebaseData, "ativaValvula", true);
        digitalWrite(valv, LOW);
    } else if (humidadeSolo > humSoloMax) {
        Firebase.setBool(firebaseData, "ativaValvula", false);
        digitalWrite(valv, HIGH);
    }
}
