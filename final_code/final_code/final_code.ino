//Add imports

//The folder name needs to be mp3, placed under the SD card root directory, and the mp3 file name needs to be 4 digits, for example, "0001.mp3", placed under the mp3 folder. If you want to name it in Both English and Chinese, you can add it after the number, for example, "0001hello.mp3" or "0001后来.mp3".

//Graphics Libraries
#include <Adafruit_GFX.h> 
#include <Adafruit_ILI9341.h>  

//Audio Libraries
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

//Define Pins
#define TFT_CS 8   // TFT CS  pin is connected to arduino pin 8
#define TFT_RST 9  // TFT RST pin is connected to arduino pin 9
#define TFT_DC 10  // TFT DC  pin is connected to arduino pin 10

//Define Display Colors 
#define BLACK       0x0000  ///<   0,   0,   0
#define NAVY        0x000F  ///<   0,   0, 123
#define DARKGREEN   0x03E0  ///<   0, 125,   0
#define DARKCYAN    0x03EF  ///<   0, 125, 123
#define MAROON      0x7800  ///< 123,   0,   0
#define PURPLE      0x780F  ///< 123,   0, 123
#define OLIVE       0x7BE0  ///< 123, 125,   0
#define LIGHTGREY   0xC618  ///< 198, 195, 198
#define DARKGREY    0x7BEF  ///< 123, 125, 123
#define BLUE        0x001F  ///<   0,   0, 255
#define GREEN       0x07E0  ///<   0, 255,   0
#define CYAN        0x07FF  ///<   0, 255, 255
#define RED         0xF800  ///< 255,   0,   0
#define MAGENTA     0xF81F  ///< 255,   0, 255
#define YELLOW      0xFFE0  ///< 255, 255,   0
#define WHITE       0xFFFF  ///< 255, 255, 255
#define ORANGE      0xFD20  ///< 255, 165,   0
#define GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define PINK        0xFC18  ///< 255, 130, 198

//Initialize ILI9341 TFT library
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//Initialize Audio Libraries
SoftwareSerial mySoftwareSerial(4, 5);
DFRobotDFPlayerMini myDFPlayer;

//Initalize Volume Pin
int potPin = 0; // Assign analog pin to potentiometer
int volVal = 0; // Variable to read value from potentiometer, starts at 0
int oldVolume = 0; // Used to compare volume levels
int currentVolume = 0; // Used to compare volume levels
int manualVol = false;

void setup() {
  //Setup Display
  Serial.begin(9600);
  tft.begin();

  //Setup Audio
  mySoftwareSerial.begin(9600); //CHANGE SERIAL??
  serial.begin(115200);

  //Audio Debug
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  //myDFPlayer.play(1);  //Play the first mp3

  //States: 
  //0 = Startup, 1 = Ready to play noise, 2 = Play White Noise, 3 = Play Brown Noise, 4
  //
  int state = 0;

}

void loop() {
  //Detect Volume Changes
  if (manualVol == true) {
    volVal = analogRead(potPin); //Reads potentiometer value (between 0 and 1023)
    val = map(val, 0, 1023, 0, 30); //Scale value to volume (value between 0 and 30)
    //Sets net Volume
    if (val != oldVolume) {
      volumeControl(val);
    }
  }
  else {
    //Code to autochange volume based on decibel level, lets say 40 - 80/90 decibels corresponds to 8-22 volume?
    

  }

    



}


void playAudio(char audioType) {
  switch (audioType) {
    case 'white':
      myDFPlayer.play(0);
    case 'brown':
      myDFPlayer.play(1);
    case 'pink':
      myDFPlayer.play(2);
  }
}

void volumeControl(int newVolume) {
  
}

void displayMode(char noiseToDisplay) {
//Default display, always runs
// to do
}

void tempDisplayMode(int numToDisplay, int volume) {
  tft.fillScreen(WHITE);    //default display = type of white noise, rest flash on screen
  switch (numToDisplay) {
    case 0: //welcome screen - stretch goal
      tft.setCursor(0,0);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.println("WELCOME"); //to do
    case 1: //splash screen - "journey 1.0"
      tft.setCursor(0,0);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.println("BROWN NOISE"); //to do
    case 2: //display white noise
      tft.setCursor(0,0);   //set txt start point - display dimensions: 320 x 240
      tft.setTextColor(BLACK);  //set txt color
      tft.setTextSize(1);       //set txt size
      tft.println("WHITE NOISE");   //print on display
    case 3: //display pink noise
      tft.setCursor(0,0);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.println("PINK NOISE");
    case 4: //display brown noise
      tft.setCursor(0,0);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.println("BROWN NOISE");
    case 5: //volume value
      tft.setCursor(0,0);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.println(volume);      
    case 6: //display "play" 
      tft.setCursor(0,0);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.println("PLAY");
    case 7: //display "pause"
      tft.setCursor(0,0);
      tft.setTextColor(BLACK);
      tft.setTextSize(1);
      tft.println("PAUSE");
    case 8: //display "off" - have a great day!
  }

}


// Audio Print Debugs
void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
