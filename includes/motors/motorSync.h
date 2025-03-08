const float driveKp = 5;
const float driveKd = 8;
const float driveKi = 0.05;

float syncEold = 0;
float syncIsum = 0;

float sync(float speedB, float speedC) {
	float curB = -(nMotorEncoder[leftMotor] - localDistB) * min(1, fabs(speedC / speedB)) * sgn(speedB);
	float curC = (nMotorEncoder[rightMotor] - localDistC) * min(1, fabs(speedB / speedC)) * sgn(speedC);

	float e = curC - curB;
	syncIsum = syncIsum + e * driveKi;
	syncIsum = lim(syncIsum, -80, 80);

	float u = (e - syncEold) * driveKd + e * driveKp + syncIsum;
	syncEold = e;

	return u;
}

void drive(float powerB, float powerC, float encB = 0, float encC = 0, int startPower = 20, int endPower = 20) {
	float speedB = SmoothB(startPower, powerB, endPower, encB, fabs(powerB / powerC));
	float speedC = SmoothC(startPower, powerC, endPower, encC, fabs(powerC / powerB));

	float u = sync(powerB * sgn(encB), powerC * sgn(encC));

	float powerrB = -speedB - u * sgn(encB);
	float powerrC = speedC - u * sgn(encC);
	float ratio = max(max(1, fabs(powerrB / 100)), fabs(powerrC / 100));
	powerrB /= ratio;
	powerrC /= ratio;
	
	motor[leftMotor] = powerrB;
	motor[rightMotor] = powerrC;

	delay(2);
}
