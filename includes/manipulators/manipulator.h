const float manipKp = 2;
const float manipKd = 5;
const float manipKi = 0.001;
float manipKc = 1;

int manipPos = 0;
float eoldManip = 0;
float isumManip = 0;
const float lslPos = 135;

task PIDManipLeft() {
	sleep(550);
	while(true) {
		float e = manipPos - nMotorEncoder[manipMotor];
		isumManip = isumManip + e * manipKi;
		isumManip = lim(isumManip, -60, 60);
		float u = e * manipKp + (e - eoldManip) * manipKd + isum;
		motor[manipMotor] = u * manipKc;
		eoldManip = e;
		sleep(2);
	}
}

task initManipLeft() {
	clearTimer(T1);
	while(time1[T1] < 80) {
		motor[manipMotor] = -100;
	}
	nMotorEncoder[manipMotor] = 0;
}

void floorGrabLeft(bool afk = false) {
	manipKc = 0.7;
	manipPos = 400;
	if (afk) {stopBC(400);}
}

void openLeftNotFull(bool afk = false) {
	manipKc = 0.1;
	manipPos = 520;
	if (afk) {stopBC(400);}
}

void openFullLeft(bool afk = false) {
	manipKc = 1;
	manipPos = 1000;
	if (afk) {stopBC(400);}
}

void liftSomeLeft(bool afk = false) {
	manipKc = 0.6;
	manipPos = 150;
	if (afk) {stopBC(400);}
}

void liftContLeft(int size, bool afk = false) {
	if (size == 0) {
		manipKc = 0.08;
		manipPos = 245;
	} else {
		manipKc = 0.11;
		manipPos = 245;
	}
	if (afk) {stopBC(400);}
}

void closeFullLeft(bool afk = false) {
	manipKc = 1;
	manipPos = -500;
	if (afk) {stopBC(400);}
}
