/*
 * MIT License
 *
 * Copyright (c) 2018 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * This a low-level nRF24L01(+) register read/write example for advanced users
 *
 * Source: https://github.com/Erriez/ArduinoLibraryNRF24L01Iface
 */

#include <Arduino.h>
#include <nRF24L01Iface.h>

// Create derived class from the nRF24L01Iface class to define some basic register
// read/write functionality by using the SPI interface.
class nRF24L01Example : nRF24L01Iface
{
public:
    // Constructor, initialize base class with SPI clock and SPI chip-select
    nRF24L01Example(uint32_t spiClock, uint8_t csnPin) :
            nRF24L01Iface(spiClock, csnPin)
    {
    };

    // Read status register
    uint8_t readStatus() {
      // Read status register
      return readRegister(REG_STATUS);
    }

    // Read from config register
    uint8_t readConfig() {
      // Read config register
      return readRegister(REG_CONFIG);
    }

    // Write to config register
    void writeConfig(uint8_t val) {
      // Write to config register
      writeRegister(REG_CONFIG, val);
    }

    // Read from pipe0 registers with 5 Byte address width
    void readWritePipe0(uint8_t *address) {
      readRegister(REG_TX_ADDR, address, 5);
    }

    // Write to TX pipe (0) registers
    void openWritePipe0(const uint8_t *address) {
      // Write 5 Bytes transmit pipe
      // Now pipe 0 cannot be used for receive
      writeRegister(REG_TX_ADDR, address, 5);
    }

    // Write commands
    void flushRxFifo() {
      // Write flush receive command
      writeCommand(CMD_FLUSH_RX);
    }
};

// SPI chip select pin
#define CSN_PIN     8

// Create object and initialize with SPI clock and SPI chip-select pin
static nRF24L01Example radio((uint32_t)10000000UL, CSN_PIN);

// Define an address pipe for transmit
static const uint8_t pipe[5] = { 0x55, 0xa5, 0x5a, 0xaa, 0x99 };

// Print a 8-bit hexadecimal value
static void printHex(uint8_t val)
{
  Serial.print(F("0x"));
  if (val < 0x10) {
    Serial.print(F("0"));
  }
  Serial.println(val, HEX);
}

// Print a 8-bit buffer
static void printBuffer(const uint8_t *buf, uint8_t len)
{
  for (uint8_t i = 0; i < len; i++) {
    Serial.print(F("  "));
    Serial.print(i);
    Serial.print(F(": "));
    printHex(buf[i]);
  }
}

void setup()
{
  uint8_t configReg;

  Serial.begin(115200);
  Serial.println(F("Low-level nRF24L01(+) register access example"));

  Serial.print(F("STATUS: "));
  printHex(radio.readStatus());

  Serial.print(F("CONFIG: "));
  printHex(radio.readConfig());

  Serial.println(F("Write power-up bit 1 to CONFIG register..."));
  radio.writeConfig(1<<1);

  Serial.print(F("CONFIG: "));
  configReg = radio.readConfig();
  printHex(configReg);
  if (configReg != 0x02) {
    Serial.println(F("Error: Verification config register failed"));
    while (1)
      ;
  }

  Serial.println(F("Flush RX FIFO..."));
  radio.flushRxFifo();

  Serial.println(F("Open write pipe address..."));
  radio.openWritePipe0(pipe);

  Serial.println(F("Configured write pipe address: "));
  uint8_t pipeReadback[5];
  radio.readWritePipe0(pipeReadback);
  printBuffer(pipeReadback, sizeof(pipeReadback));

  if (memcmp(pipe, pipeReadback, sizeof(pipe)) != 0) {
    Serial.println(F("Error: Verification write pipe registers failed"));
    while (1)
      ;
  }

  Serial.println(F("End example"));
}

void loop()
{
}
