
#define DIST_BONECO 25

void bubble( int v[], int qtd )
{
  int i;
  int j;
  int aux;
  int k = qtd - 1 ;

  for(i = 0; i < qtd; i++)
  {
     for(j = 0; j < k; j++)
     {
        if(v[j] > v[j+1])
        {
            aux = v[j];
        v[j] = v[j+1];
        v[j+1]=aux;
        }
     }
     k--;
  }
}

bool ultrassonico(){
    int vet[11];
    int i;
    for (i=0; i<11; i++){
        vet[i] = getUSDistance(ultrassonico);
    }
    bubble (vet[], 11);
    
    if (vet[5] < DIST_BONECO){
        return true;
    }else{
        return false;
    }
}


task main()
{
    bool a = ultrassonico();
    //displaySensorValues(line4, ultrassonico);
    displayVariableValues(line5, a);
}