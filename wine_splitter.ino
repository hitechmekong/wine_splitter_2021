/*
   Copyright 2020 @ Nhannv - HitechMekong LTD. Co, - nhannv@hitechmekong.vn

  Wine Splitter - Version 1.0
  
  This code is control Wine Sliptter device.
  Full device body can use 3d print, download at :

  Library used :
     - SevSeg :
     - OneButton

*/

//define software constant
#define MAX_GLASSES 10
#define STOPPED 0
#define RUNNING 1
#define AUTO_MODE 2
#define MANUAL_MODE 3
#define CLEAN_MODE 4
#define SETTING_MODE 5
#define MAX_NUMBER_STRINGS 12
#define MAX_STRING_SIZE 3
#define DEFAULT_BUMP_TIME 3000


//define hardward constant
#define LED1_PIN 4
#define LED2_PIN 5
#define LED3_PIN 6
#define GLASS_SWITCH_PIN A1
#define FINISH_SWITCH_PIN A2
#define ROTATE_MOTOR_PIN A3
#define BUMP_PIN 16
#define START_BTN_PIN 2 // attachInterrupt (OneButton Library) only supports pin 2 and 3 on UNO/NAN0. More info : https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
#define SETTING_BTN_PIN 3

//include library
#include "SevSeg.h"
#include "OneButton.h"

SevSeg sevseg; //Instantiate a seven segment controller object
OneButton start_btn(START_BTN_PIN, true);
OneButton setting_btn(SETTING_BTN_PIN, true);

//declare global variable
int deviceStatus = STOPPED;
boolean isFinish = false;
boolean hitGlass = false;
int NoOfGlasses = 0;
static int ledNo = 0;
int bumpTime = DEFAUL_BUMP_TIME;

// save the millis when a press has started.
unsigned long pressStartTime;
unsigned long pressSettingTime;

char ledString[MAX_NUMBER_STRINGS][MAX_STRING_SIZE];

//Setup
void setup() {

  //Led 7 Seg
  byte numDigits = 3;
  byte digitPins[] = {LED1_PIN, LED2_PIN, LED3_PIN};
  byte segmentPins[] = {7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  //count 3 seconds to begin system
  //Use for system check before running
  if (checkDevice()) {
    showLED_manual(0);
  } else showLED_manual(111);

  //Serial
  Serial.begin(9600);

  // link the button functions.
  //StartBTN
  start_btn.attachClick(startBTN_singleClick);
  start_btn.attachDoubleClick(startBTN_doubleClick);
  start_btn.attachDuringLongPress(startBTN_longPress);
  //SettingBTN
  setting_btn.attachClick(settingBTN_singleClick);
  setting_btn.attachDoubleClick(settingBTN_doubleClick);
  setting_btn.attachDuringLongPress(settingBTN_longPress);


  //
  // Adds set of test strings with periods in various places
  strcpy(ledString[0], "-1-");
  strcpy(ledString[1], "-2-");
  strcpy(ledString[2], "-3-");

}

void loop() {

  // keep watching the push button, even when no interrupt happens:
  start_btn.tick();
  setting_btn.tick();

  // You can implement other code in here or just wait a while
  delay(10);
  sevseg.refreshDisplay(); // Must run repeatedly
}

//Function

//Call this function at the system start to test each device.
boolean checkDevice() {
  ledShow_char_manual(0);
  for (int runtime = 0 ; runtime <= 1000 ; runtime++) {
    runMotor(100);
  }
  ledShow_char_manual(1);
  for (int runtime = 0 ; runtime <= 1000 ; runtime++) {
    runBump();
  }
  ledShow_char_manual(2);
  delay (1000);
  return true;
}

void testMotor() {

}


int ledCalculate () {
  int ledNoReturn = 0;

  //code to calculate the number of led display

  return ledNoReturn;
}

//this function will show the led with parameter
void showLED_int_manual(int num) {
  sevseg.setNumber(num, 1);
}

void showLED_char_manual(int strPos) {
  sevseg.setChars(ledString[strPos]);
}

//this function will call ledCalculate and display led automatictly
void showLED() {
  ledNo = ledCalculate ();
  sevseg.setNumber(ledNo, 1);
}

//call this funtion to rotate the motor
void runMotor (int mSpeed) {

}

//call this function to start bump
void runBump () {

}

//call this function when disc hit endstop
void stopRotate () {

}

//=============================================================================================
// BTN EVENT FUNCTION GROUP
//=============================================================================================
// This function is called from the interrupt when the signal on the PIN_INPUT has changed.
// do not use Serial in here.
void checkTicks()
{
  // include all buttons here to be checked
  start_btn.tick(); // just call tick() to check the state.
  setting_btn.tick(); // just call tick() to check the state.
}

//----------------------------------------------------------------------------------------------
//Start Button function

// this function will be called when the button was pressed 1 time only.
void startBTN_singleClick()
{
  Serial.println("singleClick() detected.");
} // singleClick


// this function will be called when the button was pressed 2 times in a short timeframe.
void startBTN_doubleClick()
{
  Serial.println("doubleClick() detected.");


} // doubleClick

void startBTN_longPress() {
  Serial.println("Button 1 longPress...");
} // lo

//------------------------------------------------------------------------------------------
// Setting button function


// this function will be called when the button was pressed 1 time only.
void settingBTN_singleClick()
{
  Serial.println("singleClick() detected.");
} // singleClick


// this function will be called when the button was pressed 2 times in a short timeframe.
void settingBTN_doubleClick()
{
  Serial.println("doubleClick() detected.");

} // doubleClick

void settingBTN_longPress() {
  Serial.println("Button 1 longPress...");
} // longPress
