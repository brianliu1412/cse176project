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

//Soundmeter Declarations
#define SoundSensorPin A1  //this pin read the analog voltage from the sound level meter
#define VREF  5.0  //voltage on AREF pin,default:operating voltage

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
#define RED        0x001F  ///<   0,   0, 255
#define GREEN       0x07E0  ///<   0, 255,   0
#define CYAN        0x07FF  ///<   0, 255, 255
#define BLUE         0xF800  ///< 255,   0,   0
#define MAGENTA     0xF81F  ///< 255,   0, 255
#define YELLOW      0xFFE0  ///< 255, 255,   0
#define WHITE       0xFFFF  ///< 255, 255, 255
#define ORANGE      0xFD20  ///< 255, 165,   0
#define GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define PINK        0xFC18  ///< 255, 130, 198

//Initialize ILI9341 TFT library
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

//Initialize Audio Libraries
SoftwareSerial mySoftwareSerial(3, 2);
DFRobotDFPlayerMini myDFPlayer;

//Initalize Volume Pin
int volVal = 0; // Variable to read value from potentiometer, starts at 0
int vol; // Declare vol value
int oldVol = 0; // Used to compare volume levels
int manualVol = true;
int dbVal;
int prevVolVal = 0;

//States
bool audioPlaying = true;
bool startScreenPlayed = false;
bool volDisplayFirst = false;

byte butLst;

enum { None, SingleClick, DoubleClick };


const int buttonPinOne = 4;  // Set button pin number to digital pin 4
const int buttonPinTwo = 6;
int buttonState = 0;  // Variable for reading the button status
int audioArray[3] = {1, 2, 3}; // Represents each sound 
int currIndex = 1;
int currDisplayIndex = 0;



void setup() {
  //Setup Display
  Serial.begin(9600);
  tft.begin();
  tempDisplayMode(8, NULL);

  //Setup Audio
  mySoftwareSerial.begin(9600); //CHANGE SERIAL??
  Serial.begin(115200);
  
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
  
  myDFPlayer.volume(6);  //Set volume value. From 0 to 30


  pinMode(buttonPinOne, INPUT_PULLUP);  // Initialize the button pin as an input
  pinMode(buttonPinTwo, INPUT_PULLUP);
  butLst = digitalRead(buttonPinOne);

}


int incrementIndex(int currIndex) {
  if (currIndex < 3) {
    Serial.println(currIndex + 1);
    return currIndex + 1;
  }
  else {
    Serial.println(1);
    return 1;
  }
}

void playAudio(int audioType) {
  switch (audioType) {
    case 1: // White
      //myDFPlayer.play(1);
      myDFPlayer.loop(1);
      tempDisplayMode(2, NULL);
      currDisplayIndex = 2;
      
      break;
    case 2: // Pink
      //myDFPlayer.play(2);
      myDFPlayer.loop(2);
      tempDisplayMode(3, NULL);
       currDisplayIndex = 3;
      break;
    case 3: // Brown
      //myDFPlayer.play(3);
      myDFPlayer.loop(3);
      tempDisplayMode(4, NULL);
       currDisplayIndex = 4;
      break;
  }
}

void loop() {
  if (startScreenPlayed == false) {
    tempDisplayMode(1, NULL);
    startScreenPlayed = true;
    playAudio(1);
  }

  //Button Code 
  buttonState = digitalRead(buttonPinTwo);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    delay(200);
    Serial.println("Auto/Manual Button");
    if (manualVol == true) {
       manualVol = false;
       tempDisplayMode(9, NULL);
       tempDisplayMode(currDisplayIndex, NULL);
    }
    else {
      manualVol = true;
      tempDisplayMode(10, NULL);
      tempDisplayMode(currDisplayIndex, NULL);
    }
  }
  //Button Code
  switch (chkButton ())  {
    case SingleClick:
      Serial.println ("single");
      if (audioPlaying == true) {
        Serial.println("Paused");
        tempDisplayMode(7, NULL);
        myDFPlayer.pause();
        audioPlaying = false;
        tempDisplayMode(currDisplayIndex, NULL);
      }
      else {
        audioPlaying = true;
        Serial.println("Play");
        tempDisplayMode(6, NULL);
        myDFPlayer.loop(currIndex);
        tempDisplayMode(currDisplayIndex, NULL);
      }
      break;

    case DoubleClick:
      Serial.println ("double");
      audioPlaying = true;
      currIndex = incrementIndex(currIndex);
      playAudio(currIndex);
      break;
  }
  
  //Detect Volume Changes
  if (manualVol == true) {
    
    volVal = analogRead(A4); //Reads potentiometer value (between 0 and 1023)
    Serial.println(volVal);
    if (abs(volVal - prevVolVal) > 20) {
      int val = map(volVal, 0, 1023, 0, 30); //Scale value to volume (value between 0 and 30)
      /*
      if (volDisplayFirst == false) {
        //tempDisplayMode(5, val);
        volDisplayFirst = true;
      }
      else {
        volDisplayFirst = false;
      }
      */
      prevVolVal = volVal;
      //Sets net Volume
      if (val == 0) {
        myDFPlayer.volume(0);
      }
      else if (val != oldVol) {
        myDFPlayer.volume(val);
        //Serial.println(myDFPlayer.readVolume());
      }
      //tempDisplayMode(5, val);
      delay(200);
    }
  }
   //Code to autochange volume based on decibel level, lets say 40 - 80/90 decibels corresponds to 8-22 volume?
  else {
    float voltageValue,dbValue;
    voltageValue = analogRead(SoundSensorPin) / 1024.0 * VREF;
    dbValue = voltageValue * 50.0; 
    //Serial.println(dbValue);
    dbVal = int(round(dbValue));
    int val = map(dbVal, 20, 90, 0, 20);
    Serial.println(val);
    if (val != oldVol) {
      /*
      if (abs(val - oldVol) > 4) {
        myDFPlayer.volume(oldVol + (val - oldVol));
        delay(200);
      }
      */
      myDFPlayer.volume(val);
      oldVol = val;
    }
    delay(200);
  }
  
}


