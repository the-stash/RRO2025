#ifndef __COLORSCHECKERS_H__
#define __COLORSCHECKERS_H__


#include "drivers/common-light.h"
#include "../../lineFollower/sensors.h"
#include "math.h"

int blueCnt = 0;

// ALLIANCE {
bool checkColor(tSensors sensor, lineColor color) {
	float r, g, b;
	sensorRGB(sensor, r, g, b);
	return color.minR <= r && r <= color.maxR && color.minB <= b && b <= color.maxB && color.minG <= g && g <= color.maxG;
}

bool checkHSVColor(tHTCS2 sensor, colorHSV color, float h, float s, float v) {
	return ((color.minH <= h && h <= color.maxH) ||(color.minH2 < 0 ? false : color.minH2 <= h) && (color.maxH2 < 0 ? false : h <= color.maxH2)) && color.minS <= s && s <= color.maxS;
}

int getColor(tHTCS2 sensor) {
	float h, s, v;
	h = sensor.hue;
	s = sensor.saturation;
	v = sensor.value;
	if(checkHSVColor(sensor, blue, h, s, v)) {
		return 2;
	} else if (checkHSVColor(sensor, green, h, s, v)) {
		return 3;
	} else if (checkHSVColor(sensor, yellow, h, s, v)) {
		return 4;
	} else if (checkHSVColor(sensor, white, h, s, v)) {
		return 6;
	} else if (checkHSVColor(sensor, black, h, s, v)) {
		return 1;
	} else if (checkHSVColor(sensor, red, h, s, v)) {
		return 5;
	}
	return -1;
}
// } NOT ALLIANCE

