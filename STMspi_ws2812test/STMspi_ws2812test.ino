#include <FastLED.h>
#include <SPI.h>
#include <cstdint>

uint8_t stripInfo[2];
#define LED_PIN_0   PB5 //tie
#define LED_PIN_1   PB6 //right shoulder
#define LED_PIN_2   PB7 //left shoulder
#define LED_PIN_3   PB8 //right shoes
#define LED_PIN_4   PB9 //right shoes
#define LED_PIN_5   PB15 //belt

#define NUM_STRIPS  6
#define BUF_SIZE    1024
#define BRIGHTNESS  50
#define COLOR_ORDER GRB
#define LED_TYPE    WS2812
#define DATA_OFFSET 1
#define START_BYTE  0xFF
const uint16_t NUM_LEDS[] = {56, 18, 18, 40, 40, 52};
uint8_t buf[BUF_SIZE];
CRGB *strips[NUM_STRIPS];
CRGB strip_0[56];
CRGB strip_1[18];
CRGB strip_2[18];
CRGB strip_3[40];
CRGB strip_4[40];
CRGB strip_5[52];

void setupSPI(void)
{
  // The clock value is not used
  // SPI1 is selected by default
  // MOSI, MISO, SCK and NSS PINs are set by the library
  SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));
}

uint8_t count = 0;
void setup()
{
  Serial1.begin(115200);
  Serial1.println("Start!");
  strips[0] = strip_0;
  strips[1] = strip_1;
  strips[2] = strip_2;
  strips[3] = strip_3;
  strips[4] = strip_4;
  strips[5] = strip_5;
  FastLED.addLeds<LED_TYPE, LED_PIN_0, COLOR_ORDER>(strips[0], NUM_LEDS[0]);
  FastLED.addLeds<LED_TYPE, LED_PIN_1, COLOR_ORDER>(strips[1], NUM_LEDS[1]);
  FastLED.addLeds<LED_TYPE, LED_PIN_2, COLOR_ORDER>(strips[2], NUM_LEDS[2]);
  FastLED.addLeds<LED_TYPE, LED_PIN_3, COLOR_ORDER>(strips[3], NUM_LEDS[3]);
  FastLED.addLeds<LED_TYPE, LED_PIN_4, COLOR_ORDER>(strips[4], NUM_LEDS[4]);
  FastLED.addLeds<LED_TYPE, LED_PIN_5, COLOR_ORDER>(strips[5], NUM_LEDS[5]);
  FastLED.setBrightness(BRIGHTNESS);
  // reset all strips
  for (uint8_t i = 0; i < NUM_STRIPS; ++i)
  {
      for (uint16_t j = 0; j < NUM_LEDS[i]; ++j)
      {
          strips[i][j].setRGB(0,0,0);
      }
  }
  FastLED.show();
  setupSPI();
}
void loop()
{
  // Blocking call to read SPI message
  SPI.transfer(stripInfo,2);
  uint8_t ID = stripInfo[0];
  SPI.transfer(buf, NUM_LEDS[ID] * 3+2);
  for (uint16_t i = 0; i < NUM_LEDS[ID]; ++i) // send pixel data to LED
    {   
        strips[ID][i].setRGB(buf[3 * i + DATA_OFFSET], buf[3 * i + DATA_OFFSET + 1], buf[3 * i + DATA_OFFSET + 2]);
    }
    FastLED.show(); // render
}
