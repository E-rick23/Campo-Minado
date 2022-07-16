#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Celula{
    int casaLivre;
    int temMina;
    int proximo;
};

struct Celula tabuleiro[10][20];
int coluna;
int linha;

//Função pra inicializar o tabuleiro do jogo
void iniciarTabuleiro(){
    for(linha = 0; linha < 10; linha++){
        for(coluna = 0; coluna < 20; coluna++){
            tabuleiro[linha][coluna].temMina = 0;
            tabuleiro[linha][coluna].casaLivre = 0;
            tabuleiro[linha][coluna].proximo = 0;
        }
    }
}

//Função para sortear as minas no tabuleiro
void sortearMinas(int n){
    int minas = 0;
    srand(time(NULL));
    for(int i = 1; i <= n; i++){
        linha = rand() % 10;
        coluna = rand() % 20;
        if(tabuleiro[linha][coluna].temMina == 0){
            tabuleiro[linha][coluna].temMina = 1;
            minas++;
        }
        else
            i--;
    }
}

//Função para definir se uma coordenada é válida ou não
int casaValida(int l, int c){
    if(l >= 0 && l < 10 && c >= 0 && c < 20)
        return 1;
    else
        return 0;
}

//Função que retorna a quantidade de minas próximas
int quantMinasVizinhas(int l, int c){
    int ndeMinas = 0;
    //Condicionais que encontram as minas próximas
    if(tabuleiro[l-1][c].temMina && casaValida(l - 1, c))
        ndeMinas++;
    if(tabuleiro[l+1][c].temMina && casaValida(l + 1, c))
        ndeMinas++;
    if(tabuleiro[l][c+1].temMina && casaValida(l, c + 1))
        ndeMinas++;
    if(tabuleiro[l][c-1].temMina && casaValida(l, c - 1))
        ndeMinas++;
    return ndeMinas;
}

// Função que conta as minas próximas
void contarMinas(){
    for(linha = 0; linha < 10; linha++){
        for(coluna = 0; coluna < 20; coluna++)
            tabuleiro[linha][coluna].proximo = quantMinasVizinhas(linha, coluna);
    }
}

// Função que imprime o jogo
void exibirJogo(){

    printf("\n\n\t    ");
    // Loop que imprime os índices das colunas
    for(coluna = 0; coluna < 20; coluna++){
        //Condicionais para espaçamento dos números
        if (coluna<8){
            printf(" %d  ", coluna+1); 
        }
        if (coluna >= 8){
            printf(" %d ", coluna+1);
        }
    }
    printf("\n\t   ---------------------------------------------------------------------------------\n");
    // Loop que imprime os índices das linhas
    for(linha = 0; linha < 10; linha++){
        //Condicionais para espaçamento dos números
        if (linha < 9){
            printf("\t%d  |", linha+1); 
        }
        if(linha == 9){
            printf("\t%d |", linha+1); 
        }
        for(coluna = 0; coluna < 20; coluna++){
            if(tabuleiro[linha][coluna].casaLivre){
                if(tabuleiro[linha][coluna].temMina)
                    printf(" * ");
                else
                    printf(" %d ", tabuleiro[linha][coluna].proximo);
            }
            else
                printf("   ");
            printf("|");
        }
        printf("\n\t   ---------------------------------------------------------------------------------\n");
    }
}


//Função que abre a célula na coordenada que o usuário digitou
void abrirCelula(int l, int c){
    if(tabuleiro[l][c].casaLivre == 0 && casaValida(l, c) == 1){
        tabuleiro[l][c].casaLivre = 1;
        //Caso as casas próximas estejam fechadas e não hajam minas próximas, o jogo também abrirá as casas adjacentes
        if(tabuleiro[l][c].proximo == 0){
            abrirCelula(l-1, c); //Casa acima
            abrirCelula(l+1, c); //Casa abaixo
            abrirCelula(l, c+1); //Casa a direita
            abrirCelula(l, c-1); //Casa a esquerda
        }
    }
}

//Função que verifica se o usuário venceu
int ganhou(){
    int tudoAberto = 0;
    for(linha = 0; linha < 10; linha++){
        for(coluna = 0; coluna < 20; coluna++){
            //Para que o usuário vença, devem haver zero minas abertas e zero casas sobrando.
            if(tabuleiro[linha][coluna].temMina == 0 && tabuleiro[linha][coluna].casaLivre == 0)
                tudoAberto++;
        }
    }
    return tudoAberto;
}

// Função que faz a leitura das coordenadas
void jogo(){
    int coordenadal, coordenadac;
    do{
        exibirJogo();
        do{
            printf("\nDigite a linha e coluna: ");
            scanf("%d%d", &coordenadal, &coordenadac);
            coordenadal = coordenadal-1;
            coordenadac = coordenadac-1;
            if(tabuleiro[coordenadal][coordenadac].casaLivre == 1 || casaValida(coordenadal, coordenadac) == 0){
                printf("\nCasa já aberta ou inválida!");
            }
                
        }while(tabuleiro[coordenadal][coordenadac].casaLivre == 1 || casaValida(coordenadal, coordenadac) == 0);

        abrirCelula(coordenadal, coordenadac);
    }while(tabuleiro[coordenadal][coordenadac].temMina == 0 && ganhou() != 0);

    if(tabuleiro[coordenadal][coordenadac].temMina == 1)
        printf("\n\tVocê virou churrasco\n");
    else
        printf("\n\tVocê venceu!\n");

    exibirJogo();
}

int main() {
    int ndeminas = 40, continuar;
    do{
        iniciarTabuleiro();
        sortearMinas(ndeminas);
        contarMinas();
        printf("\n\t\t\t\t\t   Campo Minado\n");
        jogo();
        printf("\nDigite 1 para recomeçar: ");
        scanf("%d", &continuar);
    }while(continuar == 1);

    return 0;
}