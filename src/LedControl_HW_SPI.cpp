/*
 *    LedControl.cpp - A library for controling Leds with a MAX7219/MAX7221
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

#include "LedControl_HW_SPI.h"
#include <SPI.h>

LedControl_HW_SPI::LedControl_HW_SPI() : LedControl() {};

void LedControl_HW_SPI::begin(int csPin, int numDevices, unsigned long spiSpeedMax)
{
    SPI_CS = csPin;
    if (numDevices <= 0 || numDevices > 8)
        numDevices = 8;
    maxDevices = numDevices;
    speedMaximum = spiSpeedMax;
    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(SPI_CS, OUTPUT);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin();
    digitalWrite(SPI_CS, HIGH);
    for (int i = 0; i < 64; i++)
        status[i] = 0x00;
    for (int i = 0; i < maxDevices; i++)
    {
        spiTransfer(i, LEDCTL_OP_DISPLAYTEST, 0);
        //scanlimit is set to max on startup
        setScanLimit(i, 7);
        //decode is done in source
        spiTransfer(i, LEDCTL_OP_DECODEMODE, 0);
        clearDisplay(i);
        //we go into shutdown-mode on startup
        shutdown(i, true);
    }
}


void LedControl_HW_SPI::spiTransfer(int addr, volatile byte opcode, volatile byte data)
{
    //Create an array with the data to shift out
    int offset = addr * 2;
    int maxbytes = maxDevices * 2;

    for (int i = 0; i < maxbytes; i++)
        spidata[i] = (byte)0;
    //put our device data into the array
    spidata[offset + 1] = opcode;
    spidata[offset] = data;
    //enable the line
    digitalWrite(SPI_CS, LOW);
    //Now shift out the data
    SPI.beginTransaction(SPISettings(speedMaximum, MSBFIRST, SPI_MODE0));
    for (int i = maxbytes; i > 0; i--)
        SPI.transfer(spidata[i - 1]);
    //latch the data onto the display
    digitalWrite(SPI_CS, HIGH);
    SPI.endTransaction();
}
