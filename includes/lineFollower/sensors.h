#ifndef __SENSORS_H__
#define __SENSORS_H__

#include "../sensors/hitechnic/drivers/hitechnic-colour-v2.h"

void checkSensorsWork() {
	tSensors sensor_list[3] = {S1, S2, S3};
	for (int i = 0; i < 4; i++) {
		if (SensorValue[sensor_list[i]] == 0) {
			while (1 == 1) {
				displayBigStringAt(0, 120, "Error! Sensor isnt connected!")
			}
		}
	}
}

void sensorRGB(tSensors sensor, float &r, float &g, float &b) {
	int r1, g1, b1;
	if(sensor == leftS) {
		getColorRawRGB(sensor, r1, g1, b1);
		r = map(r1, r1Min, r1Max, 100);
		g = map(g1, g1Min, g1Max, 100);
		b = map(b1, b1Min, b1Max, 100);
	} else if (sensor == rightS){
		getColorRawRGB(sensor, r1, g1, b1);
		r = map(r1, r2Min, r2Max, 100);
		g = map(g1, g2Min, g2Max, 100);
		b = map(b1, b2Min, b2Max, 100);
	} else {
		getColorRawRGB(sensor, r1, g1, b1);
		r = map(r1, r1Min, r1Max, 100);
		g = map(g1, g1Min, g1Max, 100);
		b = map(b1, b1Min, b1Max, 100);
	}
}

void sensorHSV(tHTCS2 &sen, float &h, float &s, float &v) {
	float r, g, b;
	readSensor(&sen);
	r = sen.red;
	g = sen.green;
	b = sen.blue;
	float maxx = max3(r, g, b);
	float minn = min3(r, g, b);

	h = 0;
	if(maxx == r && g >= b)
		h = (60 * (g - b)) / (maxx - minn + 0.001);
	else if(maxx == r && g < b)
		h = (60 * (g - b)) / (maxx - minn + 0.001) + 360;
	else if(maxx == g)
		h = (60 * (b - r)) / (maxx - minn + 0.001) + 120;
	else
		h = (60 * (r - g)) / (maxx - minn + 0.001) + 240;

	s = 0;
	if(maxx != 0)
    s = 1 - (minn / (maxx  + 0.001));
  	v = maxx;
}

void sensorAll(tSensors sensor, float &r, float &g, float &b, float &h, float &s, float &v) {
	sensorRGB(sensor, r, g, b)
	float maxx = max3(r, g, b);
	float minn = min3(r, g, b);

	h = 0;
	if(maxx == r && g >= b)
		h = (60 * (g - b)) / (maxx - minn + 0.001);
	else if(maxx == r && g < b)
		h = (60 * (g - b)) / (maxx - minn + 0.001) + 360;
	else if(maxx == g)
		h = (60 * (b - r)) / (maxx - minn + 0.001) + 120;
	else
		h = (60 * (r - g)) / (maxx - minn + 0.001) + 240;

	s = 0;
	if(maxx != 0)
    s = 1 - (minn / (maxx  + 0.001));
  	v = maxx;
}

void tomshinRgbToHsv(float r, float g, float b, float &h, float &s, float &v) {
	float max_ = max3(r, g, b);
	float min_ = min3(r, g, b);
	float delta = max_ - min_;
	v = max_;
	if (max_ != 0) {
		s = delta / max_;
		if (r = max_) {h = (g - b) / delta;}
		else if (g = max_) {h = 2 + (b - r) / delta}
		else {h = 4 + (r - g) / delta}
		h *= 60;
		if (h < 0) {h += 360;}
	} else {
		s = 0;
		h = -1;
	}
}

void scanValues(tSensors sensor, float &r, float &g, float &b, float &h, float &s, float &v) {
	long rlong, glong, blong;
	getColorRawRGB(sensor, rlong, glong, blong);
	r = rlong;
	g = glong;
	b = blong;
	tomshinRgbToHsv(r, g, b, h, s, v);
}

#endif
