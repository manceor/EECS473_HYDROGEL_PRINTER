#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "U8glib.h"
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
U8GLIB_ST7920_128X64_4X u8g(10);

void draw(void) {

  //u8g.setFont(u8g_font_unifont);
  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr( 0, 20, "Temperature");
  u8g.setPrintPos(0, 50);
  float temp = (mlx.readObjectTempC() * 1.6429) - 14.429;
  u8g.print(temp);
  u8g.print("*C");
}


void clearLCD(){
    u8g.firstPage();  
    do {
    } while( u8g.nextPage() );
}

void setup(void) {
  Serial.begin(9600);
  mlx.begin();
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

  clearLCD();
  
}

void loop(void) {
    u8g.firstPage(); 
  do {
    draw();
  } while( u8g.nextPage() );
  delay(500);
  //clearLCD();
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");

  Serial.println();
  delay(500);
}
