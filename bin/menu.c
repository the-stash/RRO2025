#pragma config(Sensor, S1,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S4,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Medium, openLoop, encoder)

#include "../includes/others/math.h"

const int space = 20;
const int defaultX = 120;
int curPos = 1;
int maxPos = 2;
string a[100];

void changePos(int x) {
	eraseDisplay();
	curPos = curPos + x;
	if(curPos == 0) {
		curPos += maxPos;
	} else if(curPos == maxPos + 1) {
		curPos = 1;
	}

	displayBigStringAt(0, defaultX - space * (curPos - 1), "X");
	for(int i = 0; i < maxPos; i++) {
		displayBigStringAt(20, defaultX - space * i, a[i]);
	}
}

task main()
{
  setMotorBrakeMode(leftMotor, motorCoast);
  setMotorBrakeMode(rightMotor, motorCoast);

  maxPos = 2;
  a[0] = "Line";
  a[1] = "Color";
  changePos(0);
  while(true) {
  	if(getButtonPress(buttonUp)) {
  		changePos(-1);
  		delay(500);
  	} else if(getButtonPress(buttonDown)) {
  		changePos(1);
  		delay(500);
  	}
	}
	sleep(10000);
}
