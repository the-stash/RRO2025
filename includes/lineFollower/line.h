#ifndef __LINE_H__
#define __LINE_H__

#include "../others/structures.h"
#include "../motors/motorSync.h"
#include "../motors/drive.h"

const float lineKp = 0.65;
const float lineKd = 5;
const float lineKi = 0.01;
const float cS = 50;

const float lineKpOne = 1.2;
const float lineKdOne = 6;
const float lineKiOne = 0.01;
const float cSOne = 50;

float eold = 0;
float eoldInner = 0;
float isum = 0;
float isumInner = 0;

// return values
float line(int power) {
	float r1, g1, b1, r2, g2, b2;
	sensorRGB(leftS, r1, g1, b1);
	sensorRGB(rightS, r2, g2, b2);

	float e = (r1 + g1 + b1) / 3 - (r2 + g2 + b2) / 3;
	float kp = calcCoefficient(power, lineKp, cS);
	float kd = calcCoefficient(power, lineKd, cS);
	float ki = calcCoefficient(power, lineKi, cS);
	isum = isum + e * ki;
	isum = lim(isum, -60, 60);
	float u = kp * e + (e - eold) * kd + isum;
	eold = e;
	return u;
}

/*float lineBlueGray(int power) {
	float r1, g1, b1, r2, g2, b2;
	sensorRGBBlueGray(rightS, r2, g2, b2);

	float e = 50 - (r2 + g2 + b2) / 3;
	float kp = calcCoefficient(power, lineKpOne, cSOne);
	float kd = calcCoefficient(power, lineKdOne, cSOne);
	float ki = calcCoefficient(power, lineKiOne, cSOne);
	isum = isum + e * ki;
	isum = lim(isum, -60, 60);
	float u = kp * e + (e - eold) * kd + isum;
	eold = e;
	return u;
}*/

float lineS2Inner(int power) {
	float r1, g1, b1;
	sensorRGB(leftS, r1, g1, b1);

	float eInner = 20 - (r1 + g1 + b1) / 3;
	float kpInner = calcCoefficient(power, lineKpOne, cSOne);
	float kdInner = calcCoefficient(power, lineKdOne, cSOne);
	float kiInner = calcCoefficient(power, lineKiOne, cSOne);
	isumInner = isumInner + eInner * kiInner;
	isumInner = lim(isumInner, -60, 60);
	float u = kpInner * eInner + (eInner - eoldInner) * kdInner + isumInner;
	eoldInner = eInner;
	return u;
}

void stabilize() {
	clearTimer(T4);
	while(time1[T4] < 200) {
		float u = line(0);
		motor[leftMotor] = -u;
		motor[rightMotor] = -u;
	}
}

void lineReading(int power, int startPower = startDefault, int &i1, int &i2) {
	nMotorEncoder[motorC] = 0;
	eold = 0;
	isum = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}

	int cols[6];
	int i = 0, buffer;
	int degr = 150;
	while (i < 6){
		float speedB = SmoothB(startPower, power, 0, 0);
		float speedC = SmoothC(startPower, power, 0, 0);
		float u = line(speedC);

		float powerB =  -speedB - u;
		float powerC =  speedC - u;
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[motorB] = powerB;
		motor[motorC] = powerC;
		if (nMotorEncoder[motorC] > i * degr) {
			cols[i] = getColorReflected(colorS);
			if (cols[i] < 5) {cols[i] = 1;}
			else {cols[i] = 6;}
			i++;
		}
	}
	int bufferi1 = -1;
	int bufferi2 = -1;
    for (int i = 0; i < 6; i++) {
        if (cols[i] == 1) {
            if (bufferi1 == -1) {
                bufferi1 = i; 
            } else if (bufferi2 == -1) {
                bufferi2 = i;
                break;
            }
        }
    }
	i1 = bufferi1;
	i2 = bufferi2;
	/*stopBC(0);
    displayBigStringAt(0, 120, "%d", cols[0]);
    displayBigStringAt(0, 100, "%d", cols[1]);
    displayBigStringAt(0, 80, "%d", cols[2]);
    displayBigStringAt(0, 60, "%d", cols[3]);
    displayBigStringAt(0, 40, "%d", cols[4]);
    displayBigStringAt(0, 20, "%d", cols[5]);
    waitForButtonPress();
*/
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}

void lineCMReverse(int power, float cm, int startPower = startDefault, int endPower = stopDefault) {
	eold = 0;
	isum = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}

	float enc = fromCmToDeg(cm);

	while(fabs(nMotorEncoder[leftMotor] - localDistB) + fabs(nMotorEncoder[rightMotor] - localDistC) < 2 * fabs(enc)) {
		float speedB = SmoothB(startPower, power, endPower, enc);
		float speedC = SmoothC(startPower, power, endPower, enc);
		float u = line(speedC);

		float powerB =  -(-speedB + u);
		float powerC =  -(speedC + u);
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[motorB] = powerB;
		motor[motorC] = powerC;
	}

	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}

void lineCM(int power, float cm, int startPower = startDefault, int endPower = stopDefault) {
	eold = 0;
	isum = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}

	float enc = fromCmToDeg(cm);

	while(fabs(nMotorEncoder[leftMotor] - localDistB) + fabs(nMotorEncoder[rightMotor] - localDistC) < 2 * fabs(enc)) {
		float speedB = SmoothB(startPower, power, endPower, enc);
		float speedC = SmoothC(startPower, power, endPower, enc);
		float u = line(speedC);

		float powerB =  -speedB - u;
		float powerC =  speedC - u;
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[motorB] = powerB;
		motor[motorC] = powerC;
	}

	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}

