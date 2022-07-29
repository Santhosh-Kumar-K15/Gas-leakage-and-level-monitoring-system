#include <Arduino.h>
#include "HX711.h"
#include <BlynkSimpleEsp8266.h>

//Enter auth,ssid and pass according to your project
char auth[] = "AxapiQSfhBFIOFC4IsChvfSMWWAmDiqi";
char ssid[] = "******";
char pass[] = "******";

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   
  Serial.println("HX711 Demo");
  Serial.println("Initializing the scale");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5)); 

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1); 
            
  scale.set_scale(470.562);
                 
  scale.tare();             

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);      

  Serial.println("Readings:");
}

void loop() {
  
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);

   if(scale.read()>100)
  {
       Serial.println("low gas");
       Serial.print(scale.read());
       Blynk.notify("book your gas cylinder");
       delay(1000); 
  }
  Blynk.virtualWrite(V1,scale.read());
  Blynk.run();
  
  scale.power_down();            
  delay(5000);
  scale.power_up();
}
