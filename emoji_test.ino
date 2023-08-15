/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-OLEDM0.42-1
Display is Hardward I2C 2-Wire I2C Interface 
Tested and worked with:
Works with Arduino 1.6.0 IDE  
Test OK : Arduino DUE,Arduino mega2560,Arduino UNO Board 
****************************************************/
#include <Wire.h>
#include "er_oled.h"

/*
  == Hardware connection for 4 PIN module==
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3V
  *3. SCL    ->    SCL
  *4. SDA    ->    SDA

 == Hardware connection for 7 PIN module==
 Note:The module needs to be jumpered to an I2C interface.
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3V
  *3. SCL    ->    SCL
  *4. SDA    ->    SDA
  *5. RES    ->    8 
  *6. DC     ->    GND 
  *7. CS     ->    GND  
*/


void setup() {
//  Serial.begin(9600);
//  Serial.print("OLED Example\n");
  Wire.begin();
  
  /* display an image of bitmap matrix */
  er_oled_begin();
//  er_oled_clear(oled_buf);

}

void loop() {
  for(uint16_t i=0; i < 720; i++){
      drawBitmap(jingjiu_flash, 0, 0, i, 72, 5);
  }
}

void setCursorXY(byte X, byte Y){
  // Y up to down,    unit: 1 page (8 pixels)
  // X left to right, unit: 1 seg  (1 pixel)
    command(0x0c + (X & 0x0F));     //set column lower address
    command(0x11 + ((X>>4)&0x0F));  //set column higher address
    command(0xB0 + Y);                //set page address 
}

void drawBitmap(const byte *bitmap, uint8_t X, uint8_t Y, uint16_t bitmap_offset_x, uint8_t w, uint8_t h){
  setCursorXY(X, Y);
  for(uint16_t i = 0; i<h; i++) {
    for (uint16_t j = 0; j< w; j++){
        uint16_t idx = (bitmap_offset_x+j)%499+499*i;
        data(pgm_read_byte(&bitmap[idx]));
//          data(bitmap[idx]);
    }
    setCursorXY(X, ++Y);
  }
}

//void load_bitmap(uint16_t x,uint8_t y,const uint8_t *bitmap, uint16_t bitmap_w, uint8_t bitmap_h, uint8_t* buffer)
//{
//  for(uint8_t i = 0;i < 5;i++){
//    for(uint8_t j = 0;j <72;j++){
////      uint16_t idx = (x+y*x+i*bitmap_w+j)%(bitmap_w*bitmap_h);
//        uint16_t idx = (x+j)%bitmap_w+bitmap_w*i;
//        buffer[i*72+j] = pgm_read_byte(&bitmap[idx]);
//    }
//  }   
//}
