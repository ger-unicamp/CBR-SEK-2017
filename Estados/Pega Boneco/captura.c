#pragma config(Sensor, S1,     ult,            sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     ,               sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     giro,           sensorEV3_Gyro)
#pragma config(Motor,  motorA,          dir,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          esq,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          cancela,       tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* Defini��o de estados */
#define RETO 			1
#define INTERSECCAO		2
#define CAPTURAR		3
#define RAMPA_IDA		4
#define PLAZA			5
#define RAMPA_VOLTA		6

/* Outras defini��es */
#define DIST_BONECO		25
#define DIST_ANDAR 30
#define TAM 6
#define POTENCIA 25 / 30
#define FRENTE 1
#define TRAS -1
#define ANTIHORARIO -1 //ESQUERDA
#define HORARIO 1 //DIREITA
#define DESLIGA 0
//int bonecos_total = 0;

/*Funcao girar robo
** Param: angulo, sentido
*/
void GirarRobo(int degree, int sentido){
//Direita Angulo Negativo - angulo diminou se for para direita
//Esquerda Angulo Positivo = angulo aumenta se for para esquerda

	//SET GIRO
	AndarReto(DESLIGA);

	//Verificar Angulo
	if(degree == 90){
		degree = degree - 10;
	}else if(degree == 180){
		displayTextLine(1,"ANGULO 180");
		degree = degree - 5;
	}

	if(degree == 0 && sentido == FRENTE){
		AndarReto(FRENTE);
	}

	resetGyro(S3);
	delay(1500);

	 repeatUntil(abs(getGyroDegrees(S3)) > degree){
	   if(sentido == HORARIO){ //Gira para direita
		   	displayTextLine(3,"girando sentido horario");
			  setMotorSpeed(esq, FRENTE*POTENCIA_GIRO);
			  setMotorSpeed(dir, TRAS*POTENCIA_GIRO);
			  //delay(2000);
		}else{
			displayTextLine(3,"girando sentido antihorario");
		  setMotorSpeed(esq, TRAS*POTENCIA_GIRO);
		  setMotorSpeed(dir, FRENTE*POTENCIA_GIRO);
		  //delay(2000);
		}
	}

	 //Stop the motors at the end of the turn
	 setMotorSpeed(esq, DESLIGA);
	 setMotorSpeed(dir, DESLIGA);
	 delay(1500);
	 resetGyro(S3);
	 delay(1500);
}

/*Funcao para andar x cm
** Param: distancia
*/
void anda_x_cm (float x){
	float angulo;

	angulo = (x*20.835);

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

/*Funcao andar reto
** Param: sentido
*/
void AndarReto (int sentido){
	setMotorSync(dir,esq,0,sentido*POTENCIA);
}

/*Funcao para girar robo
** Param: sentido do giro
*/
void GirarRobo(int degree, int sentido){
	//Keep looping until the gyro sensor reads greater
	//than 90 degrees (from latest reset position)
	repeatUntil(getGyroHeading(S4) > degree){

		if(sentido == ANTIHORARIO){
			//Point turn to the left
			setMotorSpeed(esq, -50);
			setMotorSpeed(dir, 50);
			}else{
			//Point turn to the right
			setMotorSpeed(esq, 50);
			setMotorSpeed(dir, -50);
		}
	}

	if(sentido == FRENTE){
		AndarReto(FRENTE);
	}


	//Stop the motors at the end of the turn
	setMotorSpeed(esq, 0);
	setMotorSpeed(dir, 0);
	delay(100);
	resetGyro(S4);
}

/*Funcao para pegar boneco
** Param:
*/
void pega_boneco(){

	GirarRobo(90,HORARIO); //giro (direita)
	setMotorTarget (cancela, 140, 10);
	waitUntilMotorStop (cancela);
	anda_x_cm (DIST_ANDAR);
	setMotorTarget (cancela, 0, 5);
	waitUntilMotorStop (cancela);
	anda_x_cm (DIST_ANDAR);
	GirarRobo(90,ANTIHORARIO);//giro (esquerda);
}

/* Fun��o para saber se existe boneco a ser recolhido ou n�o
** Params: nenhum
*/
bool ultrassonico(){
	int vet[11];
	int i;
	int j;
	int aux;
	int k = 10;

	//L� 11 valores de dist�ncia em CM
	for (i=0; i<11; i++){
		vet[i] = getUSDistance(ult);
	}

	//Bubble Sort
	for(i = 0; i < 11; i++){
		for(j = 0; j < k; j++){
			if(vet[j] > vet[j+1]){
				aux = vet[j];
				vet[j] = vet[j+1];
				vet[j+1]=aux;
			}
		}
		k--;
	}

	//Ver se o sensor achou o boneco e retorna true ou false
	if (vet[5] < DIST_BONECO){
		return true;
		}else{
		return false;
	}
}


task main(){
bool ult;
resetGyro(S4);

//int estado = RETO;
//TLegoColors cor;


	while(true){
		ult = ultrassonico();
	//	cor = getColor(S2);

		if(ult == true){
			pega_boneco();
		}else{
			AndarReto(FRENTE);
		}
	}


}