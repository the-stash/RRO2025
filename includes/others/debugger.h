#include "../sensors/hitechnic/drivers/hitechnic-colour-v2.h"

void showRGB(tSensors s) {
	float r, g, b, r1, g1, b1;
	while(1) {
		sensorRGB(leftS, r, g, b);
		sensorRGB(rightS, r1, g1, b1);
		displayBigTextLine(1, "%d %d %d", r, g, b);
		displayBigTextLine(5, "%d %d %d", r1, g1, b1);
	}
}

void showHSV(tHTCS2 sen) {
	float hsvVals[6];
  	setMotorBrakeMode(leftMotor, motorCoast);
  	setMotorBrakeMode(rightMotor, motorCoast);

  	for(int i = 0; i < 3; i++) {
  		hsvVals[i] = 1000;
	}

 	for(int i = 3; i < 6; i++) {
 		hsvVals[i] = 0;
	}
	float hsvcurr[3];
	clearTimer(T1);
	while(time1[T1] < 5000) {
		sensorHSV(sen, hsvcurr[0], hsvcurr[1], hsvcurr[2]);
		for(int i = 0; i < 3; i++){
			hsvVals[i] = min(hsvcurr[i], hsvVals[i]);
			hsvVals[3 + i] = max(hsvcurr[i], hsvVals[3 + i]);
		}
	}
	float h1min=hsvVals[0];
	float s1min= hsvVals[1];
	float v1min= hsvVals[2];
	float h1max= hsvVals[3];
	float s1max= hsvVals[4];
	float v1max=hsvVals[5];

	displayBigStringAt(0, 120, "h1Min %f", h1min);
	displayBigStringAt(0, 100, "s1min%f", s1min);
	displayBigStringAt(0, 80,  "v1min %f", v1min);
	displayBigStringAt(0, 60, "h1max %f", h1max);
	displayBigStringAt(0, 40, "s1max %f", s1max);
	displayBigStringAt(0, 20, "v1max %f", v1max);
	waitForButtonPress();
}
