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
 * Nordic nRF24L01(+) register read/write library for Arduino
 *
 * Source: https://github.com/Erriez/ArduinoLibraryNRF24L01Iface
 */

#include <SPI.h>

#include "nRF24L01Iface.h"

nRF24L01Iface::nRF24L01Iface(uint32_t spiClock, uint8_t csnPin) :
        _csnPin(csnPin), _spiClock(spiClock)
{
  // CSN high to disable SPI chip select
  digitalWrite(_csnPin, HIGH);

  // Configure SPI chip-select pin
  pinMode(_csnPin, OUTPUT);

  // Initialize SPI
  SPI.begin();
}

uint8_t nRF24L01Iface::readRegister(uint8_t reg, uint8_t* buf, uint8_t len)
{
  uint8_t status = 0xFF;

  if (reg < NUM_REGISTERS) {
    beginTransaction();
    status = SPI.transfer(CMD_R_REGISTER | reg);
    while (len--) {
      *buf++ = SPI.transfer(0xff);
    }
    endTransaction();
  }

  return status;
}

uint8_t nRF24L01Iface::readRegister(uint8_t reg)
{
  uint8_t result = 0xFF;

  if (reg < NUM_REGISTERS) {
    beginTransaction();
    SPI.transfer(CMD_R_REGISTER | reg);
    result = SPI.transfer(0xff);
    endTransaction();
  }

  return result;
}

void nRF24L01Iface::writeCommand(uint8_t cmd)
{
  beginTransaction();
  (void)SPI.transfer(cmd);
  endTransaction();
}

void nRF24L01Iface::writeRegister(uint8_t reg, uint8_t value)
{
  // Check valid reg, but can't generate a user error
  if (reg < NUM_REGISTERS) {
    beginTransaction();
    (void) SPI.transfer(CMD_W_REGISTER | reg);
    (void) SPI.transfer(value);
    endTransaction();
  }
}

void nRF24L01Iface::writeRegister(uint8_t reg, const uint8_t *buf, uint8_t len)
{
  // Check valid reg, but can't generate a user error
  if (reg < NUM_REGISTERS) {
    beginTransaction();
    (void) SPI.transfer(CMD_W_REGISTER | reg);
    while (len--) {
      (void) SPI.transfer(*buf++);
    }
    endTransaction();
  }
}

void nRF24L01Iface::beginTransaction()
{
  SPI.beginTransaction(SPISettings(_spiClock, MSBFIRST, SPI_MODE0));

  // SPI chip-select LOW
  digitalWrite(_csnPin, LOW);
  delayMicroseconds(1);
}

void nRF24L01Iface::endTransaction()
{
  // SPI chip-select HIGH
  digitalWrite(_csnPin, HIGH);
  delayMicroseconds(1);

  SPI.endTransaction();
}
