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