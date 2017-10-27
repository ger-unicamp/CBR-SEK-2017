#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>



#define DIST_BONECO 25

#define tam 6


//Vetor
typedef struct dados{
    int cor;
    int dir;    
}dados;

//Pilha
typedef struct Pilha{
    int max;
    int topo;
    dados *elems;
}Pilha;


//Inicializar Pilha
Pilha* iniciar_pilha(int tamanho_vetor){

    Pilha* retorno = malloc(sizeof(Pilha)); //Ponteiro para Pilha
    retorno->max = tamanho_vetor; //Inicializar pilha criada
    retorno->topo = 0;
    retorno->elems = malloc(sizeof(dados)*tamanho_vetor);
    return retorno;
    
}


//Verificar Pilha Vazia
bool empty(Pilha *p){

    if(p->topo == 0){ //Pilha Vazua
        return true; 
    }else{
        return false;
    }
}


//Remover
bool pop (Pilha *p){
    if(empty(p) == true){
        printf("Erro: pilha vazia\n");
        return false;
    }else{
        p->elems[--p->topo];
        return true;
    }
}


//Inserir
bool push (Pilha *p, int cor, int dir){
    if(p->topo == p->max){ //Pilha cheia
        printf("Erro: stack overflow\n");
        return false;
    }else{ 
        p->elems[p->topo].cor = cor; 
        p->elems[p->topo++].dir = dir;
        return true;
    }
}


//Imprime
void imprime_pilha(Pilha *p){
int i;

    printf("Imprimir Pilha:\n");

    for(i=0;i<p->topo;i++){
        printf("cor:%d - dir:%d\n",p->elems[i].cor,p->elems[i].dir);
        printf("\n");
    }
}


//Ultrassônico
bool ultrassonico(){
int vet[11];
int i;
int j;
int aux;
int k = 10 ;

    //Leitura do Vetor
    for (i=0; i<11; i++){
        vet[i] = getUSDistance(ult);
    }

    //Ordenação do Vetor
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
    
    //Retorna a Mediana do Vetor
    if (vet[5] < DIST_BONECO){
        return true; //Boneco Encontrado
    }else{
        return false; //Boneco Não Encontrado
    }
}




//Funcao Principal
task main(){
Pilha p; 

    iniciar_pilha(tam);


    
    while (true){

        bool mediana = ultrassonico();
        displaySensorValues(line7, ultra); //Imprime Mediana
        displayVariableValues(line8, mediana); //True - Boneco Entrado

    }



}

