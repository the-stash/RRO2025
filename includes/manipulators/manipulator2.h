const float manipKp2 = 2;
const float manipKd2 = 5;
const float manipKi2 = 0.001;
float manipKc2 = 1;

int manipPos2 = 0;
float eoldManip2 = 0;
float isumManip2 = 0;

task PIDManipRight() {
	sleep(550);
	while(true) {
		float e2 = manipPos2 - nMotorEncoder[manipMotor2];
		isumManip2 = isumManip2 + e2 * manipKi2;
		isumManip2 = lim(isumManip2, -60, 60);
		float u2 = e2 * manipKp2 + (e2 - eoldManip2) * manipKd2 + isum;
		motor[manipMotor2] = u2 * manipKc2;
		eoldManip2 = e2;
		sleep(2);
	}
}

task initManipRight() {
	clearTimer(T1);
	while(time1[T1] < 80) {
		motor[manipMotor2] = 100;
	}
	nMotorEncoder[manipMotor2] = 0;
}

void floorGrabRight(bool afk = false) {
	manipKc2 = 1;
	manipPos2 = -375;
	if (afk) {stopBC(400);}
}

void openRightNotFull(bool afk = false) {
	manipKc2 = 0.1;
	manipPos2 = -520;
	if (afk) {stopBC(400);}
}

void openFullRight(bool afk = false) {
	manipKc2 = 1;
	manipPos2 = -1000;
	if (afk) {stopBC(400);}
}

void openFullRightLowSpeed(bool afk = false) {
	manipKc2 = 0.1;
	manipPos2 = -750;
	if (afk) {stopBC(400);}
}

void openFullRightLowLowSpeed(bool afk = false) {
	manipKc2 = 0.02;
	manipPos2 = -1050;
	if (afk) {stopBC(400);}
}

void closeFullRightLowSpeed(bool afk = false) {
	manipKc2 = 0.15;
	manipPos2 = 550;
	if (afk) {stopBC(400);}
}

void liftSomeRight(bool afk = false) {
	manipKc2 = 0.65;
	manipPos2 = -170;
	if (afk) {stopBC(400);}
}

void liftContRight(int size, bool afk = false) {
	if (size == 0) {
		manipKc2 = 0.15;
		manipPos2 = -170;
	} else {
		manipKc2 = 0.36;
		manipPos2 = -210;
	}
	if (afk) {stopBC(425);}
}

void closeFullRight(bool afk = false) {
	manipKc2 = 1;
	manipPos2 = 500;
	if (afk) {stopBC(400);}
}