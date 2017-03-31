#include <SBUS.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x50
#define NUM_CHANNELS 7
int i = 0;
byte ch[2*NUM_CHANNELS];
int chan[NUM_CHANNELS];
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
  for (i = 0; i < NUM_CHANNELS; i++) {
    chan[i] = sBus.getChannel(i+1);
    byte l = chan[i] & 0xff;
    byte h = (chan[i] & 0xff00) >> 8;
    ch[2*i] = h;
    ch[2*i+1] = l;
  }    
  Wire.write(ch, 2*NUM_CHANNELS);  
}
