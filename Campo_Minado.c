#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Celula{
    int livre; //Se a casa está vazia ou não 0 ou 1
    int bomba; //Tem bomba ou não tem 0 ou 1
    int proximos; // 0 a 4
};

struct Celula tabuleiro[10][20];

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

//Função que imprime o jogo
void imprimir(){
    printf("\n\n\t    ");
    for(l = 0; l < 10; l++)
        printf(" %d  ",l); //Indices das colunas
    printf("\n\t   ---------------------------------------------\n");
    for(l = 0; l < 10; l++){
        printf("\t%d  |", l); //Indices das linhas
        for(c = 0; c<20; c++){
            if(tabuleiro[l][c].livre){
                if(tabuleiro[l][c].bomba){
                    printf(" * ");
                } else {
                    printf(" %d ", tabuleiro[l][c].proximos);
                }
            } else {
                printf("   ");
            }
            printf("|");
        }
        printf("\n\t   ---------------------------------------------\n");
    }
}

//Função recursiva que abre a casa nas coordenadas que o usuário digitar
void abralapuerta(int linha, int coluna){
    if(tabuleiro[linha][coluna].livre == 0 && coordenadaValida(linha, coluna) == 1){
        tabuleiro[linha][coluna].livre = 1;
        if(tabuleiro[linha][coluna].proximos == 0){
            abralapuerta(l-1, c); //Cima
            abralapuerta(l+1, c); //Baixo
            abralapuerta(l, c+1); //Direita
            abralapuerta(l, c-1); //Esquerda
            abralapuerta(l-1, c-1); //Diagonal superior esquerda
            abralapuerta(l-1, c+1); //Diagonal superior direita
            abralapuerta(l+1, c-1); //Diagonal inferior esquerda
            abralapuerta(l+1, c+1); //Diagonal inferior direita
        }
    }
}

//Função que lê as coordenadas
void iniciarjogo(){
    int coordenadal, coordenadac;
    do{
        printf("Digite a linha e coluna: ");
        scanf("%d%d", &coordenadal, &coordenadac);
        if(coordenadaValida(coordenadal, coordenadac) == 0);
            printf("\nCoordenada Inválida!");
    } while(coordenadaValida(coordenadal, coordenadac) == 0 || tabuleiro[coordenadal][coordenadac].livre == 1);

    abralapuerta(coordenadal, coordenadac);
}
void main(){
    int qdebomba = 40;
    iniciarTabuleiro();
    jogabomba(qdebomba);
    contarBombas();
    printf("\n\t\t\tCampo Minado\n");
    imprimir();
    printf("\n");
}