#pragma config(Sensor, S1,     ultrassonico,   sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     sensor_cor,     sensorNone)
#pragma config(Motor,  motorA,          dir,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          esq,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          cancela,       tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Fun��o que devolve a cor lida pelo sensor
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

//Fun��o que faz o rob� andar uma dist�ncia desejada
void anda_x_cm (float x){ 	//O par�metro � a distancia que deve ser percorrida
	float angulo;
	angulo = (x*20.835); //constante obtida de 360/(2*pi*r) onde r � o raio da roda
	if (angulo >= 0){		//Se dist�ncia for negativa, definimos o motor para tr�s
		setMotorReversed(dir, false);
		setMotorReversed(esq, false);
	} else {				//Se dist�ncia for positiva, definimos o motor para frente
		setMotorReversed(esq, true);
		setMotorReversed(dir, true);
	}
	moveMotorTarget(dir, angulo, 20);
	moveMotorTarget(esq, angulo, 20);	//Gira o motor
	waitUntilMotorStop(dir);
	waitUntilMotorStop(esq);
	setMotorReversed(dir, false);
	setMotorReversed(esq, false);	//Definimos o motor para frente (configura��o inicial)
}

//Estado Plaza
/*
Algor�tmo:
1.Andar reto mantendo 77,5 cm* de dist�ncia entre as paredes enquanto cor (branco)
2.Quando cor for preto, usando os dados do encoder dos motores, andar por mais 30 cm (centro do c�rculo preto).
3.Para e levanta a cancela para depositar os bonecos.
4.Anda para tr�s por uma dist�ncia suficiente para sair do c�rculo preto e gira 180�.
5.Andar reto mantendo 77,5 cm de dist�ncia entre as paredes.
6.Ao dectetar faixas de cores mudar de estado
*comprimento do m�dulo: 185 cm
largura do rob�: 30 cm
185-30 = 155 / 2 = 77,5
*/
void estado_plaza (){
	while (getColor(sensor_cor) != colorBlack){			//Anda para frente com uma dist�ncia de no m�nimo 50cm e m�ximo de 100cm de dist�ncia da parede.
		if (getUSDistance(ultrassonico) >100){
			setMotorSpeed(dir, 18);
			setMotorSpeed(esq, 22);
		} else if (getUSDistance(ultrassonico) < 50) {
			setMotorSpeed(dir, 22);
			setMotorSpeed(esq, 18);
		} else {
			setMotorSpeed(dir, 20);
			setMotorSpeed(esq, 20);
		}
	}
	//Anda 30cm, abre a cancela anda 50cm para tr�s, fecha a cancela e gira 180�
	anda_x_cm (30);
	setMotorTarget (cancela, 120, 10);
	waitUntilMotorStop (cancela);
	anda_x_cm (-50);
	setMotorTarget (cancela, 0, 10);
	waitUntilMotorStop (cancela);
	setMotorSpeed(dir, 50); //gira 180� faltando fun��o !! (mero exemplo)
	setMotorSpeed(esq, -50);
	sleep (1570);
	setMotorSpeed(dir, 0);
	setMotorSpeed(esq,0);

	while (getColor(sensor_cor) != colorBlack){		//Volta para a rampa, tentando manter a dist�ncia minima de 50cm e m�xima de 100cm da parede
		if (getUSDistance(ultrassonico) >100){
			setMotorSpeed(dir, 18);
			setMotorSpeed(esq, 22);
		} else if (getUSDistance(ultrassonico) < 50) {
			setMotorSpeed(dir, 22);
			setMotorSpeed(esq, 18);
		} else {
			setMotorSpeed(dir, 20);
			setMotorSpeed(esq, 20);
		}
	}
}


task main{
	estado_plaza();
}
