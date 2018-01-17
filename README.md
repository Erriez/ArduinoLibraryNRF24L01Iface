# Low-level nRF24L01(+) register read/write library for Arduino

This is a low-level Arduino library to read and write nRF24L01(+) registers 
by using a SPI interface. It should be used in combination with a derived class 
with a higher level functional API.

## Hardware
A Nordic nRF24L01 or nRF24L01(+) 2.4GHz wireless transceiver connected to an 
Arduino board.

![alt text](https://raw.githubusercontent.com/Erriez/ArduinoLibraryNRF24L01Iface/master/extras/FritzingRotary.png "Nordic nRF24L01(+) - Arduino UNO schematic")

## Example
nRF24L01(+) Interface | ["RegisterAccess"](https://github.com/Erriez/ArduinoLibraryNRF24L01Iface/blob/master/examples/RegisterAccess/RegisterAccess.ino)

## Usage

### Includefile
```c++
#include <nRF24L01Iface.h>
```

### Derive nRF24L01Iface class
```c++
class nRF24L01Example : nRF24L01Iface
{
public:
    // Constructor, initialize base class with SPI clock and SPI chip-select
    nRF24L01Example(uint32_t spiClock, uint8_t csnPin) :
            nRF24L01Iface(spiClock, csnPin)
    {
    };
};
```

### Create an object from the custom derived class
```c++
// SPI chip select pin
#define CSN_PIN     8
  
// Create object and initialize with SPI clock and SPI chip-select pin
static nRF24L01Example radio((uint32_t)10000000UL, CSN_PIN);
```

### Use the class in an application
```c++
// Read status register
uint8_t status = radio.readStatus();
  
// Read config register
uint8_t status = radio.readConfig();
  
// Define an address pipe for transmit
const uint8_t pipe[5] = { 0x55, 0xa5, 0x5a, 0xaa, 0x99 };
  
// Configure write pipe0
radio.openWritePipe0(pipe);
  
// Read write pipe0 back
uint8_t pipeReadback[5];
radio.readWritePipe0(pipeReadback);
```

## Library installation
1. Start the Arduino IDE.
2. Download the latest version from:  
   https://github.com/Erriez/ArduinoLibraryNRF24L01Iface/archive/master.zip
3. Click Sketch | Include Library | Add .ZIP Library... and select this ZIP.
5. Run the example.
