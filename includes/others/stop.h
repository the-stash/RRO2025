void stopB(int t = 200) {
	motor[leftMotor] = 0;
	sleep(t);
}

void stopC(int t = 200) {
	motor[rightMotor] = 0;
	sleep(t);
}

void stopBC(int t = 200) {
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	sleep(t);
}
