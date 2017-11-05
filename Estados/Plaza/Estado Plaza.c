#pragma config(Sensor, S1,     ultrassonico,   sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     sensor_cor,     sensorNone)
#pragma config(Motor,  motorA,          dir,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          esq,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          cancela,       tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

TLegoColors getColor(tSensors sensor){
	bool getColor = false;
	TLegoColors color;

	while(!getColor){
		color = getColorName(sensor);
		if(color != colorNone)
			getColor = true;
		else
			getColor = false;
	}

	return color;
}

void anda_x_cm (float x){
	float angulo;
	angulo = (x*20.835); //20.835 foi obtido de 2*pi*r
	if (angulo >= 0){
		setMotorReversed(dir, false);
		setMotorReversed(esq, false);
	} else {
		setMotorReversed(esq, true);
		setMotorReversed(dir, true);
	}
	moveMotorTarget(dir, angulo, 20);
	moveMotorTarget(esq, angulo, 20);
	waitUntilMotorStop(dir);
	waitUntilMotorStop(esq);
	setMotorReversed(dir, false);
	setMotorReversed(esq, false);
}

void estado_plaza (){
	while (getColor(sensor_cor) == colorWhite){
		if (getUSDistance(ultrassonico) >77.5){
			setMotorSpeed(dir, 18);
			setMotorSpeed(esq, 22);
		} else if (getUSDistance(ultrassonico) < 77.5) {
			setMotorSpeed(dir, 22);
			setMotorSpeed(esq, 18);
		} else {
			setMotorSpeed(dir, 20);
			setMotorSpeed(esq, 20);
		}
		displayMotorValues (line4, dir);
		displayMotorValues (line5, esq);
		displaySensorValues(line6, ultrassonico);
		displayVariableValues(line7, getColor(sensor_cor));
	}
	displayVariableValues(line7, getColor(sensor_cor));
	if (getColor(sensor_cor) == colorBlack){
		anda_x_cm (30);
		setMotorTarget (cancela, 140, 10);
		waitUntilMotorStop (cancela);
		anda_x_cm (-50);
		setMotorTarget (dir, 600, 20);//gira 180�
		setMotorTarget (esq, -600, 20);
	} else {
		estado_plaza ();
	}
	while (getColor(sensor_cor) == colorWhite){
		if (getUSDistance(ultrassonico) >77.5){
			setMotorSpeed(dir, 18);
			setMotorSpeed(esq, 22);
		} else if (getUSDistance(ultrassonico) < 77.5) {
			setMotorSpeed(dir, 22);
			setMotorSpeed(esq, 18);
		} else {
			setMotorSpeed(dir, 20);
			setMotorSpeed(esq, 20);
		}
		displayVariableValues(line7, getColor(sensor_cor));
	}
}


task main{
	estado_plaza();
}