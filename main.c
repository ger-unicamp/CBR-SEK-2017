#pragma config(Sensor, S1,     ultraev3,       sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     color,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     ultranxt,       sensorSONAR)
#pragma config(Motor,  motorA,          dir,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          esq,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          cancela,       tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
**
** C�digo principal do rob� da categoria IEEE SEK 2017
** Baseado em uma m�quina de estados dependente de sensores ultrass�nico e de cor
** GER - Grupo de Estudos em Rob�tica
** 09/11/2017
**
*/

/* Defini��o de estados */
#define RETO 			1
#define INTERSECCAO		2
#define CAPTURAR		3
#define RAMPA		4
#define PLAZA			5
#define SEM_SAIDA		6

/* Outras defini��es */
#define DIST_BONECO		30
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
#define CALIBRA_GIRO 3.25
#define CALIBRA_RETO 21.7

/*Informacoes*/
typedef struct dados{
	TLegoColors cor;
	int dir;
}dados;

// Topo da pilha
int topo, interseccoes = 0;
int DIST_PISO = 0;

/*Pilha*/
typedef struct Pilha{
	int max;
	dados elems[TAM];
}Pilha;

/* Variaveis globais */
int sem_saida = 0;
int estado = RETO;
bool plaza = false, volta = false;

/*Funcao para andar x cm
** Param: distancia
*/
void anda_x_cm (float x){
	float encoder;
	int sinal;

	encoder = (x*CALIBRA_RETO);

	if (encoder >= 0){
		sinal = 1;
		} else {
		sinal = -1;
	}

	setMotorSyncEncoder(dir, esq, 0, encoder, sinal*POTENCIA);

	waitUntilMotorStop(dir);
	waitUntilMotorStop(esq);

	setMotorReversed(dir, false);
	setMotorReversed(esq, false);

}
/* Funcao para subir rampa
** Params: nothing
*/
void rampa(){
	setMotorSync(dir,esq,0,30);
}

/*Funcao inserir
** Param: ponteiro para pilha, direcao e cor
*/
bool push (Pilha *p, TLegoColors cor, int dir){
	if(topo == p->max){ //Pilha cheia
		//displayBigTextLine(line6,"Erro: stack overflow\n");
		return false;
		}else{
		p->elems[topo].cor = cor;
		p->elems[topo++].dir = dir;
		return true;
	}
}

/*Funcao imprime
// Param: ponteiro para pilha
void imprime_pilha(Pilha p){
int i;
//displayBigTextLine(line1,"Imprimir Pilha:\n");
for(i=0;i<topo;i++){
//displayBigTextLine(line1,"cor:%d",p.elems[i].cor);
//displayBigTextLine(line2,"dir:%d",p.elems[i].dir);
}
}*/

/*Funcao andar reto
** Param: sentido
*/
void AndarReto (int sentido){
	setMotorSync(dir,esq,0,sentido*POTENCIA);
}


/*Funcao girar robo
** Param: angulo (em graus), sentido (DIREITA ou ESQUERDA)
*/
void GirarRobo (float angulo, int sentido){
	float encoder;

	encoder = (angulo*CALIBRA_GIRO);

	//GIRAR DIREITA
	if(sentido == DIREITA){
		setMotorSyncEncoder(dir,esq,-100,encoder,30);

		waitUntilMotorStop(dir);
		waitUntilMotorStop(esq);

		}else{
		if(sentido == ESQUERDA){
			setMotorSyncEncoder(dir,esq,100,encoder,30);

			waitUntilMotorStop(dir);
			waitUntilMotorStop(esq);

		}
	}
}


/* Funcao do estado captura bonecos
** Params: nothing
*/
void pega_boneco(){
	anda_x_cm (5); //teste para deixar o boneco no centro
	GirarRobo(90,ESQUERDA); //giro (direita)
	setMotorTarget (cancela, 120, 10); // abre cancela
	waitUntilMotorStop (cancela);
	anda_x_cm (DIST_ANDAR); // anda para pegar boneco
	setMotorTarget (cancela, 0, 5);
	waitUntilMotorStop (cancela);
	anda_x_cm (-DIST_ANDAR);
	GirarRobo(90,DIREITA);//giro (esquerda);
}

