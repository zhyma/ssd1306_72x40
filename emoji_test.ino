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

uint8_t oled_buf[WIDTH * HEIGHT / 8];

void setup() {
  Serial.begin(9600);
  Serial.print("OLED Example\n");
  Wire.begin();
  
  /* display an image of bitmap matrix */
  er_oled_begin();
  er_oled_clear(oled_buf);

}

void loop() {
load_bitmap(0, 0, bmp_l, 72, 40, oled_buf);
er_oled_display(oled_buf);
delay(1000);

}

void load_bitmap(uint8_t x,uint8_t y,const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer)
{
  uint8_t i, j, byteWidth = (chWidth + 7)/8;
  for(j = 0;j < chHeight;j++){
    for(i = 0;i <chWidth;i++){
      if(pgm_read_byte(pBmp + j * byteWidth + i / 8) & (128 >> (i & 7))){
        er_oled_pixel(x + i,y + j, 1, buffer);
      }
    }
  }   
}
