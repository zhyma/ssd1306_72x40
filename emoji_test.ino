/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-OLEDM0.42-1
Display is Hardward I2C 2-Wire I2C Interface 
Tested and worked with:
Works with Arduino 1.6.0 IDE  
Test OK : Arduino DUE,Arduino mega2560,Arduino UNO Board 
****************************************************/
#include "er_oled.h"

/*
  == Hardware connection for 4 PIN module==
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3V
  *3. SCL    ->    SCL
  *4. SDA    ->    SDA
*/

void setup() {
  /* display an image of bitmap matrix */
  er_oled_begin();

}

void loop() {
  for(uint16_t i=0; i < 720; i++){
      drawBitmap(jingjiu_flash, 0, 0, i, 72, 5);
  }
}
