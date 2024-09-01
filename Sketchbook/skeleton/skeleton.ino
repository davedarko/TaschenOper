#include <Adafruit_NeoPixel.h>
// unsurprisingly easy to find in library manager
#include <Adafruit_SH110X.h>

// https://github.com/mathertel/RotaryEncoder
#include <RotaryEncoder.h>

#define LED_PIN    19
#define LED_COUNT  25
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// oled
#define OLED_DC  14
#define OLED_RST 15
#define OLED_CS  22
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &SPI1, OLED_DC, OLED_RST, OLED_CS);
boolean displayUpdateNeeded = true;

// Rotary encoder
#define PIN_ROTA 17
#define PIN_ROTB 18
RotaryEncoder encoder(PIN_ROTA, PIN_ROTB, RotaryEncoder::LatchMode::FOUR3);
void checkPosition() {
  encoder.tick();
}
int encoderPosition = 0;
boolean encoderPressed = false;
int encoderPosDelta = 0;

// keyboard matrix
uint8_t keys_out [5] = {6, 7, 8, 9, 10};
uint8_t keys_in [5] = {1, 2, 3, 4, 5};
boolean keys_state [25];

uint8_t bpm = 120;
unsigned long bpm_ms, bpm_millis;

void setup() {
  // put your setup code here, to run once:

  // Serial.begin(115200);

  strip.begin();
  strip.show();
  strip.setBrightness(5);

  for (uint8_t j = 0; j < 5; j++) {
    pinMode(keys_out[j], OUTPUT);
  }

  // Set rotary encoder inputs and interrupts
  pinMode(PIN_ROTA, INPUT_PULLUP);
  pinMode(PIN_ROTB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_ROTA), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ROTB), checkPosition, CHANGE);

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();

  bpm_millis = millis();
  calculate_bpm_ms();

  // Start OLED display
  display.begin(0, true);
  display.setTextColor(SH110X_WHITE, SH110X_BLACK);
  display.display();
}

void calculate_bpm_ms() {
  bpm_ms = 1000; //60000 / bpm / 4; // 16th
}
boolean flipOn = false;

void loop() {


  calculate_bpm_ms();
  if ( millis() - bpm_millis > bpm_ms)
  {
    bpm_millis = millis();
    flipOn = !flipOn;
    ploink();


  }
  updateDisplay();
  
  processEncoder();
  processKeyboard();

}


void updateDisplay() {


  display.clearDisplay();
  display.setCursor(0, 0);

  display.setTextSize(1);

  display.println("Henlo");
  display.println(encoderPosDelta);

  for (uint8_t i = 0; i < 25; i++) {
    if (keys_state[i]) {
      display.print(i);
      display.print(",");
    }
  }
  display.println();

  // Display oled
  display.display();

}

void processEncoder() {
  encoder.tick();
  int newEncoderPosition = encoder.getPosition();
  if (encoderPosition != newEncoderPosition) {
    encoderPosDelta += newEncoderPosition - encoderPosition;
  }
  encoderPosition = newEncoderPosition;
}

void processKeyboard() {
  for (uint8_t i = 0; i < 5; i++) {

    for (uint8_t j = 0; j < 5; j++) {

      digitalWrite(keys_out[j], HIGH);

      uint8_t x = digitalRead(keys_in[i]);
      if (x == HIGH) {
        // Serial.println(j+i*5);
        keys_state[j + i * 5] = HIGH;
      }
      else
      {
        keys_state[j + i * 5] = LOW;
      }

      digitalWrite(keys_out[j], LOW);
    }
  }
}

void ploink() {
  if (flipOn)
  {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(127, 0, 64));
    }
    strip.show();
  }
  else {
    for (int i = 0; i < strip.numPixels(); i++) {
      //strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.setPixelColor(i, strip.Color(64, 0, 64)); // purple
    }
    strip.show();
  }
}
