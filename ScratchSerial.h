#ifndef _SCRATCHSERIAL_H
#define _SCRATCHSERIAL_H

#include "Arduino.h"
#include "StreamBuffer.h"

class ScratchSerial : public Stream {
  public:
    ScratchSerial(size_t _write, size_t _read, int _from, int _to);

    size_t write(uint8_t c);
    // size_t write(const uint8_t *buf, size_t size);

    int available();
    int read();
    // int read(uint8_t *buf, size_t size);
    int peek();
    void flush();
    void loop();

  private:
    ScratchData lastScratch;
    ringbuffer *w;
    ringbuffer *r;
    StreamBuffer *x;
    StreamBuffer *y;
    int to;
    int from;
    
    void move(Stream &stream, int scratch);
    void move(int scratch, Stream &stream);
    bool compareScratch( ScratchData * scratch1, ScratchData * scratch2 );

};

#endif // _SCRATCHSERIAL_H