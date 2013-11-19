// Includes
#include "ObstacleAvoidance.h"
#include "Direction.h"
#include "Collision.h"
// Include other stuff

// Constants
float offsetFactorTurning = 10.5;

// Variables
int previousGoalHeading = 0;
int direction = 0;

void reachRamp();

void driveDistance(int inches, int power);

void reachHeading(int goalHeading);

void reachRamp(){
	determinePath();
}

void driveDistance(int inches, int power){
	movement = 0;
	wait10Msec(5);
	nMotorEncoder[motorA] = 0; // It is good practice to reset encoder values at the start of a function.
	//Calculate inches by multiplying the ratio we determined earlier with the amount of
	//inches to go, then divide by ten as the ratio used is for an inch value.
	//Since we don't want to calculate every iteration of the loop, we will find the clicks needed
	//before we begin the loop.
	inches = inches + -3.5;

	int tickGoal = ((360.0 * inches ) / 12.12);
	while(abs(nMotorEncoder[motorA]) < tickGoal && (movement != 2 || power < 0))
	{
		motor[motorD] = power;  // The nice thing about encoders is that we can use any power value we want, and
		motor[motorE] = -power; // still get the same distance.
		//motor[motorB] = power;
		//motor[motorC] = power;

		//nxtDisplayTextLine(6, "dist  %f", nMotorEncoder[motorA]);
		//nxtDisplayTextLine(4, "tickGoal  %f", tickGoal);
	}
	if (movement == 2 && power > 0){
		StopAllTasks();
	}
	motor[motorE] = 0;
	motor[motorD] = 0;
	wait10Msec(2);
	//motor[motorD] = 0;
	//motor[motorE] = 0;
}

void reachHeading(int goalHeading){
// goalHeading = goalHeading - 2;
	setGatheringData(true);
	while(goalHeading>360){
		goalHeading-=360;
	}
	while(goalHeading<0){
		goalHeading+=360;
	}
	int staticCurrentHeading = currentHeading;
	if (staticCurrentHeading < goalHeading) {
		staticCurrentHeading += 360;
	}
	int left = staticCurrentHeading - goalHeading;
	if (left > 180){
		direction = 1;
	}else{
		direction = -1;
	}
	motor[motorD] = 50 * direction;
	motor[motorE] = 50 * direction;

	while (abs(goalHeading - currentHeading) > offsetFactorTurning){
		log_integer(currentHeading);
		wait1Msec(1);
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
	motor[motorD] = 0;
	motor[motorE] = 0;
	wait10Msec(20);
	setGatheringData(false);
	previousGoalHeading = goalHeading;
}
