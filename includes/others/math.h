#ifndef __MATH_H__
#define __MATH_H__

const float diametr = 6.24;
const float base = 17.657;

bool in_range(float value, float a, float b) {
	if (value >= a && value <= b) {
		return true;
	} else {
		return false;
	}
}

int min(int a, int b) {
	if(a > b) return b;
	return a;
}

float min(float a, float b) {
	if(a > b) return b;
	return a;
}

int max(int a, int b) {
	if(a < b) return b;
	return a;
}

float max(float a, float b) {
	if(a < b) return b;
	return a;
}

float min_ff(float a, float b) {
	if(a > b) return b;
	return a;
}

float max_ff(float a, float b) {
	if(a > b) return a;
	return b;
}

float roundSasha(float num, int q) {
    int a = 1;
    for (int i = 0; i < q; i++) {
        a *= 10;
    }
    return round(num * a) / a;
}

float fromCmToDeg(float cm) {
	return (cm / (diametr * PI)) * 360;
}

float fromDegToCm(float degr) {
	return (degr * (diametr / PI)) / 360;
}

float d2d(float angle, float k = 1) {
	return (base * angle * k) / diametr;
}

float map(float val, float l, float r, float maxVal) {
	float a = (val - l) / (r - l);
  return a * maxVal;
}

int lim(int cur, int l, int r) {
	if(cur > r)
    return r;
  else if(cur < l)
    return l;
  return cur;
}

float calcCoefficient(float speed, float default_coef, float default_speed) {
	if(speed == 0) return default_coef;
	return sqrt(speed / default_speed) * default_coef;
}

#endif
