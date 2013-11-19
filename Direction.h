#include "Logger.h"
#include "hitechnic-gyro.h"

bool gatheringData = true;
float currentHeading = 1;

void setGatheringData(bool gathering);

task getHeading () {
	float deltaTime = 0;
	float prevHeading = 0;
	float currRate = 0;
	time1[T4] = 0;
	while (true) {

		currRate = HTGYROreadRot(GYRO);
		if (gatheringData == true){
			if (abs(currRate) > 5 || abs(currRate) < -5) {

				prevHeading = currentHeading;
				currentHeading = prevHeading + currRate * deltaTime;

				if (currentHeading > 360) currentHeading -= 360;
				else if (currentHeading < 0) currentHeading += 360;
			}
		}
		//	nxtDisplayClearTextLine(4);
		//  nxtDisplayString(4, "%d", currentHeading);
		wait1Msec(1);
		deltaTime = ((float)time1[T4]) / 1000.0;
		if (deltaTime == 0){
			PlaySound(soundBeepBeep);
			wait10Msec(20);
		}
		time1[T4] = 0;
		log_integer(currentHeading);
		log_integer(deltaTime*1000);
		log_integer(currRate);

		//delTime /= 1000;
	}
}

//task getHeading () {
//	float delTime = 0;
//	float prevHeading = 0;
//	float curRate = 0;

//  HTGYROstartCal(GYRO);
//  PlaySound(soundBeepBeep);
//  while (true) {
//    time1[T4] = 0;
//    curRate = HTGYROreadRot(GYRO);
//    if (abs(curRate) > 5 || abs(curRate) < -5) {
//      prevHeading = currentHeading;
//      currentHeading = prevHeading + curRate * delTime;
//      if (currentHeading > 360) currentHeading -= 360;
//      else if (currentHeading < 0) currentHeading += 360;
//    }
//    wait1Msec(5);
//    delTime = ((float)time1[T4]) / 1000;
//    //delTime /= 1000;
//  }
//}

void setGatheringData(bool gathering){
	gatheringData = gathering;
}
