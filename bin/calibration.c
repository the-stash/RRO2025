#pragma config(Sensor, S1,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S4,     ,               sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Motor,  motorA,           ,             tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Medium, openLoop, encoder)

#include "math.h"

task main()
{
	int rgbValsLeft[6];
	int rgbValsRight[6];
  setMotorBrakeMode(leftMotor, motorCoast);
  setMotorBrakeMode(rightMotor, motorCoast);

  for(int i = 0; i < 3; i++) {
  	rgbValsLeft[i] = 1000;
  	rgbValsRight[i] = 1000;
	}

 	for(int i = 3; i < 6; i++) {
 		rgbValsLeft[i] = 0;
 		rgbValsRight[i] = 0;
	}
	int rgbS1[3];
	int rgbS2[3];
	clearTimer(T1);
	while(time1[T1] < 5000) {
		displayBigTextLine(0, "%d", time1[T1]);
		getColorRawRGB(leftS, rgbS1[0], rgbS1[1], rgbS1[2]);
		getColorRawRGB(rightS, rgbS2[0], rgbS2[1], rgbS2[2]);
		for(int i = 0; i < 3; i++){
			rgbValsLeft[i] = min(rgbS1[i], rgbValsLeft[i]);
			rgbValsLeft[3 + i] = max(rgbS1[i], rgbValsLeft[3 + i]);

			rgbValsRight[i] = min(rgbS2[i], rgbValsRight[i]);
			rgbValsRight[3 + i] = max(rgbS2[i], rgbValsRight[3 + i]);
		}
	}

	long fileHandle = fileOpenWrite("vals.txt");
	fileWriteLong(fileHandle, rgbValsLeft[0]);
	fileWriteLong(fileHandle, rgbValsLeft[1]);
	fileWriteLong(fileHandle, rgbValsLeft[2]);
	fileWriteLong(fileHandle, rgbValsLeft[3]);
	fileWriteLong(fileHandle, rgbValsLeft[4]);
	fileWriteLong(fileHandle, rgbValsLeft[5]);

	fileWriteLong(fileHandle, rgbValsRight[0]);
	fileWriteLong(fileHandle, rgbValsRight[1]);
	fileWriteLong(fileHandle, rgbValsRight[2]);
	fileWriteLong(fileHandle, rgbValsRight[3]);
	fileWriteLong(fileHandle, rgbValsRight[4]);
	fileWriteLong(fileHandle, rgbValsRight[5]);
	fileClose(fileHandle);
	

	delay(2000);
}
