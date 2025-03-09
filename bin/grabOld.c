void grab4objects() {
    driveCM(85, -6, 15, 30);
    turnLine180(75, 120, 20);
    driveCM(85, -6, 15, 30);
    XCross(90, 1, 55);

    //reverse array
    int start = 0;
    int end = 5;
    while (start < end) {
        int temp = scannedColors[start];
        scannedColors[start] = scannedColors[end];
        scannedColors[end] = temp;
        start++;
        end--;
    }

    //logic
    for (int obj = 0; obj < 6; obj++) {
        if (scannedColors[obj] == 1 && scannedColors[obj + 1] == 1) {
            needCross = obj + 1;
            twoObjNear = true;
            break;
        }
        else if (scannedColors[obj] == 1) {
            firstRubb = obj;
            needCross = obj + 1;
            break;
        }
    }
    for (int i = 0; i < 6; i++) {
        if (scannedColors[i] == 1 && scannedColors[i + 1] == 1) {situation = -1; break;}
        if (scannedColors[i] == 1 && scannedColors[i + 1] == 6 && scannedColors[i + 2] == 1) {situation = 2; break;}
        else if (scannedColors[i] == 1 && scannedColors[i + 1] == 6 && scannedColors[i + 2] == 6) {situation = 1; break;}
    }
    
    for (int i = 0; i < needCross - currCross; i++) {
        XCross(40, 1, 40);
    }
    if (twoObjNear) {driveCM(30, 1, 15, 25);}
    else {driveCM(30, 0.8, 15, 25);}
    if (!twoObjNear) {
        stopBC(0);
        turnOneMotor(leftMotor, 60, -86.5, 15, 60); 
        takeDuoLeftRubbishRightNormal(); 
        driveCM(55, -17.23, 55, 55);
        stopBC(0);
        turnOneMotor(leftMotor, 60, 85, 15, 60);
    }
    else {
        stopBC(0);
        turnOneMotor(leftMotor, 50, -86, 15, 60); 
        takeDuo2Rubbish(); 
        driveCM(55, -18.2, 15, 10);
    }
    currCross = needCross;
    if (!twoObjNear) {
        if (situation == 1) {
            for (int i = 0; i < 6; i++) {
                if (firstRubb != i && scannedColors[i] == 1) {
                    needCross = i;
                    for (int i = 0; i < needCross - currCross; i++) {
                        XCross(45, 1, 45, true);
                    }
                    grabSituation1();
                    currCross = needCross;
                    break;
                }
            }
        }
        else if (situation == 2) {
            if (scannedColors[5] != 1) {
                grabSituation2();
                for (int k = 0; k < 6; k++) {
                    if (scannedColors[k] == 1 && k != firstRubb) {
                        currCross = k;
                        break;
                    }
                    else if (scannedColors[k] == 1) {
                        firstRubb = k;
                    }
                }
                break;
            } else {
                grabSituation2Bad();
                flag = false;
                currCross = 0;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            if (i > 1) {
                if (scannedColors[i] == 1 && scannedColors[i - 1] == 6 && scannedColors[i - 2] == 6) {
                    situation = 3;
                    needCross = i - 1;
                    stopBC(0);
                    turnOneMotor(rightMotor, 85, 90, 65, 65);
                    for (int j = 0; j < fabs(currCross - needCross); j++) {
                        XCross(50, 1, 50, true);
                    }
                    stopBC(0);
                    turnOneMotor(rightMotor, 60, -86.5, 35, 60); 
                    takeDuo2Obj();
                    stopBC(0);
                    turnOneMotor(leftMotor, 65, 87, 35, 65);
                    for (int j = 0; j < 6; j++) {
                        if (j > 0) {
                            if (scannedColors[j] == 1) {currCross = j - 2;}
                        }
                    }
                    currCross = needCross;
                    break;
                }     
            } if (i < 4) {
                if (scannedColors[i] == 1 && scannedColors[i + 1] == 6 && scannedColors[i + 2] == 6) {
                    situation = 4;
                    needCross = i - 2;
                    stopBC(0);
                    turnOneMotor(leftMotor, 85, 90, 65, 65);
                    for (int j = 0; j < fabs(currCross - needCross); j++) {
                        XCross(50, 1, 50, true);
                    }
                    stopBC(0);
                    turnOneMotor(leftMotor, 60, -86.5, 35, 60); 
                    takeDuo2Obj();
                    stopBC(0);
                    turnOneMotor(leftMotor, 65, 87, 35, 65);
                    currCross = i + 2;
                    break;
                }     
            }
        }
    }
    needCross = 4;
    if (flag) {
        if (currCross == 4) {driveCM(65, -4, 65, 38); turnLineRight(65, 70, 25);}
        else if (currCross == 5) {driveCM(65, -14.35, 65, 38); turnLineRight(65, 70, 25);}
        else {
            for (int i = 0; i < needCross - currCross; i++) {
                XCross(60, 1, 60, true);
            }
            turnLineRight(65, 70, 25);
        }
    }
}