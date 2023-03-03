#include "DHT.h"
#include "Ubidots.h"


#define DHTPIN1 D1 //PIN for Data collection
#define DHTTYPE DHT11 // Sensor Type


#define TOKEN "BBFF-Ds3HqkwyQKuzS37o7EphxTTcJ8uRLT" // Put your Ubidots API TOKEN here
#define WIFISSID "XXXXX" //Insert Network Name.
#define PASSWORD "XXXXX" //Insert Network Password here.
Ubidots client(TOKEN);


DHT dht1(DHTPIN1, DHTTYPE);


void read_1()
{
  // Wait a few seconds between measurements.
delay(2000);

float h = dht1.readHumidity();

float t = dht1.readTemperature();

float f = dht1.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println("Failed to read from DHT1 sensor!");
return;
}
float hif = dht1.computeHeatIndex(f, h);

float hic = dht1.computeHeatIndex(t, h, false);
Serial.print("Humidity1: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature1: ");
Serial.print(t);
Serial.print(" *C ");
Serial.print(f);
Serial.print(" *F\t");
Serial.print("Heat index1: ");
Serial.print(hic);
Serial.print(" *C ");
Serial.print(hif);
Serial.println(" *F");
    client.add("Humidity 1 (%)", h );
    client.add("Temperature 1 (*C)", t );
    client.send();
}


void setup() {
  
Serial.begin(9600);
Serial.println("IoT Workshop-DHT11 Demo");

dht1.begin();
bool msg1;
bool msg2;
msg1=client.wifiConnect(WIFISSID, PASSWORD);
int i=0;
if(!msg1){
  Serial.println("Reconnecting");
  for(i=0;i<10;i++){
    msg2=client.wifiConnect(WIFISSID, PASSWORD);
    if(msg2){
      break;
    }
    else{
      Serial.println("Reconnecting");
      Serial.println("Attempt "+String(i+1));
    }
  }
}
if(i==11){
  Serial.println("Max Attempts Reached, displaying values on serial monitor without data upload");
}
}
void loop() {
read_1();

}