void XCross1Sensor(int power, int n, int startPower = startDefault, bool toWheels = true, int dist = 8, lineColor stopColorLeft = blackLine, lineColor stopColorRight = blackLine) {
	eold = 0;
	isum = 0;
	int cur = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}
	bool flag = false;
	if (n == 0) {return;}
	while(cur < n) {
		float speedB = SmoothB(startPower, power, 0, 0);
		float speedC = SmoothC(startPower, power, 0, 0);
		float u = lineS2Inner(speedC);

		float powerB =  -speedB - u;
		float powerC =  speedC - u;
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[leftMotor] = powerB;
		motor[rightMotor] = powerC;

		if(checkColor(leftS, stopColorLeft) && checkColor(rightS, stopColorRight)) {
			//peak();
			if (!flag) {
				cur++;
				flag = true;
			}
		} else {
			flag = false;
		}
		delay(1);
	}

	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
	if (toWheels) {
		driveCM(power, dist, 50, 50);
	}
}

void align() {
	eold = 0;
	isum = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	clearTimer(T1);
	while (time1[T1] < 300) {
		float u = line(50);
		motor[motorB] = 9 - u;
		motor[motorC] = 9 - u;
	}
	
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}

void XCross(int power, int n, int startPower = startDefault, bool toWheels = true, int dist = 8, lineColor stopColorLeft = blackLine, lineColor stopColorRight = blackLine) {
	eold = 0;
	isum = 0;
	int cur = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}
	bool flag = false;
	if (n == 0) {return;}
	while(cur < n) {
		float speedB = SmoothB(startPower, power, 0, 0);
		float speedC = SmoothC(startPower, power, 0, 0);
		float u = line(speedC);

		float powerB =  -speedB - u;
		float powerC =  speedC - u;
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[leftMotor] = powerB;
		motor[rightMotor] = powerC;

		if(checkColor(leftS, stopColorLeft) && checkColor(rightS, stopColorRight)) {
			//peak();
			if (!flag) {
				cur++;
				flag = true;
			}
		} else {
			flag = false;
		}
		delay(1);
	}

	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
	if (toWheels) {
		driveCM(power, dist, 50, 50);
	}
}

void QCross(int power, int n, int startPower = startDefault, bool last2wheels = false, int dist = 5) {
	for (int i = 0; i < n; i++) {
		if (i == n - 1) {XCross(power - 20, 1, startPower, last2wheels, 0)}
		else {XCross(power, 1, startPower, true, dist)}
	}
}

//Gcross FUNCTIYA NE ALLIANCA


/*void lineBlueGrayCM(int power, float cm, int startPower = startDefault, int endPower = stopDefault) {
	eold = 0;
	isum = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}

	float enc = fromCmToDeg(cm);

	while(fabs(nMotorEncoder[leftMotor] - localDistB) + fabs(nMotorEncoder[rightMotor] - localDistC) < 2 * fabs(enc)) {
		float speedB = SmoothB(startPower, power, endPower, enc);
		float speedC = SmoothC(startPower, power, endPower, enc);
		float u = lineBlueGray(speedC);

		float powerB =  -speedB - u;
		float powerC =  speedC - u;
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[leftMotor] = powerB;
		motor[rightMotor] = powerC;
	}

	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}*/

void crossS2Inner(int power, int n, int startPower = startDefault) {
	eold = 0;
	isum = 0;
	int cur = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}
	bool flag = false;

	while(cur < n) {
		float speedB = SmoothB(startPower, power, 0, 0);
		float speedC = SmoothC(startPower, power, 0, 0);
		float u = lineS2Inner(speedC);

		float powerB =  -speedB - u;
		float powerC =  speedC - u;
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[leftMotor] = powerB;
		motor[rightMotor] = powerC;

		if(checkColor(leftS, blackLine) && checkColor(rightS, blackLine)) {
			if(!flag) {
				cur++;
				flag = true;
			}
		} else {
			flag = false;
		}
		delay(1);
	}

	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}

void lineS2InnerCM(int power, float cm, int startPower = startDefault, int endPower = stopDefault) {
	eold = 0;
	isum = 0;
	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

	if(startPower != 0) {
		globalDistB = nMotorEncoder[leftMotor];
		globalDistC = nMotorEncoder[rightMotor];
	}

	float enc = fromCmToDeg(cm);

	while(fabs(nMotorEncoder[leftMotor] - localDistB) + fabs(nMotorEncoder[rightMotor] - localDistC) < 2 * fabs(enc)) {
		float speedB = SmoothB(startPower, power, endPower, enc);
		float speedC = SmoothC(startPower, power, endPower, enc);
		float u = lineS2Inner(speedC);

		float powerB =  -speedB - u;
		float powerC =  speedC - u;
		float ratio = max(max(1, fabs(powerB / 100)), fabs(powerC / 100));
		powerB /= ratio;
		powerC /= ratio;

		motor[leftMotor] = powerB;
		motor[rightMotor] = powerC;
	}

	localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}

#endif
