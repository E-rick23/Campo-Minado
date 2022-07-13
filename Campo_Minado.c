#include <stdio.h>
#include <stdlib.h>

struct Celula{
    int livre; //Se a casa está vazia ou não 0 ou 1
    int bomba; //Tem bomba ou não tem 0 ou 1
    int vizinhos; // 0 a 4
};

Celula tabuleiro[10][20];

int tam = 10, l, c;

void ComeçarJogo(){
    for(l = 0; l < tam; l++){
        for(c = 0; c < tam; c++){
            tabuleiro[l][c].livre = 0;
            tabuleiro[l][c].bomba = 0;
            tabuleiro[l][c].vizinhos = 0;
        }
    }
}

void jogabomba(int n){
    int i;
    srand(time(NULL));
    for(i = 1; i <= n; i++){
        //Essas variáveis geram valores aleatórios, nos quais as bombas serão colocadas.
        l = rand() % 10;
        c = rand() % 20;
        if(jogo[l][c].eBomba == 0){
            tabuleiro[l][c].bomba = 1;
        } else {
            /*Caso o algoritmo coloque duas bombas no mesmo lugar esse teste reduzirá o contador em um
              dessa forma fazendo com a bomba seja colocada em uma nova posição.*/
            i--;
        }
    }
}
void main(){
    ComeçarJogo();
    jogabomba(40);
}