/*
**
** C�digo simples para testar o reconhecimento da rampa pelo rob�
**
*/

#pragma config(Sensor, S1,     ultrassonico,   sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     sensor_cor,     sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          dir,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          esq,           tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          cancela,       tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define NORMAL	0
#define RAMPA 	1

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

task main()
{
	TLegoColors cor;
	setMotorTarget (cancela, 90, 20);
	int estado = NORMAL;

	while(true){
		// ve cor da pista
		cor = getColor(S2);
		if(cor == colorWhite){
			setMotorSpeed(dir, 20);
			setMotorSpeed(esq, 20);
			estado = NORMAL;
		}else{
			// se cor � vermelha, pode ser que seja inicio de rampa
			if(cor == colorRed){
				// anda devagar pra frente
				setMotorSpeed(dir, 5);
				setMotorSpeed(esq, 5);
				delay(800);
				// l� de novo a cor
				cor = getColor(S2);
				// se a cor for verde, entao � rampa
				if(cor == colorGreen){
					estado = RAMPA;
				}
			}
      if(cor == colorYellow && estado == RAMPA){
				setMotorSpeed(dir, 5);
				setMotorSpeed(esq, 5);
				delay(800);
				cor = getColor(S2);
				if(cor == colorGreen){
					estado = NORMAL;
				}
			}
		}

		if(estado == RAMPA){
			delay(2000);
			setMotorSpeed(dir, 10);
			setMotorSpeed(esq, -10);
			delay(2000);

		}
	}
}
