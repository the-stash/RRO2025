const float shipTurn = 68.5;

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
    driveCM(55, -16, 20, 40);
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
    turnOneMotor(leftMotor, 70, shipTurn, 35, 25);
    turnOneMotor(rightMotor, 70, shipTurn, 35, 25);
    toShipRun();
    openLeftNotFull();
    openRightNotFull(true);
    driveCM(65, -6, 30, 30);
    turnOneMotor(rightMotor, 70, -shipTurn, 35, 25);
    turnOneMotor(leftMotor, 70, -shipTurn, 35, 25);
}

void right1left0() {
    turnOneMotor(rightMotor, 70, shipTurn, 35, 25);
    turnOneMotor(leftMotor, 70, shipTurn, 35, 25);
    toShipRun();
    openLeftNotFull();
    openRightNotFull(true);
    driveCM(65, -5, 30, 30);
    turnOneMotor(leftMotor, 70, -shipTurn, 35, 25);
    turnOneMotor(rightMotor, 70, -shipTurn, 35, 25);
}

void twoSituations(bool big) {
    turnOneMotor(leftMotor, 70, shipTurn, 35, 25);
    turnOneMotor(rightMotor, 70, shipTurn, 35, 25);
    toShipRun();
    if (big) {openLeftNotFull(true);}
    else {openRightNotFull(true);}
    driveCM(75, -5, 60, 60);
    turnOneMotor(rightMotor, 70, -shipTurn, 35, 25);
    turnOneMotor(leftMotor, 70, -shipTurn, 35, 25);
    if (big) {closeFullLeft();}
    else {closeFullRight();}
    turnOneMotor(rightMotor, 70, shipTurn, 35, 25);
    turnOneMotor(leftMotor, 70, shipTurn, 35, 25);
    toShipRun(250);
    if (big) {openRightNotFull(true);}
    else {openLeftNotFull(true);}
    driveCM(75, -5, 60, 60);
    turnOneMotor(leftMotor, 70, -shipTurn, 35, 25);
    turnOneMotor(rightMotor, 70, -shipTurn, 35, 25);
}

void leaveRubbishCellsR(bool fr, bool fl) {
    driveCM(62, -10, 25, 30);
    if (fr) {closeFullRight();}
    if (fl) {closeFullLeft();}
    liftSomeRight2(true);
    driveCM(62, 10, 25, 30);
    turnOneMotor(rightMotor, 50, 30, 50, 50);
    turnOneMotor(rightMotor, 50, -30, 50, 50);
}

void leaveRubbishCellsL(bool fr, bool fl) {
    driveCM(62, -10, 25, 30);
    if (fr) {closeFullRight();}
    if (fl) {closeFullLeft();}
    liftSomeLeft2(true);
    driveCM(62, 10, 25, 30);
    turnOneMotor(leftMotor, 50, 30, 50, 50);
    turnOneMotor(leftMotor, 50, -30, 50, 50);
}

void sortRubbish(int *elements) {
    bool mflagl = false;
    bool mflagr = false;
    for (int i = 3; i > -1; i--) {
        if (elements[i] == -1) {
            if (i == 2) {driveCM(60, 4, 60, 60); openFullLeft(true); driveCM(60, -4, 60, 60); mflagl = true;} 
            if (i == 3) {driveCM(60, 4, 60, 60); openFullRight(true); driveCM(60, -4, 60, 60); mflagr = true;}
            if (i == 1) {leaveRubbishCellsR(mflagr, mflagl);}
            if (i == 0) {leaveRubbishCellsL(mflagr, mflagl);}
        }
    }
    driveCM(65, -13, 25, 30);
    turnLineRight(40, 70, 25);
}

void leaveCubes(int *heights, int *cols, int i) {
    int waiting = 140; //55
    if (cols[i] == 6) {
        if (heights[i] == 1) {
            peak();
            openFullRightLowLowSpeed(true);
            delay(waiting);
            closeFullRight(true);
            delay(waiting);
            openFullRightLowLowSpeed(true);
            delay(waiting);
            closeFullRight(true);
        }
        else {
            openFullRightLowLowSpeed(true);
            delay(waiting);
            closeFullRight(true);
        }
    }
}
