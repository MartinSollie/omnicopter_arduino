#include <SBUS.h>
#include <Wire.h>
#define SLAVE_ADDRESS 0x50
int i = 0;
byte ch0[2], ch1[2], ch2[2], ch3[2], ch4[2], ch5[2], ch6[2], ch7[2], ch8[2], ch9[2], ch10[2], ch11[2], ch12[2], ch13[2], ch14[2], ch15[2];
byte* ch[] = {ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15};
int chan0, chan1, chan2, chan3,chan4, chan5, chan6, chan7, chan8, chan9, chan10, chan11, chan12, chan13, chan14, chan15;
int chan[] = {chan0, chan1, chan2, chan3, chan4, chan5, chan6, chan7, chan8, chan9, chan10, chan11, chan12, chan13, chan14, chan15};
int registerAddr;
SBUS sBus(Serial);

void setup() {
  sBus.begin();
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveRegister);
}

// this is timer2, which triggers every 1ms and processes the incoming SBUS datastream
ISR(TIMER2_COMPA_vect)
{
  sBus.process();
}

void loop()
{
  delay(30);
  for (i = 0; i < 16; i++) {
    chan[i] = sBus.getChannel(i);
    byte l = chan[i] & 0xff;
    byte h = (chan[i] & 0xff00) >> 8;
    ch[i][0] = h;
    ch[i][1] = l;
  }
}
void receiveRegister(int x){
  registerAddr = Wire.read();  
}
void requestEvent() {

  //Wire.write(chan[registerAddr]);
  
  for (i = 0; i < 16; i++){
    
    Wire.write(ch[i], 2);  
    

  }
}
