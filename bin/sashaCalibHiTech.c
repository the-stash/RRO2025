#pragma config(Sensor, S1,     colorS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S4,     ebat,           sensorNone)
#pragma config(Motor,  motorA,          manipMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorD,          liftMotor,     tmotorEV3_Medium, openLoop, encoder)

#include "../includes/math.h"
#include "../includes/hitechnic-colour-v2.h"
tHTCS2 s;

task main() {
  initSensor(&s, S1);
	while (true) {
		eraseDisplay();
		readSensor(&s);
		displayBigStringAt(0,120,"%d",s.red);
		displayBigStringAt(0,100,"%d",s.green);
		displayBigStringAt(0,80,"%d",s.blue);
		displayBigStringAt(0,40,"%d",s.red + s.green + s.blue);
		delay(50);
	}
}
