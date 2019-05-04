/*
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LEDCONTROL_HW_SPI_H
#define LEDCONTROL_HW_SPI_H

#include "LedControl.h"

class LedControl_HW_SPI : public LedControl {
  private:
    /* Max SPI communication speed passed to SPISettings() */
    unsigned long speedMaximum;
    void spiTransfer(int addr, byte opcode, byte data);
  public:
    LedControl_HW_SPI();
    /* 
     * Create a new controler 
     * Params :
     * csPin		pin for selecting the device 
     * numDevices           maximum number of devices that can be controled
     * spiSpeedMax          Maximum SPI communication speed (passed to SPISettings)
    */
    void begin(int csPin, int numDevices = 1, unsigned long spiSpeedMax = 10000000);
};

#endif // LEDCONTROL_HW_SPI_H