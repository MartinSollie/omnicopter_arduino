#include <NewPing.h>
#include <Wire.h>

#define TRIGGER_PIN  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SLAVE_ADDRESS 0x55

NewPing sonar = NewPing(6, 7, MAX_DISTANCE);

int heightCm = 0;
byte data[2];

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  heightCm = sonar.ping_cm();
}

void requestEvent() {
  byte l = heightCm & 0xff;
  byte h = (heightCm & 0xff00) >> 8;
  data[0] = h;
  data[1] = l;  
  Wire.write(data, 2);  
}
