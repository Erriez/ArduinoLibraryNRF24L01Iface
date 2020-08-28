/*
 * MIT License
 *
 * Copyright (c) 2020 Erriez
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
 * Source: https://github.com/Erriez/ErriezNRF24L01Iface
 */

#ifndef NRF24L01_IO_H__
#define NRF24L01_IO_H__

#include <Arduino.h>
#include "nRF24L01_regs.h"

class nRF24L01Iface
{
public:
    nRF24L01Iface(uint32_t spiClock, uint8_t csnPin);

protected:
    virtual uint8_t readRegister(uint8_t reg, uint8_t *buf, uint8_t len);
    virtual uint8_t readRegister(uint8_t reg);

    virtual void writeCommand(uint8_t cmd);
    virtual void writeRegister(uint8_t reg, uint8_t value);
    virtual void writeRegister(uint8_t reg, const uint8_t *buf, uint8_t len);

    virtual inline void beginTransaction();
    virtual inline void endTransaction();

private:
    uint32_t _spiClock;
    uint8_t  _csnPin;
};

#endif // NRF24L01_IO_H__
