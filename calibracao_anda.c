#pragma config(Sensor, S1,     ult,            sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     color,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     gyro,           sensorEV3_Gyro, modeEV3Gyro_RateAndAngle)
#pragma config(Motor,  motorA,          dir,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          esq,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          cancela,       tmotorNXT, PIDControl, encoder)


void anda_x_cm (float x){
	float encoder;
	int sinal;

	encoder = (x*17.5);

	if (encoder >= 0){
		sinal = 1;
	}
	else{
		sinal = -1;
	}


	setMotorSyncEncoder(dir, esq, 0, encoder, sinal*30);

	waitUntilMotorStop(dir);
	waitUntilMotorStop(esq);

	setMotorReversed(dir, false);
	setMotorReversed(esq, false);
}


task main()
{
	anda_x_cm(30);
	sleep(2000);
	anda_x_cm(-30);
}
