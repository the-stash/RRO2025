float shipTurn = 68;
const float copyST = 68;
const float turnPower = 55;

void r() {
    stopBC(2.5);
    delay(2.5);
}

int detectHigh() {
    if (getUSDistance(colorS2) > 7) {return 0;}
    else {return 1;}
}

void reverseArray(int *arr, int size) {
    int start = 0;
    int end = size - 1;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void toShipRun(int w = 110) {
    localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];

    setMotorSpeed(motorB, -65);
    setMotorSpeed(motorC, 65);
    delay(w);
    stopBC(0);

    localDistB = nMotorEncoder[leftMotor];
	localDistC = nMotorEncoder[rightMotor];
}

void swapConts() {
    openFullLeft();
    openFullRight(true);
    driveCM(60, -10, 30, 30);
}

void takeDuoCells() {
    liftSomeLeft();
    liftSomeRight();
    turnLeft(50, 91.5, 35, 20);
    driveCM(55, 17, 20, 40);
    closeFullLeft();
    closeFullRight(true);
    driveCM(55, -14.5, 20, 40);
}

void takeDuoManips() {
    turnLeft(50, 92, 35, 20);
    driveCM(55, -5, 25, 30);
    openFullLeft();
    openFullRight(true);
    driveCM(55, 13.5, 20, 40);
    floorGrabLeft();
    floorGrabRight(true);
    driveCM(55, -7, 20, 40);
    turnLeft(35, -93, 35, 20);
    lineCM(50, 5, 30, 30);
}

void takeRightManip() {
    turnOneMotor(leftMotor, 65, -22, 35, 35);
    driveCM(70, -2, 70, 70);
    openFullRight(true);
    driveCM(65, 10.5, 30, 30);
    floorGrabRight(true);
    driveCM(65, -8.5, 30, 30);
    turnOneMotor(leftMotor, 65, 22, 35, 35);
}

void takeLeftManip() {
    turnOneMotor(rightMotor, 65, -22, 35, 35);
    driveCM(70, -2, 70, 70);
    openFullLeft(true);
    driveCM(65, 10.5, 30, 30);
    floorGrabLeft(true);
    driveCM(65, -8.5, 30, 30);
    turnOneMotor(rightMotor, 65, 22, 35, 35);
}

void right0left1() {
    turnOneMotor(leftMotor, turnPower, shipTurn, 35, 25);
    turnOneMotor(rightMotor, turnPower, shipTurn, 35, 25);
    toShipRun();
    openLeftNotFull();
    openRightNotFull(true);
    driveCM(65, -6, 30, 30);
    turnOneMotor(rightMotor, turnPower, -shipTurn, 35, 25);
    turnOneMotor(leftMotor, turnPower, -shipTurn, 35, 25);
}

void right1left0() {
    turnOneMotor(rightMotor, turnPower, shipTurn, 35, 25);
    turnOneMotor(leftMotor, turnPower, shipTurn, 35, 25);
    toShipRun();
    openLeftNotFull();
    openRightNotFull(true);
    driveCM(65, -5, 30, 30);
    turnOneMotor(leftMotor, turnPower, -shipTurn, 35, 25);
    turnOneMotor(rightMotor, turnPower, -shipTurn, 35, 25);
}

void twoSituations(bool big) {
    if (big) {shipTurn += 2;}
    turnOneMotor(leftMotor, turnPower, shipTurn, 35, 25);
    if (big) {shipTurn -= 3;}
    turnOneMotor(rightMotor, turnPower, shipTurn, 35, 25);
    toShipRun(55);
    if (big) {openLeftNotFull(true);}
    else {openRightNotFull(true);}
    driveCM(75, -5, 60, 60);
    turnOneMotor(rightMotor, turnPower, -shipTurn, 35, 25);
    turnOneMotor(leftMotor, turnPower, -shipTurn, 35, 25);
    if (big) {closeFullLeft();}
    else {closeFullRight();}
    if (big) {shipTurn -= 5;}
    turnOneMotor(rightMotor, turnPower, shipTurn, 35, 25);
    turnOneMotor(leftMotor, turnPower, shipTurn, 35, 25);
    toShipRun(250);
    if (big) {openRightNotFull(true);}
    else {openLeftNotFull(true);}
    driveCM(75, -5, 60, 60);
    turnOneMotor(leftMotor, turnPower, -shipTurn, 35, 25);
    turnOneMotor(rightMotor, turnPower, -shipTurn, 35, 25);
    shipTurn = copyST;
}

void leaveCubes(int *heights, int *cols, int i) {
    int waiting = 140; //55
    if (cols[i] == 6) {
        if (heights[i] == 1) {
            peak();
            openFullRightLowLowSpeed(true);
            delay(waiting);
            closeFullRightLowSpeed(true);
            delay(waiting);
            openFullRightLowLowSpeed(true);
            delay(waiting);
            closeFullRightLowSpeed(true);
        }
        else {
            openFullRightLowLowSpeed(true);
            delay(waiting);
            closeFullRightLowSpeed(true);
        }
    }
}
