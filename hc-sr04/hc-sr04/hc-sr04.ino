#include <NewPing.h>
#include <Wire.h>

#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


NewPing sonar = NewPing(6, 7, MAX_DISTANCE);

int heightCm = 0; 

void setup() {
  Wire.begin(6);
  Serial.begin(9600);
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  heightCm = sonar.ping_cm();
  Serial.print("Ping: ");
  Serial.print(heightCm); 
  Serial.println("cm");

  Wire.write(sonar.ping_cm());
}
