void sensorRGBBlueGray(tSensors sensor, float &r, float &g, float &b) {
	int r1, g1, b1;
	if(sensor == leftS) {
		getColorRawRGB(sensor, r1, g1, b1);
		r = map(r1, r1MinBlueGray, r1MaxBlueGray, 100);
		g = map(g1, g1MinBlueGray, g1MaxBlueGray, 100);
		b = map(b1, b1MinBlueGray, b1MaxBlueGray, 100);
	} else if (sensor == rightS){
		getColorRawRGB(sensor, r1, g1, b1);
		r = map(r1, r2MinBlueGray, r2MaxBlueGray, 100);
		g = map(g1, g2MinBlueGray, g2MaxBlueGray, 100);
		b = map(b1, b2MinBlueGray, b2MaxBlueGray, 100);
	} else {
		getColorRawRGB(sensor, r1, g1, b1);
		r = r1;
		g = g1;
		b = b1;
	}
}

float lineBlueGray(int power) {
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
}



void lineBlueGrayCM(int power, float cm, int startPower = startDefault, int endPower = stopDefault) {
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
}

long r1MinBlueGray = 0;
long g1MinBlueGray = 38;
long b1MinBlueGray = 39;
long r1MaxBlueGray = 263;
long g1MaxBlueGray = 278;
long b1MaxBlueGray = 336;

long r2MinBlueGray = 22;
long g2MinBlueGray = 47;
long b2MinBlueGray = 42;
long r2MaxBlueGray = 151;
long g2MaxBlueGray = 276;
long b2MaxBlueGray = 356;