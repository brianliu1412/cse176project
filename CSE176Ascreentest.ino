#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library

#define TFT_CS    8      // TFT CS  pin is connected to arduino pin 8
#define TFT_RST   9      // TFT RST pin is connected to arduino pin 9
#define TFT_DC    10     // TFT DC  pin is connected to arduino pin 10

#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

char sensorPrintout[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(ILI9341_BLACK);
  Serial.println(tft.width());
  Serial.println(tft.height());

  tft.setTextSize(3);
  tft.println("Volume (Val)");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  String sensorVal = String(analogRead(A4));
  sensorVal.toCharArray(sensorPrintout, 4);
  Serial.println(analogRead(A4));
  
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.setCursor(100, 80);
  tft.print(sensorPrintout);

if (analogRead(A4) <= 255) {
      tft.fillCircle(100, 180, 40, MAGENTA);
      //tft.fillCircle(100, 180, 40, ILI9341_BLACK);
} else if (analogRead(A4)  > 255 && sensorPrintout <= 600){
      tft.fillRoundRect(60, 140, 80, 80, 10, YELLOW);
      //tft.fillRoundRect(80, 150, 80, 80, 10, ILI9341_BLACK);
} else if (analogRead(A4)  > 600){
      tft.fillTriangle(60, 220, 100, 140, 140, 220, CYAN);
      //tft.fillTriangle(80, 200, 140, 80, 200, 150, ILI9341_BLACK);
}

delay(250);

  tft.setCursor(100, 80);
  tft.setTextColor(ILI9341_BLACK);
  tft.print(sensorPrintout);
  
 // void setTextWrap(boolean w);

}
