#include <ScratchSerial.h>

int readBufferSize = 50;
int writeBufferSize = 50;
int readScratch = 1;
int writeScratch = 1;
ScratchSerial stream(readBufferSize, writeBufferSize, readScratch, writeScratch);

void setup() 
{
  Serial.begin();
}

void loop() 
{
  //give some program stream instead of Serial, and all that will pop out of defined scratch
  //well mock that by just echoing
  while(stream.available()){
    stream.write(stream.read());
  }

  //we need to service the stream so it can check the characteristic for data and
  //push any outgoing to the characteristic. This should happen as often as possible so be
  //wary of delays in your code, or writing more than y
  stream.loop();
}