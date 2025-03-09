//CHANGE K DEPENDING ON DISTANCE
float stabilizeK(float current_distance, float known_distance, float k) {
	return (current_distance / known_distance) * k;
}

float getColorHTSashaNI(tHTCS2 sensor) {
	readSensor(&sensor);
	return sensor.color;
}

//GET CMYK FROM RGB
void rgbToCmyk(int r, int g, int b, float &c, float &m, float &y, float &k) {
    float rNorm = r / 255.0;
    float gNorm = g / 255.0;
    float bNorm = b / 255.0;

    k = 1 - max3(rNorm, gNorm, bNorm);

    if (k < 1) {
        c = (1 - rNorm - k) / (1 - k);
        m = (1 - gNorm - k) / (1 - k);
        y = (1 - bNorm - k) / (1 - k);
    } else {
        c = 0;
        m = 0;
        y = 0;
    }
}

void printCmyk(tHTCS2 sensor) {
	float r, g, b, c, m, y, k;
	while (true) {
		readSensor(&sensor);
		r = sensor.red;
		g = sensor.green;
		b = sensor.blue;
		rgbToCmyk(r, g, b, c, m, y, k);
		displayBigStringAt(0,120,"r %d",r);
		displayBigStringAt(0,100,"g %d",g);
		displayBigStringAt(0,80,"b %d",b);

		displayBigStringAt(50,120,"c %f",c);
		displayBigStringAt(50,100,"m %f",m);
		displayBigStringAt(50,80,"y %f",y);
		displayBigStringAt(50,60,"k %f",k);
	}
}