//GET RGB AND HSV FROM HITECH
void getRGBHSVht(tHTCS2 sensor, float &r, float &g, float &b, float &h, float &s, float &v, float &color) {
	readSensor(&sensor);
	r = sensor.red;
	g = sensor.green;
	b = sensor.blue;
	color = sensor.color;
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

//GET PRECENTS HITECH
void getPercentsHT(tHTCS2 sensor, float &r_percent, float &g_percent, float &b_percent, float &h_percent, float &s_percent, float &v_percent) {
	float r, g, b, h, s, v, htcolor;
	getRGBHSVht(sensor, r, g, b, h, s, v, htcolor);
	float sum_rgb = r + g + b;
	float sum_hsv = h + s + v;
	r_percent = r / sum_rgb * 100;
	g_percent = g / sum_rgb * 100;
	b_percent = b / sum_rgb * 100;
	h_percent = h / sum_hsv * 100;
	s_percent = s / sum_hsv * 10000;
	v_percent = v / sum_hsv * 100;
}

float getRed(tHTCS2 sensor) {
	float r, g, b, h, s, v, htcolor;
	getRGBHSVht(sensor, r, g, b, h, s, v, htcolor);
	return r;
}

float getSaturation(tHTCS2 sensor) {
	float r, g, b, h, s, v, htcolor;
	getRGBHSVht(sensor, r, g, b, h, s, v, htcolor);
	return s;
}

//GET COLOR HITECH
int getColorHTSasha(tHTCS2 sensor) {
	float h, s, v, r, g, b, ht_color;
	float r_percent, g_percent, b_percent;
	float h_percent, s_percent, v_percent;

	getRGBHSVht(sensor, r, g, b, h, s, v, ht_color);
	if (r == 0) {r = 1;}
	else if (g == 0) {g = 1;}
	else if (b == 0) {b = 1;}
	else if (h == 0) {h = 1;}
	else if (s == 0) {s = 1;}
	else if (v == 0) {v = 1;}
	getPercentsHT(sensor, r_percent, g_percent, b_percent, h_percent, s_percent, v_percent);
	int col = 3;
	if (((r > 50 && g > 50 && b > 50) || (h > 239 && r >= 21 && g >= 21 && b >= 21)) && fabs(r - g) < 5.7) {col = 6;}
	else if (in_range(r_percent, 0, 40) && in_range(g_percent, 0, 40) && in_range(b_percent, 0, 43)) {
		if (h <= 218 && h > 3) {col = 3;}
		else {col = 1;}
	}
	else if (max3(r_percent, g_percent, b_percent) == r_percent && r_percent > 38.5) {
		if (g_percent >= 30) {col = 4;}
		else {col = 5;}
	}
	else if (max3(r_percent, g_percent, b_percent) == g_percent || fabs(g_percent - b_percent) < 5.5)
  	else if (max3(r_percent, g_percent, b_percent) == b_percent) {col = 2;}
	return col;
}


// PRINTS

void printPercentHT(tHTCS2 sensor) {
	float r_percent, g_percent, b_percent, h_percent, s_percent, v_percent;
	while (true) {
		getPercentsHT(sensor, r_percent, g_percent, b_percent, h_percent, s_percent, v_percent)
		displayBigStringAt(0, 120, "%.2f", r_percent);
		displayBigStringAt(0, 100, "%.2f", g_percent);
		displayBigStringAt(0, 80, "%.2f", b_percent);
		displayBigStringAt(0, 60, "%.2f", h_percent);
		displayBigStringAt(0, 40, "%.2f", s_percent);
		displayBigStringAt(0, 20, "%.2f", v_percent);
	}
}

void printValuesHT(tHTCS2 sensor) {
	float r, g, b, h, s, v, htcolor;
	while (true) {
		getRGBHSVht(sensor, r, g, b, h, s, v, htcolor);
		displayBigStringAt(0, 120, "%.2f", r);
		displayBigStringAt(0, 100, "%.2f", g);
		displayBigStringAt(0, 80, "%.2f", b);
		displayBigStringAt(0, 60, "%.2f", h);
		displayBigStringAt(0, 40, "%.2f", s);
		displayBigStringAt(0, 20, "%.2f", v);
	}
}

void printValuesHTOnce(tHTCS2 sensor) {
	float r, g, b, h, s, v, htcolor;
	getRGBHSVht(sensor, r, g, b, h, s, v, htcolor);
	displayBigStringAt(0, 120, "%.2f", r);
	displayBigStringAt(0, 100, "%.2f", g);
	displayBigStringAt(0, 80, "%.2f", b);
	displayBigStringAt(0, 60, "%.2f", h);
	displayBigStringAt(0, 40, "%.2f", s);
	displayBigStringAt(0, 20, "%.2f", v);
}

void printPercentHTOnce(tHTCS2 sensor) {
	float r_percent, g_percent, b_percent, h_percent, s_percent, v_percent;
	getPercentsHT(sensor, r_percent, g_percent, b_percent, h_percent, s_percent, v_percent)
	displayBigStringAt(0, 120, "%.2f", r_percent);
	displayBigStringAt(0, 100, "%.2f", g_percent);
	displayBigStringAt(0, 80, "%.2f", b_percent);
	displayBigStringAt(0, 60, "%.2f", h_percent);
	displayBigStringAt(0, 40, "%.2f", s_percent);
	displayBigStringAt(0, 20, "%.2f", v_percent);
}

void printColorHT(tHTCS2 sensor) {
	float scan;
	while (1 == 1) {
		scan = getColorHTSasha(sensor);
		displayBigStringAt(0, 120,"color - %d", scan);
	}
}

void printColorHTOnce(tHTCS2 sensor) {
	float scan;
	scan = getColorHTSasha(sensor);
	displayBigStringAt(0, 120,"color - %d", scan);
}

//MAIN DEBUG
int htDebugger(tHTCS2 sensor, int wait = 100) {
	htmenu:
	string values = "-> values";
	string percents = "xx percents";
	string color_ = "xx color";
	int ht_mode = 0;
	bool e = true;
	htmenu:
	delay(wait);
	eraseDisplay();
	while (e) {
		delay(wait);
		if (getButtonPress(buttonUp) && ht_mode > 0) {
			ht_mode--;
			delay(wait);
		} else if (getButtonPress(buttonDown) && ht_mode < 3) {
			ht_mode++;
			delay(wait);
		}
		if (ht_mode == 0) {
			values = "-> values";
			percents = "xx percents";
			color_ = "xx color";
		} else if (ht_mode == 1) {
			values = "xx values";
			percents = "-> percents";
			color_ = "xx color";
		} else {
			values = "xx values";
			percents = "xx percents";
			color_ = "-> color";
		}
		if (getButtonPress(buttonEnter)) {e = false; delay(wait);}
		else if (getButtonPress(buttonLeft)) {e = false; delay(wait); return 1;}
		displayBigStringAt(20, 100, "%s", values);
		displayBigStringAt(20, 80, "%s", percents);
		displayBigStringAt(20, 60, "%s", color_);
		delay(wait);
	}
	delay(wait);
	eraseDisplay();
	while (!getButtonPress(buttonLeft)) {
		if (ht_mode == 0) {
			printValuesHTOnce(sensor);
		} else if (ht_mode == 1) {
			printPercentHTOnce(sensor);
		} else {
			printColorHTOnce(sensor);
		}
	}
	goto htmenu;
}

#endif
