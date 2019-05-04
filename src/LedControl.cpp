#include "LedControl.h"

int LedControl::getDeviceCount() {
  return maxDevices;
}

void LedControl::shutdown(int addr, bool b) {
  if(addr<0 || addr>=maxDevices)
    return;
  if(b)
    spiTransfer(addr, LEDCTL_OP_SHUTDOWN,0);
  else
    spiTransfer(addr, LEDCTL_OP_SHUTDOWN,1);
}

void LedControl::setScanLimit(int addr, int limit) {
  if(addr<0 || addr>=maxDevices)
    return;
  if(limit>=0 && limit<8)
    spiTransfer(addr, LEDCTL_OP_SCANLIMIT,limit);
}

void LedControl::setIntensity(int addr, int intensity) {
  if(addr<0 || addr>=maxDevices)
    return;
  if(intensity>=0 && intensity<16)	
    spiTransfer(addr, LEDCTL_OP_INTENSITY,intensity);
}

void LedControl::clearDisplay(int addr) {
  int offset;

  if(addr<0 || addr>=maxDevices)
    return;
  offset=addr*8;
  for(int i=0;i<8;i++) {
    status[offset+i]=0;
    spiTransfer(addr, i+1,status[offset+i]);
  }
}

void LedControl::setLed(int addr, int row, int column, boolean state) {
  int offset;
  byte val=0x00;

  if(addr<0 || addr>=maxDevices)
    return;
  if(row<0 || row>7 || column<0 || column>7)
    return;
  offset=addr*8;
  val=B10000000 >> column;
  if(state)
    status[offset+row]=status[offset+row]|val;
  else {
    val=~val;
    status[offset+row]=status[offset+row]&val;
  }
  spiTransfer(addr, row+1,status[offset+row]);
}

void LedControl::setRow(int addr, int row, byte value) {
  int offset;
  if(addr<0 || addr>=maxDevices)
    return;
  if(row<0 || row>7)
    return;
  offset=addr*8;
  status[offset+row]=value;
  spiTransfer(addr, row+1,status[offset+row]);
}

void LedControl::setColumn(int addr, int col, byte value) {
  byte val;

  if(addr<0 || addr>=maxDevices)
    return;
  if(col<0 || col>7) 
    return;
  for(int row=0;row<8;row++) {
    val=value >> (7-row);
    val=val & 0x01;
    setLed(addr,row,col,val);
  }
}

void LedControl::setDigit(int addr, int digit, byte value, boolean dp) {
  int offset;
  byte v;

  if(addr<0 || addr>=maxDevices)
    return;
  if(digit<0 || digit>7 || value>15)
    return;
  offset=addr*8;
  v=pgm_read_byte_near(charTable + value); 
  if(dp)
    v|=B10000000;
  status[offset+digit]=v;
  spiTransfer(addr, digit+1,v);
}

void LedControl::setChar(int addr, int digit, char value, boolean dp) {
  int offset;
  byte index,v;

  if(addr<0 || addr>=maxDevices)
    return;
  if(digit<0 || digit>7)
    return;
  offset=addr*8;
  index=(byte)value;
  if(index >127) {
    //no defined beyond index 127, so we use the space char
    index=32;
  }
  v=pgm_read_byte_near(charTable + index); 
  if(dp)
    v|=B10000000;
  status[offset+digit]=v;
  spiTransfer(addr, digit+1,v);
}