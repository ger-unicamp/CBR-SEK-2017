#pragma config(Sensor, S1,     ult,            sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     color,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     gyro,           sensorEV3_Gyro, modeEV3Gyro_RateAndAngle)
#pragma config(Motor,  motorA,          dir,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          esq,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          cancela,       tmotorNXT, PIDControl, encoder)

/* Definição de estados */
#define RETO 			1
#define INTERSECCAO		2
#define CAPTURAR		3
#define RAMPA_IDA		4
#define PLAZA			5
#define RAMPA_VOLTA		6
#define SEM_SAIDA		7

/* Outras definições */
#define DIST_BONECO		25
#define DIST_ANDAR 20
#define TAM 6
#define POTENCIA 20 // 30

/* Definicoes de direcoes das interseccoes */
#define DIREITA 1
#define FRENTE 2
#define ESQUERDA 3

/* Definicoes para motores */
#define TRAS -1
#define DESLIGA 0
#define POTENCIA_GIRO 10

/* Definicoes de calibracao */
#define CALIBRA_GIRO 3.227
#define CALIBRA_RETO 21.7


/*Funcao: Gira o robo por certo angulo
Parametros: Angulo (em graus) e Sentido (DIREITA ou ESQUERDA)
*/

void GirarRobo (float angulo, int sentido){
	float encoder;

	encoder = (angulo*CALIBRA_GIRO);

	//GIRAR DIREITA
	if(sentido == DIREITA){
		setMotorSyncEncoder(dir, esq, -100, encoder, 30);

		waitUntilMotorStop(dir);
		waitUntilMotorStop(esq);

		}else{

		if(sentido == ESQUERDA){
			setMotorSyncEncoder(dir, esq, 100, encoder, 30);

			waitUntilMotorStop(dir);
			waitUntilMotorStop(esq);
		}
	}


}

task main()
{

	int i;

	for (i=0;i<4;i++){
		GirarRobo(90,ESQUERDA);
		delay (1000);
	}
	for (i=0;i<4;i++){
		GirarRobo(90,DIREITA);
		delay (1000);
	}
	for (i=0;i<4;i++){
		GirarRobo(180,ESQUERDA);
		delay (1000);
	}
	for (i=0;i<4;i++){
		GirarRobo(180,DIREITA);
		delay (1000);
	}

}
