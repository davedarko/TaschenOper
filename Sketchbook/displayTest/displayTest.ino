// #define OLED_MOSI     27
// #define OLED_CLK      26

#define OLED_DC       14
#define OLED_RST      15
#define OLED_CS       22

#include <SPI.h>
#include <Adafruit_SH110X.h>

const int DW = 128;
const int DH = 64;

uint8_t count = 0; 
uint32_t last_encoder_millis = 0;

Adafruit_SH1106G display = Adafruit_SH1106G(DW, DH, &SPI1, OLED_DC, OLED_RST, OLED_CS);

void setup() {
  // put your setup code here, to run once:
  display.begin(0, true);
  display.clearDisplay();
  display.display();  // must clear before display, otherwise shows adafruit logo
  
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if( millis() - last_encoder_millis > 1000 ) {
    last_encoder_millis = millis();

    display.clearDisplay();
    display.setTextColor(SH110X_WHITE, SH110X_BLACK); // white text, black background
    display.setTextSize(2); // Draw 2X-scale text
    display.setCursor(0, 10);
    display.println(count++);
    display.display();
  }
  
}
