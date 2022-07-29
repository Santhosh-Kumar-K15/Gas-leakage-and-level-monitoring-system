#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Enter auth , ssid and pass according to your project
char auth[] = "guqFsG2lNQL7IeJdUfob2mMKoJXb_JFk";
char ssid[] = "*****";
char pass[] = "*****";


const int buzzer = 2;
int smokeA0 = A0;

// Your threshold value. You might need to change it.
int sensorThres = 100;

void setup() {
 pinMode(buzzer, OUTPUT);
 pinMode(smokeA0, INPUT);
 Serial.begin(115200);
 Blynk.begin(auth,ssid,pass);
}

void loop() {
 int analogSensor = analogRead(smokeA0);

 Serial.print("Pin A0: ");
 Serial.println(analogSensor);
 // Checks if it has reached the threshold value
 if (analogSensor > sensorThres)
 {
    //tone(buzzer, 1000);
    //digitalWrite(buzzer,HIGH);
    Blynk.notify("Gas leakage");
 }
// else
// {
//    noTone(buzzer);
//    digitalWrite(buzzer,LOW);
// }
 delay(1000);
}