int chkButton (void) {
    const  unsigned long ButTimeout  = 400;
    static unsigned long msecLst;
           unsigned long msec = millis ();

    if (msecLst && (msec - msecLst) > ButTimeout)  {
        msecLst = 0;
        return SingleClick;
    }

    byte but = digitalRead(buttonPinOne);
    if (butLst != but)  {
        butLst = but;
        delay (10);           // **** debounce

        if (LOW == but)  {   // press
            if (msecLst)  { // 2nd press
                msecLst = 0;
                return DoubleClick;
            }
            else
                msecLst = 0 == msec ? 1 : msec;
        }
    }
    return None;
}


// f for fast, s for slow gradual volume change
void volumeControl(int newVolume, char fastSlow, int oldVolume) {
  int change = newVolume - oldVolume;
  if (fastSlow == 'f') {
    int delay = 10;
  }
  else {
    int delay = 200;
  }
  if (change > 0) {
    for (int i = 0; i < change; i++) {
      Serial.println("Vol Up: " + myDFPlayer.readVolume());
      myDFPlayer.volumeUp();
    }
  }
  else if (change < 0) {
    for (int i = 0; i < abs(change); i++) {
      Serial.println("Vol Down: " + myDFPlayer.readVolume());
      myDFPlayer.volumeDown();
    }
  }
}

void displayMode(char noiseToDisplay) {
//Default display, always runs
// to do
}

void tempDisplayMode(int numToDisplay, int volume) {
  tft.fillScreen(WHITE);    //default display = type of white noise, rest flash on screen
  switch (numToDisplay) {
    case 0: //welcome screen - stretch goal
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.fillRect(30,200,40,5,BLACK); //fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t t)
      tft.fillTriangle(10,204,30,190,30,220,BLACK); //fillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, uint16_t t)
      tft.setCursor(50,30);
      Serial.println("Case 0!");
      delay(3000); //to do
      break;
    case 1: //splash screen - "journey 1.0"
      tft.setCursor(90,100); 
      tft.fillScreen(WHITE);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("JOURNEY 1.0"); 
      Serial.println("Case 1!");
      delay(3000);
      tft.fillScreen(WHITE);
      break;
    case 2: //display white noise
      tft.setCursor(80, 100);   //set txt start point - display dimensions: 320 x 240
      tft.setTextColor(BLACK);  //set txt color
      tft.setTextSize(2);       //set txt size
      tft.println("WHITE NOISE");   //print on display
      Serial.println("Case 2!");
      delay(200);
      break;
    case 3: //display pink noise
      tft.setCursor(80,100);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("PINK NOISE");
      Serial.println("Case 3!");
      delay(200);
      break;
    case 4: //display brown noise
      tft.setCursor(80,100);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("BROWN NOISE");
      Serial.println("Case 4!");
      delay(200);
      break;
    case 5: //volume value
      tft.setCursor(140,100);
      tft.setTextColor(BLACK);
      tft.setTextSize(5);
      tft.println(volume);    
      Serial.println("Case 5!"); 
      delay(600); 

      break;
    case 6: //display "play" 
      tft.setCursor(108,100);
      tft.setTextColor(BLACK);
      tft.setTextSize(3);
      tft.println("PLAY");
      Serial.println("Case 6!");
      delay(1000);
      break;
    case 7: //display "pause"
      tft.setCursor(100,100);
      tft.setTextColor(BLACK);
      tft.setTextSize(3);
      tft.println("PAUSE");
      Serial.println("Case 7!");
      delay(1000);
      break;
    case 8: //Making Screen White
      tft.setRotation(0);
      tft.fillScreen(WHITE);
      tft.setRotation(1);
      tft.fillScreen(WHITE);
      tft.setRotation(2);
      tft.fillScreen(WHITE);
      tft.setRotation(3);
      tft.fillScreen(WHITE);
      tft.setRotation(2);
      break;
    case 9: //Automatic
      tft.setCursor(100,104);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("AUTOMATIC");
      Serial.println("Case 9!");
      delay(1000);
      break;
    case 10: //Manual
      tft.setCursor(114,104); 
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("MANUAL");
      Serial.println("Case 10!");
      delay(1000);
      break;
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
