#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//-------------------VARIABLES GLOBALES--------------------------
const char* ssid = "MOVISTAR_XXXX"; // Nombre de la red wifi.
const char* password = "123JFjhgsJAK7"; // Clave de la red wifi.
const char *host = "192.168.1.4"; // IP host

bool flanco_subida; // flanco ascendente del valor confirmado
bool flanco_bajada; // flanco descandente del valor confirmado

int ldrvalue = 0; // valor que se graba en la base de datos
byte cont = 0;
byte max_intentos = 50;

void setup() {
  // Inicia Serial
  Serial.begin(115200);
  pinMode(14, INPUT_PULLUP); // PIN 5: INPUT DE LA SEÑAL
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.println("\n");

  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) { //Cuenta hasta 50 si no se puede conectar lo cancela
    cont++;
    delay(500);
    Serial.print(".");
  }

  Serial.println("");

  if (cont < max_intentos) {  //Si se conectó
    Serial.println("********************************************");
    Serial.print("Conectado a la red WiFi: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("macAdress: ");
    Serial.println(WiFi.macAddress());
    Serial.println("*********************************************");
  }
  else { //No se conectó
    Serial.println("------------------------------------");
    Serial.println("Error de conexion");
    Serial.println("------------------------------------");
  }
}

void loop() {

  digitalWrite(LED_BUILTIN, LOW);
  if ((digitalRead(14) == 1) && (flanco_subida == 0)) {
    Serial.println("------SE DETECTÓ SEÑAL------");
    ldrvalue++;
    HTTPClient http;    //Declaramos nuestro objeto HTTPClient
    WiFiClient client;

    String LdrValueSend, postData;

    LdrValueSend = String(ldrvalue);   //Covertimos el string en un integer

    //Post Data
    postData = "ldrvalue=" + LdrValueSend;

    Serial.println("Mandando información a la base de datos...");
    http.begin(client, "http://192.168.1.4:8080/iclementem/UpdateDB.php");  //Ruta de nuestro .php
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");


    int httpCode = http.POST(postData);   //Send the request
    String payload = http.getString();    //Get the response payload
    Serial.println("Valor escrito=" + LdrValueSend);
    http.end();  // Cerramos la conexión
  }
  flanco_subida = digitalRead(14);



}
