//Só funções, sem include e main



/*Funcao para verificar se cor esta na pilha
** Param: ponteiro para pilha, cor
*/
bool checa_cor(Pilha *p, TLegoColors cor){
    int i;
    for(i=0;i<TAM;i++){
        if(p->elems[i].cor == cor){
            displayBigTextLine(line1,"ndeu certo");
            return true;
        }
    }
    return false;
}

/*Funcao para verificar se dir esta na pilha
** Param: ponteiro para pilha, direcao, cor
*/
bool checa_dir(Pilha *p, int dir, TLegoColors cor){
int i;
    for(i=0;i<TAM;i++){
        if(p->elems[i].dir == dir){
            if(p->elems[i].cor == cor){
                displayBigTextLine(line1,"ndeu certo"); //Cor e direcao salvo
            return true;
            }else{
                return false;
            }
        }
    }
    return false;
}

/*Retorna na ultima interseccao
** Param:
*/
void volta(bool plaza){
    int andar = 1;
    while(andar){
        AndarReto(TRAS);
        if(getColor(S2) != colorWhite && ultrassonico() == false && plaza == false){ // Verifica se esta em uma interseccao - verificar cor
            andar = 0;
        }
    }
}

/*Funcao que verificar qual direcao seguir, caso errada, volta para ultiam interseccao
** Param: Ponteiro para pilha, direcao, cor
*/
bool testa_dir(Pilha *p, int direcao, TLegoColors cor, bool plaza){
int andar = 1;

    GirarRobo(90,direcao); //Vira o robo para direcao dada

    while(andar){
        AndarReto(FRENTE); // Andar reto
        if(ultrassonico() == true){ //procura boneco enquanto testa
            bonecos_total++;
                p->elems[p->topo].bonecos_bifurcacao++;
                p->elems[p->topo].bonecos_direita++;
        }

        if(cor != colorWhite && cor != colorBlack){ // Verifica se esta em outra interseccao
            AndarReto(DESLIGA);
            return true;
        }else if(cor == colorBlack){ // Verifica se esta em rua sem saida - chao preto
            AndarReto(DESLIGA);
            volta(plaza); // Funcao que faz o robô voltar até a ultima interseccao
            return false;
        }
    }
    return false;
}

/*Funcao para o estado interseccao
** Param: ponteiro para pilha, cor
*/
void run_rua(Pilha *p, TLegoColors cor, bool plaza){
int i;

    if(ultrassonico() == true){ //Verifica de tem boneco
        bonecos_total++; //contar todos os bonecos
        p->elems[p->topo].bonecos_bifurcacao++; //contar bonecos na bifurcacao
        p->elems[p->topo].bonecos_direita++; //contar numero de bonecos a direita em uma bifurcacao
    }

    if(cor != colorWhite && !checa_cor(p,cor)){ //se cor for diferente de branco e nao estiver na pilha...
        if(!checa_dir(p,ANTIHORARIO,cor) && testa_dir(p,ANTIHORARIO,cor,plaza)){ //verifica se a direcao esta na pilha - ESQUERDA
            push(p,cor,ANTIHORARIO); //testa
        }else if(!checa_dir(p,HORARIO,cor) &&  testa_dir(p,HORARIO,cor,plaza)){
                push(p,cor,FRENTE); //testa
        }else{
            testa_dir(p,HORARIO,cor,plaza);
            push(p,cor,HORARIO);
        }
    }else{
       for(i=0;i<=TAM;i++){ //
         if(cor == p->elems[i].cor){
           GirarRobo(90,p->elems[i].dir);
          }
        }
    }
}
