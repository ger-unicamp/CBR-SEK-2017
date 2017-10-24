/*
**
** Código principal do robô da categoria IEEE SEK 2017
** Baseado em uma máquina de estados dependente de sensores ultrassônico e de cor
** GER - Grupo de Estudos em Robótica
** 23/10/2017
**
*/

/* Definição de estados */
#define RETO 			1
#define INTERSECCAO		2
#define CAPTURAR		3
#define RAMPA_IDA		4
#define PLAZA			5
#define RAMPA_VOLTA		6

/* Outras definições */
#define DIST_BONECO		30

/* Função para Retornar a Cor lida pelo Sensor 
** Params: porta conectada do sensor de cor
*/
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

/* Função para saber se existe boneco a ser recolhido ou não 
** Params: nenhum
*/
bool ultrassonico(){
	int vet[11];
	int i;
	int j;
	int aux;
	int k = 10;

	//Lê 11 valores de distância em CM
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

/* Função Principal */
task main(){
	/* declaração de variáveis*/
	//Pilha p;
	bool ultrassonico, plaza = false; 
	TLegoColors cor;
	int estado = RETO;
	/* inicialização necessárias */
    //iniciar_pilha(tam);


    /* loop infinito*/
    while (true){
    	ultrassonico = ultrassonico();
    	cor = getColor(S2);

    	if(cor == colorWhite){
    		if(!ultrassonico){
    			// if(!plaza){ // fazer função usando ultrassonico para saber se é plaza ou não
    			estado = RETO;
				//}else
				// estado = PLAZA;
    		}
    		else
    			estado = CAPTURAR;
    	}else{
    		// robô vai poucos cm a frente e faz nova leitura da cor 
    		/* if(!rampa){
				estado = INTESECCAO;
    		}else{
				// tratar caso para rampa ida e volta -> depende da sequencia de cores
    		}
    		*/
    	}

    	switch(estado){
    		case RETO:
    			// chamar as funções relativas a este estado
    			break;
    		case CAPTURAR:
    			// chamar as funções relativas a este estado
    			break;
    		case INTESECCAO:
    			// chamar as funções relativas a este estado
    			break;
    		case RAMPA_IDA:
    			// chamar as funções relativas a este estado
    			break;
    		case PLAZA:
    			// chamar as funções relativas a este estado
    			break;
    		case RAMPA_VOLTA:
    			// chamar as funções relativas a este estado
    			break;	
    		default:
    			break;
    	}
    }
}

