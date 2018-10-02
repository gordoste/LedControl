#ifndef LEDCONTROL_HW_SPI_H
#define LEDCONTROL_HW_SPI_H

#include "LedControl.h"

class LedControl_HW_SPI : public LedControl {
  public:
  /* 
         * Create a new controler 
         * Params :
         * csPin		pin for selecting the device 
         * numDevices           maximum number of devices that can be controled
         * spiSpeedMax          Maximum SPI communication speed (passed to SPISettings)
         */
  void begin(int csPin, int numDevices = 1, unsigned long spiSpeedMax = 10000000);

  private:
  /* Max SPI communication speed passed to SPISettings() */
  unsigned long speedMaximum;
  void spiTransfer(int addr, byte opcode, byte data);

};

#endif // LEDCONTROL_HW_SPI_H