#pragma config(Sensor, S1,     colorS,         sensorNone)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S4,     ebat,           sensorNone)
#pragma config(Motor,  motorA,          manipMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorD,          liftMotor,     tmotorEV3_Medium, openLoop, encoder)

#include "../includes/others/math.h"

bool exit = true;

task main()
{
	int rgbValsLeft[6];
	int rgbValsRight[6];
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
	setMotorBrakeMode(motorB, motorCoast);
	setMotorBrakeMode(motorC, motorCoast);
	clearTimer(T1);
	while (time1[T1] < 5000) {
		getColorRawRGB(leftS, rgbS1[0], rgbS1[1], rgbS1[2]);
		getColorRawRGB(rightS, rgbS2[0], rgbS2[1], rgbS2[2]);
		for(int i = 0; i < 3; i++){
			rgbValsLeft[i] = min(rgbS1[i], rgbValsLeft[i]);
			rgbValsLeft[3 + i] = max(rgbS1[i], rgbValsLeft[3 + i]);

			rgbValsRight[i] = min(rgbS2[i], rgbValsRight[i]);
			rgbValsRight[3 + i] = max(rgbS2[i], rgbValsRight[3 + i]);}
	}
	int r1min=rgbValsleft[0];
	int g1min= rgbValsleft[1];
	int b1min= rgbValsleft[2];
	int r1max= rgbValsleft[3];
	int g1max= rgbValsleft[4];
	int b1max=rgbValsleft[5];
	int r2min=rgbValsRight[0];
	int g2min= rgbValsRight[1];
	int b2min=rgbValsRight[2];
	int r2max=rgbValsRight[3];
	int g2max=rgbValsRight[4];
	int b2max=rgbValsRight[5];

	displayBigStringAt(0, 120, "r1Min %d", r1min);
	displayBigStringAt(0, 100, "g1Min%d", g1min);
	displayBigStringAt(0, 80,  "b1Min %d", b1min);
	displayBigStringAt(0, 60, "r1max %d", r1max);
	displayBigStringAt(0, 40, "g1max %d", g1max);
	displayBigStringAt(0, 20, "b1max %d", b1max);
	displayBigStringAt(120, 120, " %d", r2min);
	displayBigStringAt(120, 100, " %d", g2min);
	displayBigStringAt(120, 80,  " %d", b2min);
	displayBigStringAt(120, 60, " %d", r2max);
	displayBigStringAt(120, 40, " %d", g2max);
	displayBigStringAt(120, 20, " %d", b2max);
	waitForButtonPress();
}
