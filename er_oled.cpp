/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#include <Wire.h>
#include "er_oled.h"
#include "Arduino.h"

void sendCommand(uint8_t cmd){
  Wire.beginTransmission(OLED_ADDRESS); // begin transmitting
  Wire.write(OLED_COMMAND_MODE);//data mode
  Wire.write(cmd);
  Wire.endTransmission();    // stop transmitting
}

void sendData(uint8_t data) {
  Wire.beginTransmission(OLED_ADDRESS); // begin transmitting
  Wire.write(OLED_DATA_MODE);//data mode
  Wire.write(data);
  Wire.endTransmission();    // stop transmitting
}

void er_oled_begin()
{
  Wire.begin();
  for (uint8_t i = 0; i < OLED_INIT_LEN; i++){
    sendCommand(pgm_read_byte(&OLED_INIT_CMD[i]));
  }
  sendCommand(0xaf);//--turn on oled panel
}

void setCursorXY(byte X, byte Y){
  // Y up to down,    unit: 1 page (8 pixels)
  // X left to right, unit: 1 seg  (1 pixel)
    sendCommand(0x0c + (X & 0x0F));     //set column lower address
    sendCommand(0x11 + ((X>>4)&0x0F));  //set column higher address
    sendCommand(0xB0 + Y);                //set page address 
}

void drawBitmap(const uint8_t *bitmap, uint8_t X, uint8_t Y, uint16_t bitmap_offset_x, uint8_t w, uint8_t h){
  setCursorXY(X, Y);
  for(uint16_t i = 0; i<h; i++) {
    for (uint16_t j = 0; j< w; j++){
        uint16_t idx = (bitmap_offset_x+j)%499+499*i;
        sendData(pgm_read_byte(&bitmap[idx]));
    }
    setCursorXY(X, ++Y);
  }
}
