void cube1(int fAngle = -24, int sAngle = 24) {
	turn(100, fAngle);
	if(fAngle == 0) stopBC();
	open();
	driveCM(100, 10);
	stopBC();
	close();
	delay(100);
	driveCM(100, -10);
	stopBC();
	turn(100, sAngle);
	if(sAngle == 0) stopBC();
}

void cube2(int fAngle = -7, int sAngle = 7) {
	turn(100, fAngle);
	if(fAngle == 0) stopBC();
	open();
	driveCM(100, 9);
	stopBC();
	close();
	delay(100);
	driveCM(100, -9);
	stopBC();
	turn(100, sAngle);
	if(sAngle == 0) stopBC();
}

void cube3(int fAngle = 9, int sAngle = -9) {
	turn(100, fAngle);
	if(fAngle == 0) stopBC();
	open();
	driveCM(100, 9);
	stopBC();
	close();
	delay(100);
	driveCM(100, -9);
	stopBC();
	turn(100, sAngle);
	if(sAngle == 0) stopBC();
}

void cube4(int fAngle = 23, int sAngle = -23) {
	turn(100, fAngle);
	if(fAngle == 0) stopBC();
	open();
	driveCM(100, 10);
	stopBC();
	close();
	delay(100);
	driveCM(100, -10);
	stopBC();
	turn(100, sAngle);
	if(sAngle == 0) stopBC();
}
