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

const int buttonPin = 4;  // Set button pin number to digital pin 4
int buttonState = 0;  // Variable for reading the button status
int audioArray[3] = {1, 2, 3}; // Represents each sound 
int currIndex = 0;

}

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

  pinMode(buttonPin, INPUT_PULLUP);  // Initialize the button pin as an input

}


int incrementIndex(int currIndex) {
  if (currIndex < 2) {
    Serial.println(currIndex + 1);
    return currIndex + 1;
  }
  else {
    Serial.println(currIndex);
    currIndex = 0;
    return currIndex;
  }
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

    
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    Serial.println("Hello");
    currIndex = incrementIndex(currIndex);
    playAudio(currIndex);
    delay(500);
  }

}

void playAudio(int audioType) {
  switch (audioType) {
    case 0:
      myDFPlayer.play(1);
    case 1:
      myDFPlayer.play(2);
    case 2:
      myDFPlayer.play(3);
  }
}

void volumeControl(int newVolume) {
  
}

void displayMode(int numToDisplay) {
  switch (numToDisplay) {
    case 0: 
    
    case 1:

    case 2:

    case 3:

    case 4:

    case 5:

    case 6:

    case 7:
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
