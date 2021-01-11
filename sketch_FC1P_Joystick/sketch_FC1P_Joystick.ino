//--------------------------------------------------------------------

#include <Joystick.h>

#define JOYSTICK_COUNT 2

const int FC_CLK = 10;
const int FC_PS = 9;
const int FC_1P_DAT = 6;
const int FC_EXT_DAT = 4;

int loopi = 0;

//int XAxis[JOYSTICK_COUNT] = {0};
//int YAxis[JOYSTICK_COUNT] = {0};
int XAxis[JOYSTICK_COUNT] = {0, 0};
int YAxis[JOYSTICK_COUNT] = {0, 0};

Joystick_ Joystick[JOYSTICK_COUNT] = {
  Joystick_(0x03, JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false),  // No accelerator, brake, or steering
  Joystick_(0x04, JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false)  // No accelerator, brake, or steering
};

void setup() {
  // Initialize Button Pins
  pinMode(FC_CLK, OUTPUT);
  pinMode(FC_PS, OUTPUT);
  pinMode(FC_1P_DAT, INPUT); 
  pinMode(FC_EXT_DAT, INPUT); 

  // Initialize Joystick Library
  for (int index = 0; index < JOYSTICK_COUNT; index++)
  {
    Joystick[index].begin();

    Joystick[index].setXAxisRange(-1, 1);
    Joystick[index].setYAxisRange(-1, 1);
  }
}

void loop() {

  // 周期開始
  if (loopi % 16 == 0){
    loopi = 0;
    for (int index = 0; index < JOYSTICK_COUNT; index++)
    {
      XAxis[index] = 0;
      YAxis[index] = 0;
    }
    digitalWrite(FC_PS, HIGH);
  }

  // クロックを与えて押下判定
  digitalWrite(FC_CLK, HIGH);
  delayMicroseconds(20);
  int state_1P_dat = digitalRead(FC_1P_DAT);
  int state_Ext_dat = digitalRead(FC_EXT_DAT);

  // 1P側判定
  FC_Joystick_Hantei(0, state_1P_dat);
  // Ext側判定
  FC_Joystick_Hantei(1, state_Ext_dat);

  // 次のクロックへ
  digitalWrite(FC_CLK, LOW);
  digitalWrite(FC_PS, LOW);
  loopi = loopi + 1;
  delayMicroseconds(20);
}

void FC_Joystick_Hantei(int JoystickNo, int state_dat)
{
  bool currentButtonState = false;
  if (state_dat == LOW){
    currentButtonState = true;    // 押されている
  }

  // クロック周期判定処理
  switch (loopi){
    case 0:
      Joystick[JoystickNo].setButton(0, currentButtonState);
      break;
    case 1:
      Joystick[JoystickNo].setButton(1, currentButtonState);
      break;
    case 2:
      Joystick[JoystickNo].setButton(2, currentButtonState);
      break;
    case 3:
      Joystick[JoystickNo].setButton(3, currentButtonState);
      break;
    case 4:
      if (currentButtonState) {
        YAxis[JoystickNo] = -1;
      }
      break;
    case 5:
      if (YAxis[JoystickNo] == 0 && currentButtonState) {
        YAxis[JoystickNo] = 1;
      }
      break;
    case 6:
      if (currentButtonState) {
        XAxis[JoystickNo] = -1;
      }
      break;
    case 7:
      if (XAxis[JoystickNo] == 0 && currentButtonState) {
        XAxis[JoystickNo] = 1;
      }
      break;
    case 15:
      Joystick[JoystickNo].setXAxis(XAxis[JoystickNo]);
      Joystick[JoystickNo].setYAxis(YAxis[JoystickNo]);
      break;
  }
}