/* Fun��o para Retornar a Cor lida pelo Sensor
** Params: porta conectada do sensor de cor
*/
TLegoColors getColor(tSensors sensor)
{
	//Creates variables to store the red, green, and blue values
	long int redValue;
	long int greenValue;
	long int blueValue;

	//Get the value of all three channels of the color sensor
	//and store it in the variables
	getColorRGB(sensor, redValue, greenValue, blueValue);
	// se alguma COR for detectada
	if((redValue != 0) && (greenValue != 0) && (blueValue != 0)){
		// BRANCO
		if(redValue >= 40 && greenValue >= 40 && blueValue >= 30){
			return colorWhite;
			}else{
			// VERDE
			if((redValue <= 12) && (greenValue >= 25) && (blueValue <= 15)){
				return colorGreen;
				}else{
				// VERMELHO MALDITO
				if((redValue >= 35) && (greenValue <= 15) && (blueValue <= 12)){
					return colorRed;
					}else{
					// AMARELO
					if((redValue >= 30) && (greenValue >= 15) && (blueValue <= 10)){
						return colorYellow;
						}else{
						// AZUL
						if((redValue <= 15) && (greenValue >= 30) && (blueValue >= 30)){
							return colorBlue;
							}else{
							// PRETO
							if((redValue <= 10) && (greenValue <= 10) && (blueValue <= 10)){
								return colorBlack;
							}
						}
					}
				}
			}
		}
	}
	// nenhuma cor lida
	return colorNone;
}

