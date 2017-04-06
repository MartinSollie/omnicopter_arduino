#include <SBUS.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x50
#define TIMEOUT_MS 200 

/*
 * 7 channels: 4 for sticks, 1 for arm, 2 for mode switches
 * 1 byte for failsafe status (bit 0) and timeout status (bit 1)
 */
#define NUM_BYTES 15
int i = 0;
byte ch[NUM_BYTES];
int chan[7];
SBUS sBus(Serial);

void setup() {
  sBus.begin();
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
}

// this is timer2, which triggers every 1ms and processes the incoming SBUS datastream
ISR(TIMER2_COMPA_vect)
{
  sBus.process();
}

void loop(){}

void requestEvent() {
  for (i = 0; i < 7; i++) {
    chan[i] = sBus.getChannel(i+1);
    byte l = chan[i] & 0xff;
    byte h = (chan[i] & 0xff00) >> 8;
    ch[2*i] = h;
    ch[2*i+1] = l;
  }
  ch[14] = 0xff & sBus.getFailsafeStatus(); // 1 = failsafe, 0 = no failsafe
  if(millis() - sBus.getLastTime() > TIMEOUT_MS){
    ch[14] |= 0b10;
  }
  Wire.write(ch, NUM_BYTES);  
}
