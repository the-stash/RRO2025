const float cmToScan = 4.8;
const int closeMax = 5;

void getRGB(tHTCS2 sensor, float &r, float &g, float &b) {
    readSensor(&sensor);
    r = sensor.red;
    g = sensor.green;
    b = sensor.blue;
}

void getHSVL(tHTCS2 sensor, float &h, float &s, float &v, float &l) {
    float r, g, b;
    getRGB(sensor, r, g, b);
    float max_ = max3(r, g, b);
    float min_ = min3(r, g, b);
    if (max_ == min_) {h = 0;}
    else if (max_ == r && g >= b) {h = 60 * (g - b) / (max_ - min_);}
    else if (max_ == r && g < b) {h = 60 * (g - b) / (max_ - min_) + 360;}
    else if (max_ == g) {h = 60 * (b - r) / (max_ - min_) + 120;}
    else if (max_ == b) {h = 60 * (r - g) / (max_ - min_) + 240;}

    if (max_ == 0) {s = 0;}
    else {s = 1 - min_ / max_;}

    l = (max_ + min_) / 2;
    v = max_;
}

void getRGBcs(tSensors sensor, long &r, long &g, long &b) {
    long r1, g1, b1;
    getColorRawRGB(sensor, r1, g1, b1);
    r = r1;
    g = g1;
    b = b1;
}

void getHSVLcs(tSensors sensor, float &h, float &s, float &v, float &l) {
    long r, g, b;
    getRGBcs(sensor, r, g, b);
    float max_ = max3(r, g, b);
    float min_ = min3(r, g, b);
    if (max_ == min_) {h = 0;}
    else if (max_ == r && g >= b) {h = 60 * (g - b) / (max_ - min_);}
    else if (max_ == r && g < b) {h = 60 * (g - b) / (max_ - min_) + 360;}
    else if (max_ == g) {h = 60 * (b - r) / (max_ - min_) + 120;}
    else if (max_ == b) {h = 60 * (r - g) / (max_ - min_) + 240;}

    if (max_ == 0) {s = 0;}
    else {s = 1 - min_ / max_;}

    l = (max_ + min_) / 2;
    v = max_;
}

int getColorCS(tSensors sensor) {
    float h, s, v, l;
    getHSVLcs(sensor, h, s, v, l);
    if (v < 20) {return 5;}
    else {
        if (s < 0.3) {return 6}
        else {
            if ((h >= 300 && h <= 360) || (h < 20) ) {return 1;}
            else if (h >= 20 && h < 90) {return 2;}
            else if (h >= 90 && h < 160) {return 3;}
            else if (h >= 160 && h < 300) {return 4;}
        }
    }
}

float getL(tHTCS2 sensor) {
    float h, s, v, l;
    getHSVL(sensor, h, s, v, l);
    return l;
}

// 0.3 cm - min; 5 cm - max
int getColorCloseHT(tHTCS2 sensor, bool withZero = true) {
    float h, s, v, l;
    getHSVL(sensor, h, s, v, l);
    if (withZero && v < 7) {return 0;}
    if (s <= 0.4) {
        if (h >= 90 && h < 210) {return 3;}
        else if (v < 60) {return 1;}
        else {return 6;}
    } else {
        if ((h >= 300 && h <= 360) || (h < 20)) {return 5;}
        else if (h >= 20 && h < 90) {return 4;}
        else if (h >= 90 && h < 210) {return 3;}
        else if (h >= 210 && h < 300) {return 2;}
    }
    return -1;
}

// 5 cm - min; 9 cm - max;
int getColorFarHT(tHTCS2 sensor, bool withZero = true) {
    float h, s, v, l;
    getHSVL(sensor, h, s, v, l);
    if (withZero && v < 7) {return 0;}
    if (s < 0.4 && h > 215) {
        if (v >= 25) {return 6;}
        else {return 1;}
    } else {
        if ((h >= 300 && h <= 360) || (h < 20)) {return 5;}
        else if (h >= 20 && h < 90) {return 4;}
        else if (h >= 90 && h < 220) {return 3;}
        else {return 2;}
    }
}


int getColorHT(tHTCS2 sensor, float cm = cmToScan, bool withZero = true) {
    if (cm <= closeMax) {return getColorCloseHT(sensor, withZero);}
    return getColorFarHT(sensor, withZero);
}
