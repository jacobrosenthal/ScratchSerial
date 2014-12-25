#include <ScratchSerial.h>
#include <ringbuffer.h>

ScratchSerial::ScratchSerial(size_t _write, size_t _read, int _from, int _to){

  w = new ringbuffer(_write);
  r = new ringbuffer(_read);  

  x = new StreamBuffer(w,r);
  y = new StreamBuffer(r,w);

  from = _from;
  to = _to;
}

// size_t ScratchSerial::write(const uint8_t *buf, size_t size) {
//   return size;
// }

size_t ScratchSerial::write(uint8_t c)
{
  return x->write(c);
}

void ScratchSerial::flush()
{
  return x->flush();
}

int ScratchSerial::available() {
  return x->available();
}

int ScratchSerial::read() {
  return x->read();
}

// //TODO 
// int ScratchSerial::read(uint8_t *buf, size_t size) {
// }

int ScratchSerial::peek() 
{
  return x->peek();
}

void ScratchSerial::loop(){
  move(from, (*x));
  move((*y), to);
}

void ScratchSerial::move(Stream &stream, int scratch){
  //move data from stream to scratch 20 bytes or less at a time
  while(stream.available()){
    int idx = 0;
    int length = stream.available();

    length = length > 20 ? 20 : length;
    uint8_t buffer[length];

    while(idx<length){
      int c = stream.read();
      buffer[idx++] = c & 0xFF;
    }
    Bean.setScratchData(scratch, buffer, length);    
  }
}

void ScratchSerial::move(int scratch, Stream &stream)
{
  //move data from scratch to incoming buffer
  ScratchData thisScratch = Bean.readScratchData(scratch);
  bool matched = compareScratch( &thisScratch, &lastScratch );
  if ( false == matched )
  {
    lastScratch = thisScratch;
    
    int i = 0;
    while ( i < thisScratch.length ){
      stream.write(thisScratch.data[i++]);
    }
  }
}

//This function copyright Punchthrough, no idea the license
//https://punchthrough.com/bean/the-arduino-reference/readscratchdata/
bool ScratchSerial::compareScratch( ScratchData * scratch1, ScratchData * scratch2 )
{
  bool matched = true;
  
  if ( scratch1->length != scratch2->length )
  {
    matched = false;
  }
  else
  {
    int length = min( scratch1->length, scratch2->length );
    int i = 0;
    
    while ( i < length )
    {
      if ( scratch1->data[i] != scratch2->data[i] )
      {
        matched = false;
        i = length;
      }
      i++;
    }
  }
  
    return matched;
}