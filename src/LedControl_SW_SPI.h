#ifndef LEDCONTROL_SW_SPI_H
#define LEDCONTROL_SW_SPI_H

#include "LedControl.h"

class LedControl_SW_SPI : public LedControl
{
  private:
    /* Data is shifted out of this pin*/
    int SPI_MOSI;
    /* The clock is signaled on this pin */
    int SPI_CLK;
    void spiTransfer(int addr, byte opcode, byte data);

  public:
    void begin(int dataPin, int clkPin, int csPin, int numDevices);
};

#endif // LEDCONTROL_SW_SPI_H