void directions(int currDir, int finishDir) {
    if (currDir == 0 && finishDir == 1) {turnLineRight(75);}
    if (currDir == 0 && finishDir == 2) {turnLine180(75);}
    if (currDir == 0 && finishDir == 3) {turnLineLeft(75);}

    if (currDir == 1 && finishDir == 0) {turnLineLeft(75);}
    if (currDir == 1 && finishDir == 2) {turnLineRight(75);}
    if (currDir == 1 && finishDir == 3) {turnLine180(75);}

    if (currDir == 2 && finishDir == 0) {turnLine180(75);}
    if (currDir == 2 && finishDir == 1) {turnLineLeft(75);}
    if (currDir == 2 && finishDir == 3) {turnLineRight(75);}

    if (currDir == 3 && finishDir == 0) {turnLineRight(75);}
    if (currDir == 3 && finishDir == 1) {turnLine180(75);}
    if (currDir == 3 && finishDir == 2) {turnLineLeft(75);}
    stopBC(20);
}

void directionsDeg(int currDir, int finishDir) {
    if (currDir == 0 && finishDir == 1) {turnRight(75, 91, 35);}
    if (currDir == 0 && finishDir == 2) {turnLine180(75);}
    if (currDir == 0 && finishDir == 3) {turnLeft(75, 91, 35);}

    if (currDir == 1 && finishDir == 0) {turnLeft(75, 91, 35);}
    if (currDir == 1 && finishDir == 2) {turnRight(75, 91, 35);}
    if (currDir == 1 && finishDir == 3) {turnLine180(75);}

    if (currDir == 2 && finishDir == 0) {turnLine180(75);}
    if (currDir == 2 && finishDir == 1) {turnLeft(75, 91, 35);}
    if (currDir == 2 && finishDir == 3) {turnRight(75, 91, 35);}

    if (currDir == 3 && finishDir == 0) {turnRight(75, 91, 35);}
    if (currDir == 3 && finishDir == 1) {turnLine180(75);}
    if (currDir == 3 && finishDir == 2) {turnLeft(75, 91, 35);}
    stopBC(20);
}

void navigate(int startX, int finishX, int dir, bool degr = false, int &outDir, bool lineAtStart = false) {
    if (startX != finishX) {
        int delta = finishX - startX;
        if (delta < 0) {
            if (!degr) {directions(dir, 2);}
            else {directionsDeg(dir, 2);}
            dir = 2;
        } else if (delta > 0) {
            if (!degr) {directions(dir, 0);}
            else {directionsDeg(dir, 0);}
            dir = 0;
        }
        if (lineAtStart) {lineCM(70, 4.1, 45, 45);}
        QCross(70, fabs(delta), 45);
        startX = finishX;
        outDir = dir;
    }
    outDir = dir;
    /*if (startY != finishY) {
        int delta = finishY - startY;
        if (delta < 0) {
            directions(dir, 3);
            dir = 3;
        } else if (delta > 0) {
            directions(dir, 1);
            dir = 1;
        }
        XCrossManyCrosses(100, fabs(delta), 60);
        startY = finishY;
    }*/
}