#include <stdint.h>
#include <Wire.h>

#define BUS_MAXDATA             420

static uint8_t    txFlag        = 0x00;
static uint16_t   dataLength    = 0;
static uint8_t    data[BUS_MAXDATA];

bool BusWriteCh(char c) {
  if(txFlag != 0x00) { return false; }
  if(dataLength + 1 > BUS_MAXDATA) { return false; }
  data[dataLength] = c;
  dataLength += 1;
  return true;
}

bool BusWrite(uint8_t chunk) {
  if(txFlag != 0x00) { return false; }
  if(dataLength + 1 > BUS_MAXDATA) { return false; }
  data[dataLength] = chunk;
  dataLength += 1;
  return true;
}

bool BusWrite(int8_t chunk) {
  if(txFlag != 0x00) { return false; }
  if(dataLength + 1 > BUS_MAXDATA) { return false; }
  data[dataLength] = chunk;
  dataLength += 1;
  return true;
}

bool BusWrite(int16_t chunk) {
  if(txFlag != 0x00) { return false; }
  if(dataLength + 2 > BUS_MAXDATA) { return false; }
  data[dataLength+0] = ((chunk >> 8) & 0x00ff);
  data[dataLength+1] = (chunk & 0x00ff);
  dataLength += 2;
  return true;
}

bool BusWrite(uint16_t chunk) {
  if(txFlag != 0x00) { return false; }
  if(dataLength + 2 > BUS_MAXDATA) { return false; }
  data[dataLength+0] = ((chunk >> 8) & 0x00ff);
  data[dataLength+1] = (chunk & 0x00ff);
  dataLength += 2;
  return true;
}

bool BusWrite(uint32_t chunk) {
  if(txFlag != 0x00) { return false; }
  if(dataLength + 4 > BUS_MAXDATA) { return false; }
  data[dataLength+0] = ((chunk >> 24) & 0x000000ff);
  data[dataLength+1] = ((chunk >> 16) & 0x000000ff);
  data[dataLength+2] = ((chunk >> 8) & 0x000000ff);
  data[dataLength+3] = (chunk & 0x000000ff);
  dataLength += 4;
  return true;
}

bool BusWrite(int32_t chunk) {
  if(txFlag != 0x00) { return false; }
  if(dataLength + 4 > BUS_MAXDATA) { return false; }
  data[dataLength+0] = ((chunk >> 24) & 0x000000ff);
  data[dataLength+1] = ((chunk >> 16) & 0x000000ff);
  data[dataLength+2] = ((chunk >> 8) & 0x000000ff);
  data[dataLength+3] = (chunk & 0x000000ff);
  dataLength += 4;
  return true;
}
void receiveEvent(int count) {

  if(Wire.available() != 2) { return; }
  uint8_t reg = Wire.read();
  uint8_t value = Wire.read();
  
  switch(reg) {
    case 0x00:
      txFlag = value;
      if(txFlag == 0x00) {
        dataLength = 0;
      }
      
      break;
    default:
      break;
  }
}

void requestEvent() {
  uint8_t reg = Wire.read();

  if(reg == 0x00) {
    Wire.write(txFlag);
  }
  else if(reg == 0x01) {
      Wire.write((uint8_t)((dataLength >> 8) & 0x00ff));
      Wire.write((uint8_t)(dataLength & 0x00ff));
  }
  else if(reg >= 0x10) {
    uint16_t start = (reg - 0x10);
    uint16_t stop = min(start + 32, dataLength);
    for(uint16_t i = start; i < stop; ++i) {
      Wire.write(data[i]);
    }
  }
}