/*
** Funcao para uso do sensor ultrassonico
** Params: sensor usado (do ev3 ou nxt, nesse caso)
*/
bool ultrassonico(tSensors sensor){
	int vet[11];
	int i;
	int j;
	int aux;
	int k = 10;

	// caso a leitura seja do sensor do ev3 (para detectar bonecos)
	if(sensor == ultraev3){
		//L� 11 valores de dist�ncia em CM
		for (i=0; i<11; i++){
			vet[i] = getUSDistance(sensor);
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
	else{
		// se for para ler sensor do nxt
		if(sensor == ultranxt){
			for (i=0; i<11; i++){
				vet[i] = SensorValue[S3];
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
			if(vet[5] > DIST_PISO){
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

/*Funcao para verificar se cor esta na pilha
** Param: ponteiro para pilha, cor
*/
bool checa_cor(Pilha p, TLegoColors cor){
	int i;
	for(i=0;i<TAM;i++){
		if(p.elems[i].cor == cor){
			return true;
		}
	}
	return false;
}

/*Funcao para verificar se dir esta na pilha
** Param: ponteiro para pilha, direcao, cor

bool checa_dir(Pilha p, int dir, TLegoColors cor){
int i;
for(i=0;i<TAM;i++){
if(p.elems[i].dir == dir){
if(p.elems[i].cor == cor){
return true;
}else{
return false;
}
}
}
return false;
}*/

/*Funcao troca sentido das direcoes da pilha
** Param: ponteiro para pilha
*/
void troca(Pilha *p){
	int i;

	for(i=0; i<topo; i++){
		if(p->elems[i].dir == ESQUERDA){
			p->elems[i].dir = DIREITA;
			}else if(p->elems[i].dir == DIREITA){
			p->elems[i].dir = ESQUERDA;
		}
	}
}

/*
** Funcao para mudar direcao da cor na pilha
** Params: pilha e cor lida pelo sensor
*/
bool increment_dir(Pilha *p, TLegoColors cor){
	int i;
	for(i=0;i<TAM;i++){
		if(cor == p->elems[i].cor){
			p->elems[i].dir++;
			return true;
		}
	}
	return false;
}

/*Funcao para o estado interseccao
** Param: ponteiro para pilha, cor
*/
void interseccao(Pilha &p, TLegoColors cor){

	int i;
	int direcao;
	if(!checa_cor(p,cor)){ //se cor for diferente de branco e nao estiver na pilha...
		// coloca na pilha
		push(p,cor,DIREITA);
		playSound(soundLowBuzzShort);
		//	setLEDColor(ledGreenFlash);
		//displayBigTextLine(line2,"PUSH NA PILHA");
		// primeira tentativa sempre vai para a direita
		GirarRobo(90, DIREITA);
		anda_x_cm(25);
		// indica que passou por uma interseccao
		interseccoes++;
		}else{
		if(sem_saida == 1){
			setLEDColor(ledRedPulse);
			playSound(soundFastUpwardTones);
			GirarRobo(90,DIREITA);
			anda_x_cm(25);
			// muda direcao anterior na pilha, pois robo encontrou rua sem saida
			increment_dir(p, cor);
			sem_saida = 0;
		}
		else{
			for(i=0;i<TAM;i++){
				// se tiver cor na pilha
				if(cor == p.elems[i].cor){
					//displayBigTextLine(line4,"temos cor");
					direcao = p.elems[i].dir;
					// passou pela primeira vez por outra interseccao
					interseccoes++;

					// vira de acordo com a direcao na pilha
					if(direcao == DIREITA)
					{
						GirarRobo(90, DIREITA);
					}
					else{
						if(direcao == ESQUERDA)
						{
							GirarRobo(90, ESQUERDA);
						}
					}
					setLEDColor(ledOrangeFlash);
					anda_x_cm(30);
				}
			}
		}
		estado = RETO;
	}
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

	float sensor_esq;
	float sensor_dir;
	float diferenca;

	while (getColor(color) != colorBlack){			//Anda para frente com uma dist�ncia de no m�nimo 50cm e m�ximo de 100cm de dist�ncia da parede.
		if (getUSDistance(ultraev3) > 85){
			setMotorSpeed(dir, 18);
			setMotorSpeed(esq, 22);
			} else if (getUSDistance(ultraev3) < 65) {
			setMotorSpeed(dir, 22);
			setMotorSpeed(esq, 18);
			} else {
			AndarReto (1);
		}
	}
	//Anda pra frente, abre a cancela anda para tr�s, fecha a cancela e gira 180�
	anda_x_cm (15);
	setMotorTarget (cancela, 120, 30);
	waitUntilMotorStop (cancela);
	anda_x_cm (-60);
	setMotorTarget (cancela, 0, 10);
	waitUntilMotorStop (cancela);
	delay(1000);
	sensor_esq = getUSDistance(S1);
	GirarRobo(180,DIREITA);
	delay(1000);
	sensor_dir = getUSDistance(S1);
	diferenca = (sensor_esq - sensor_dir);

	// atraves do ultrassonico ajusta o robo para sair corretamente do plaza
	while (diferenca > 1 || diferenca < -1){
		if (diferenca > 1){
			GirarRobo(90, DIREITA);
			delay(100);
			anda_x_cm(1);
			delay(100);
			GirarRobo(90, DIREITA);
			delay(1000);
			sensor_esq = getUSDistance(S1);
			GirarRobo(180,ESQUERDA);
			delay(1000);
			sensor_dir = getUSDistance(S1);
			diferenca = (sensor_esq - sensor_dir);
			} else {
			GirarRobo(90, ESQUERDA);
			delay(100);
			anda_x_cm(1.5);
			delay(100);
			GirarRobo(90, ESQUERDA);
			delay(1000);
			sensor_esq = getUSDistance(S1);
			GirarRobo(180,ESQUERDA);
			delay(1000);
			sensor_dir = getUSDistance(S1);
			diferenca = (sensor_esq - sensor_dir);
		}
	}

	anda_x_cm(50);
	setMotorSpeed(dir,0);
	setMotorSpeed(esq,0);
}

/* Funcao para o estado sem saida
** Param: nothing
*/
void semSaida(){
	playSound(soundLowBuzz);
	// gira o robo
	GirarRobo(180, ESQUERDA);
	sem_saida = 1;
	anda_x_cm(30);
	estado = RETO;
}

task main(){
	playSound(soundException);

	Pilha p;
	int i, aux;
	bool ultev3, ultnxt;
	TLegoColors cor, cor_aux;

	/* inicializa��o necess�rias */
	p.max = TAM;
	topo = 0;
	for(i=0;i<TAM;i++){
		p.elems[i].cor = colorBrown; /*testar inicialziar*/
		p.elems[i].dir = 0;
	}

	// calibra a distancia do robo da superficie de contato
	for(i=0; i < 10; i++){
		aux = SensorValue[S3];
		if(aux > DIST_PISO)
			DIST_PISO = aux;
	}

	while(true){
		setLEDColor(ledRedPulse);
		cor = getColor(S2);

		if(cor != colorNone){
			if(cor == colorBlack){
				AndarReto(DESLIGA);
				delay(1000);
				cor = getColor(S2);
				// se a cor for preta � sem saida
				if(cor == colorBlack && plaza == false){
					AndarReto(TRAS);
					delay(1000);
					AndarReto(DESLIGA);
					estado = SEM_SAIDA;
					playSoundFile("Dog whine");
				}
			}
			else{
				// le a distancia da superficie
				ultnxt = ultrassonico(ultranxt);
				if(!ultnxt){
					// se robo nao estiver saindo da rota, ve se eh interseccao
					if(cor == colorYellow || cor == colorGreen || cor == colorRed){
						anda_x_cm(3);
						AndarReto(DESLIGA);
						delay(500);
						cor_aux = getColor(S2);
						if(cor_aux == cor){
							// apos quatro interseccoes � certeza que a prox cor vermelha sera rampa
							if(interseccoes == 4){
								if(volta == false){
									estado = RAMPA;
								}
								else{
									GirarRobo(180, ESQUERDA);
									troca(p);
									volta = false;
								}
							}
							else{
								if(cor_aux == cor){
									//displayText(line1,"estado interseccao")
									estado = INTERSECCAO;
								}
							}
						}
					}
					else{
						if(cor == colorWhite){
							if(plaza == false){
								estado = RETO;
								// veja se ha bonecos nos postos ao lado do robo
								ultev3 = ultrassonico(ultraev3);
								if(ultev3){
									estado = CAPTURAR;
								}
							}
							else{
								// se passou pela rampa, o estado sera plaza
								estado = PLAZA;
							}
						}
					}
				}
				else{
					// se robo estiver torto, saindo da rua, corrige a direcao com ultrassonico a direita
					while(ultrassonico(ultranxt)){
						AndarReto(DESLIGA);
						AndarReto(TRAS);
						delay(500);
						GirarRobo(10, ESQUERDA);
						GirarRobo(6, DIREITA);
						delay(1000);
					}
				}
			}
		}
		switch(estado){
		case INTERSECCAO:
			interseccao(p,cor);
			break;
		case RETO:
			AndarReto(1);
			break;
		case SEM_SAIDA:
			semSaida();
			break;
		case CAPTURAR:
			pega_boneco();
			// se estiver contrario ao plaza
			if(volta == true){
				//gira o robo 180�
				GirarRobo(180, ESQUERDA);
				troca(p);
				volta = false;
			}
			break;
		case RAMPA:
			// sobe a rampa
			rampa();
			plaza = true;
			break;
		case PLAZA:
			interseccoes = 0;
			// deixa bonecos no plaza
			estado_plaza();
			// troca direcoes na pilha
			troca(p);
			plaza = false;
			// sai do plaza, volta para as ruas
			volta = true;

			// corrige trajetoria se robo estiver torto
			while(ultrassonico(ultranxt)){
				AndarReto(DESLIGA);
				AndarReto(TRAS);
				delay(500);
				GirarRobo(10, ESQUERDA);
				GirarRobo(6, DIREITA);
				delay(1000);
			}
			anda_x_cm(5);
			while(ultrassonico(ultranxt)){
				AndarReto(DESLIGA);
				AndarReto(TRAS);
				delay(500);
				GirarRobo(10, ESQUERDA);
				GirarRobo(6, DIREITA);
				delay(1000);
			}
			break;
		}
	}
}
