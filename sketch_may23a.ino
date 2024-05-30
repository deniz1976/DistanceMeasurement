#include "thingProperties.h"

const int trigPin = 5;
const int echoPin = 18;
const int relayPin = 19; 

long duration;
float distanceCm;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(relayPin, OUTPUT); 
  digitalWrite(relayPin, LOW); 
  
  delay(1500); 

  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;

  int tankHeight = 10; 
  float percentage = (tankHeight - distanceCm) / tankHeight * 100;
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;
  water = percentage; 

  
  if (water < 30) {
    digitalWrite(relayPin, HIGH);
    Serial.println("Adding water...");
  } else if (water >= 70) {
    digitalWrite(relayPin, LOW);
    Serial.println("Water level is good. ( above 70%)");
  }

  
  systemState = true;
  delay(1000);
}

void onWaterChange() {
  
}

void onAddWaterChange() {
  if (addWater) {
    Serial.println("Adding water...");
    digitalWrite(relayPin, HIGH);
    delay(5000); 
    digitalWrite(relayPin, LOW);
    addWater = false; 
    ArduinoCloud.update(); 
  } else {
    Serial.println("Water level is good. ( above 70%)");
    digitalWrite(relayPin, LOW);
  }
}

void onSystemStateChange() {
  if (systemState) {
    Serial.println("System is ON");
  } else {
    Serial.println("System is OFF");
  }
}
