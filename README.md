#ScratchSerial

Arduino library for the [Punch Through LightBlue Bean](https://punchthrough.com/bean/). Turns Scratch Characteristics into a Serial port. Implements Punct Through's Scratch [Read](https://punchthrough.com/bean/the-arduino-reference/readscratchdata/) an [Write](https://punchthrough.com/bean/the-arduino-reference/setscratchdata/) API.


##Note1
There is a pretty major limitation to using scratch characteristics. The data you write MUST change write to write in order to be seen as new. IE if you send "hello" twice in a row, only the first will be passed through!

##Note2
This libarary is very much in beta. It hasn't been fully tested nor are all Serial class methods implemented yet.

##Install
As usual, download zip, unzip and rename to remove the dash character and place in your Arduino Libraries folder, on MacOSX ~/Documents/Arduino/libraries/

##Use
Create a ScratchSerial supplied with the size of buffers you like, an incoming and outgoing scratch number (1-5). As always the bigger the buffer the more of your working memory you're using up so adjust to taste.
```cpp
ScratchSerial stream(readBufferSize, writeBufferSize, readScratch, writeScratch);
```

Then in your loop be sure to 'service' the ScratchSerial class by calling .loop(). It needs to go look for data on incoming Scratch Characteristic as well as move data over from the buffer to the destination Scratch Characteristic.
```cpp
stream.loop();
```

Thats it. You can now .write or .read or pass your ScratchSerial object to any class that accepts a Serial object. Here well just echo it all back out.
```cpp
  while(stream.available()){
    stream.write(stream.read());
  }

```
