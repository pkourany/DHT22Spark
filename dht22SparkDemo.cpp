// This #include statement was automatically added by the Spark IDE.
#include "dht22Spark.h"

int tAndH, humi, temp;
int dht22Pin = D4;

dht22Spark dht22(D4);

void setup() {
    Serial.begin(9600);
	  dht22.init();
    Spark.variable("temperature", &temp, INT);
    Spark.variable("humidity", &humi, INT);
} 


void loop() {
    delay(2000);
    tAndH = dht22.readValues();
    if (tAndH == -1)
        return;
	temp = dht22.getCelsius();
	humi = dht22.getHumidity();
    Serial.print("temp:");
    Serial.print(temp);
    Serial.print("  humi:");
    Serial.println(humi);
    //erial.print(" tAndH:");
   // Serial.println(tAndH, HEX);
}
