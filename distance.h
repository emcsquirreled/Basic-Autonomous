/*

    This function use records the distance gone in rotations

*/



float distance = 0;

float distanceF2 = 0;



task Distance()

{

	float holder2;

	float holder3;

	const float WheelCir = 12.55;

	nMotorEncoder[motorA] = 0;

	while(true)

	{

		while(movement != 2) // while robot is moving

		{
			distanceF2 = nMotorEncoder[motorA];  // puts degrees from motor B into variable distance

			nxtDisplayTextLine(1, "distance:  %f", distance);


		}


		if(movement == 2)

		{

			holder2 = distanceF2 / 360;       //covert degrees to rotations

			holder3 = WheelCir * holder2;    //get the distance of inches traveled

			distance = holder3;
		}

  	nxtDisplayCenteredTextLine(7, "Dist2.  %f", distance);

	}





}
