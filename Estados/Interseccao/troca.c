#define FRENTE 1
#define TRAS -1
#define ANTIHORARIO -1 //ESQUERDA
#define HORARIO 1 //DIREITA

typedef struct dados{
    TLegoColors cor;
    int dir;
    int bonecos_total; // numero de bonecos total na pista
    int bonecos_bifurcacao; //total de bonecos presentes na bifurcacao (esquerda + direita)
    int bonecos_direita; //bonecos esquerda = bonecos_bifurcacao - bonecos_direita
}dados;

typedef struct Pilha{
    int max;
    int topo;
    dados elems[6];
}Pilha;

/*Inicializar Pilha
** Params: tamanho do vetor
*/
Pilha* iniciar_pilha(int tamanho_vetor){
int i;
Pilha* retorno;//Ponteiro para Pilha
retorno->max = tamanho_vetor;
retorno->topo = 0;
    for(i=0;i<tamanho_vetor;i++){
        retorno->elems[i].cor = 0;
        retorno->elems[i].dir = 0;
    }
   return retorno;
}

/*Verificar Pilha Vazia
** Param: ponteiro para pilha
*/
bool empty(Pilha *p){

    if(p->topo == 0){ //Pilha Vazia
        return true;
    }else{
        return false;
    }
}

/*Inserir
** Param: ponteiro para pilha, cor e direcao
**/
bool push (Pilha *p, TLegoColors cor, int dir){
    if(p->topo == p->max){ //Pilha cheia
        displayBigTextLine(line6,"Erro: stack overflow\n");
        return false;
    }else{
        p->elems[p->topo].cor = cor;
        p->elems[p->topo].dir = dir;
        p->topo++;
        return true;
    }
}

/*Imprime
** Param: ponteiro para pilha
*/
void imprime_pilha(Pilha *p){
int i;

	displayBigTextLine(line1,"Imprimir Pilha:\n");

    for(i=0;i<p->topo;i++){
        displayTextLine(line1,"cor:%d",p->elems[i].cor);
        displayTextLine(line2,"dir:%d",p->elems[i].dir);
    }
}

/*Funcao Troca
** Param: ponteiro para pilha
*/
void troca(Pilha *p){
int i;

	for(i=0;i<p->topo;i++){
		if(p->elems[i].dir == FRENTE){
			p->elems[i].dir = TRAS;
		}else if(p->elems[i].dir == ANTIHORARIO){
			p->elems[i].dir = HORARIO;
		}else if(p->elems[i].dir == HORARIO){
			p->elems[i].dir = ANTIHORARIO;
		}
	}

}



task main(){
Pilha *p;
p=iniciar_pilha(6);


}
