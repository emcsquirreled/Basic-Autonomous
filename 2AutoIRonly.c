#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     GYRO,           sensorAnalogInactive)
#pragma config(Sensor, S4,     IR,             sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "beaconDetection.h"
#include "TurnAngle.h"
#include <JoystickDriver.c>

task main()
{

//Wait for the start command//
waitForStart();
	
//Start getHeading.h//
	HTGYROstartCal(GYRO);
	StartTask(getHeading);
	
//Move forward until it sees the beacon or until 5 sec is up//
	motor[motorD] = -50;
	motor[motorE] = -50;
	time1[T3] = 0;

	while (atBeacon() == false && time1[T3] < 5000) {
		wait1Msec(2);
	}

//Turn 90 to the right//
	TurnAngle(90, false);

	///////////////////////
	
//Move forward for 1 sec//
	motor[motorD] = 80;
	motor[motorE] = 80;

	wait1Msec(1000);

//Stop motors//
	motor[motorD] = 0;
	motor[motorE] = 0;

//Move the block belt for 2.5 sec//
	motor[motorC] = -100;

	wait1Msec(2500);

	motor[motorC] = 0;


//Move backward for 1 sec//
	motor[motorD] = -50;
	motor[motorE] = -50;

	wait1Msec(1000);

	motor[motorD] = 0;
	motor[motorE] = 0;

}
