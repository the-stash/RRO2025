#pragma config(Sensor, S1,     colorS,         sensorEV3_Color)
#pragma config(Sensor, S2,     leftS,          sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S3,     rightS,         sensorEV3_Color, modeEV3Color_RGB_Raw)
#pragma config(Sensor, S4,     colorS2,        sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          manipMotor2,   tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorD,          manipMotor,    tmotorEV3_Medium, PIDControl, encoder)

#include "includes/sensors/hitechnic/drivers/hitechnic-colour-v2.h"
tHTCS2 sensor;

#include "includes/others/math.h"
#include "includes/others/sound.h"
#include "includes/data/settings.h"
#include "includes/data/lineValues.h"
#include "includes/others/structures.h"
#include "includes/lineFollower/sensors.h"
#include "includes/motors/acceleration.h"
#include "includes/sensors/hitechnic/colorsCheckers.h"
#include "includes/others/debugger.h"
#include "includes/sensors/hitechnic/colorScan.h"
#include "includes/lineFollower/line.h"
#include "includes/manipulators/manipulator.h"
#include "includes/manipulators/manipulator2.h"
#include "includes/others/rroFuncs.h"
#include "includes/lineFollower/navigation.h"
#include "includes/main.h"

task main() {
	initColors();
	startTask(PIDManipRight);
	startTask(initManipRight);
	startTask(PIDManipLeft);
	startTask(initManipLeft);
	runner();
}
