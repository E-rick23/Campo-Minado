#include <stdio.h>
#include <stdlib.h>

struct Celula{
    int livre; //Se a casa está vazia ou não 0 ou 1
    int bomba; //Tem bomba ou não tem 0 ou 1
    int proximos; // 0 a 4
};

Celula tabuleiro[10][20];

int l, c;

//Função que inicializa o tabuleiro do jogo
void iniciarTabuleiro(){
    for(l = 0; l < 10; l++){
        for(c = 0; c < 20; c++){
            tabuleiro[l][c].livre = 0;
            tabuleiro[l][c].bomba = 0;
            tabuleiro[l][c].proximos = 0;
        }
    }
}

//Função que coloca bombas no campo aleatóriamente
void jogabomba(int n){
    int i;
    srand(time(NULL));
    for(i = 1; i <= n; i++){
        //Essas variáveis geram valores aleatórios, nos quais as bombas serão colocadas.
        l = rand() % 10;
        c = rand() % 20;
        if(tabuleiro[l][c].bomba == 0){
            tabuleiro[l][c].bomba = 1;
        } else {
            /*Caso o algoritmo coloque duas bombas no mesmo lugar esse teste reduzirá o contador em um
              dessa forma fazendo com a bomba seja colocada em uma nova posição.*/
            i--;
        }
    }
}

//Função que diz se um par de coordenadas é válido ou não;
int coordenadaValida(int l, int c) {
    if(l >= 0 && l < 10 && c >= 0 && c < 20)
        return 1;
    else
        return 0;
}
//Função que retorna quantas bombas estão próximas
int bombasProximas(int l, int c) {
    /*  l - 1 e c
        l + 1 e c
        l e c + 1
        l e c - 1
    */
    int ndebombas = 0;
    if (coordenadaValida(l-1, c) && tabuleiro[l-1][c].bomba)
        ndebombas++;
    if (coordenadaValida(l-1, c) && tabuleiro[l+1][c].bomba)
        ndebombas++;
    if (coordenadaValida(l-1, c) && tabuleiro[l][c+1].bomba)
        ndebombas++;
    if (coordenadaValida(l-1, c) && tabuleiro[l-1][c-1].bomba)
        ndebombas++;
    return ndebombas;
}
//Função que conta as bombas próximas
void contarBombas(){
    for(l = 0; l < 10; l++){
        for(c = 0; c < 20; c++){
            tabuleiro[l][c].proximos = bombasProximas(l, c);
        }
    }
}
void main(){
    int qdebomba = 40;
    iniciarTabuleiro();
    jogabomba(qdebomba);
    contarBombas();
}