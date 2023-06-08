/***************************************************
 DFRobot Gravity: Analog Sound Level Meter
 <https://www.dfrobot.com/wiki/index.php/Gravity:_Analog_Sound_Level_Meter_SKU:SEN0232>

 ***************************************************
 This sample code is used to test the analog sound level meter.

 Created 2017-06-26
 By Jason <jason.ling@dfrobot.com@dfrobot.com>

 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

 /***********Notice and Trouble shooting***************
 1. This sample code is tested on Arduino Uno with Arduino IDE 1.0.5 r2.
 2. In order to protect the microphone on the board, you should not touch the black membrane on the microphone. Also you should keep it clean.
 3. Please do not place this module on the surface of  conductor or semiconductor. Otherwise, this will cause the microphone pin to be shorted.
 ****************************************************/

#define SoundSensorPin A1  //this pin read the analog voltage from the sound level meter
#define VREF  5.0  //voltage on AREF pin,default:operating voltage

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    float voltageValue,dbValue;
    voltageValue = analogRead(SoundSensorPin) / 1024.0 * VREF;
    dbValue = voltageValue * 50.0;  //convert voltage to decibel value
    Serial.print(dbValue,1);
    Serial.println(" dBA");
    delay(125);
}