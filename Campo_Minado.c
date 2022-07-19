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
            tabuleiro[linha][coluna].casaLivre = 0;
            tabuleiro[linha][coluna].temMina = 0;
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
int quantMinasProximas(int l, int c){
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
    if(tabuleiro[l-1][c-1].temMina && casaValida(l - 1, c-1))
        ndeMinas++;
    if(tabuleiro[l+1][c-1].temMina && casaValida(l + 1, c-1))
        ndeMinas++;
    if(tabuleiro[l-1][c+1].temMina && casaValida(l - 1, c + 1))
        ndeMinas++;
    if(tabuleiro[l+1][c+1].temMina && casaValida(l + 1, c + 1))
        ndeMinas++;
    return ndeMinas;
}

// Função que conta as minas próximas
void contarMinas(){
    for(linha = 0; linha < 10; linha++){
        for(coluna = 0; coluna < 20; coluna++)
            tabuleiro[linha][coluna].proximo = quantMinasProximas(linha, coluna);
    }
}

// Função que imprime o jogo
void exibirJogo(){
    printf("\n\n\t\033[0;37m    "); //Esse printf garante que o tabuleiro será imprimido duas linhas abaixo de qualquer texto, e na cor branca.
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
                if(tabuleiro[linha][coluna].temMina){
                    printf("\033[0;31m * "); //Caso o usuário entrar na casa de uma mina, ela será imprimida em vermelho.
                    printf("\033[0;37m");
                } else {
                    //Caso haja uma mina próxima, o número 1 será imprimido em azul na casa adjacente.
                    if(tabuleiro[linha][coluna].proximo == 1){
                        printf("\033[0;34m %d ", tabuleiro[linha][coluna].proximo);
                    }
                    //Caso haja duas minas próximas, o número 2 será imprimido em ciano na casa adjacente.
                    if(tabuleiro[linha][coluna].proximo == 2){
                        printf("\033[0;36m %d ", tabuleiro[linha][coluna].proximo);
                    }
                    //Caso haja três minas próximas, o número 3 será imprimido em verde na casa adjacente.
                    if(tabuleiro[linha][coluna].proximo == 3){
                        printf("\033[0;32m %d ", tabuleiro[linha][coluna].proximo);
                    }
                    //Caso haja quatro minas próximas, o número 4 será imprimido em amarelo na casa adjacente.
                    if(tabuleiro[linha][coluna].proximo == 4){
                        printf("\033[0;33m %d ", tabuleiro[linha][coluna].proximo);
                    }
                    //Caso hajam cinco ou mais minas próximas, o respectivo número será imprimido em vermelho na casa adjacente.
                    if(tabuleiro[linha][coluna].proximo >= 5){
                        printf("\033[0;31m %d ", tabuleiro[linha][coluna].proximo);
                    }
                    //Caso não hajam minas próximas o numero 0 será imprimido em branco nas respectivas casas.
                    if(tabuleiro[linha][coluna].proximo != 1 && tabuleiro[linha][coluna].proximo != 2 && tabuleiro[linha][coluna].proximo != 3 && tabuleiro[linha][coluna].proximo != 4){
                        printf(" %d ", tabuleiro[linha][coluna].proximo);
                    }
                }
                /*O comando de alterar a cor do texto altera a cor não só do texto imprimido, mas de qualquer texto que venha após ele.
                  Portanto, ao imprimir as minas reiniciaremos a cor do texto para branco com o comando abaixo*/
                printf("\033[0;37m");
            }
            else
                printf("   ");
            printf("|");
        }
        printf("\n\t   ---------------------------------------------------------------------------------\n");
    }
    printf("\n\t   11 0 Para o cronômetro\n");
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
            abrirCelula(l-1, c-1); //Diagonal superior esquerda
            abrirCelula(l-1, c+1); //Diagonal superior direita
            abrirCelula(l+1, c-1); //Diagonal inferior esquerda
            abrirCelula(l+1, c+1); //Diagonal inferior direita
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

//imprimi o tempo de jogo
void contador(time_t sec){
   int segundos;
    //Variáveis para o contador.
    segundos = time(NULL);
    segundos = sec-segundos;
    segundos = segundos*-1;
    int horas, minutos;
    minutos = segundos/60;
    horas = minutos/60;
    segundos = segundos - (60*minutos);
    //Condicionais para a formatação do texto do contador.
    if (horas < 10 && minutos < 10 && segundos < 10){
        printf("\n\t\tTempo de jogo: 0%d:0%d:0%d ", horas, minutos, segundos);
    }
    if (horas < 10 && minutos < 10 && segundos > 10){
        printf("\n\t\tTempo de jogo: 0%d:0%d:%d ", horas, minutos, segundos);
    }
    if (horas < 10 && minutos > 10 && segundos > 10){
        printf("\n\t\tTempo de jogo: 0%d:%d:%d ", horas, minutos, segundos);
    }
    if (horas > 10 && minutos > 10 && segundos > 10){
        printf("\n\t\tTempo de jogo: %d:%d:%d ", horas, minutos, segundos);
    }
    printf("\033[0;37m"); //Após isso, o texto retornará para a cor padrão
}
// Função que faz a leitura das coordenadas
void jogo(){
    //Criando o contador de tempo.
    time_t seconds;
    int segundos;
    
    int  coordenadal, coordenadac, start = 0;
    do{
        exibirJogo();
        do{
            printf("\nDigite a linha e coluna: ");
            scanf("%d%d", &coordenadal, &coordenadac);
            if(coordenadal == 11 && coordenadac == 0 ){
                contador(seconds);
            }else{
            coordenadal = coordenadal-1;
            coordenadac = coordenadac-1;
            start ++;
            if(start == 1){
                seconds = time(NULL);
            }
            if(tabuleiro[coordenadal][coordenadac].casaLivre == 1 || casaValida(coordenadal, coordenadac) == 0){
                printf("\nCasa já aberta ou inválida!");
            }
            }
        }while(tabuleiro[coordenadal][coordenadac].casaLivre == 1 || casaValida(coordenadal, coordenadac) == 0);

        abrirCelula(coordenadal, coordenadac);
    }while(tabuleiro[coordenadal][coordenadac].temMina == 0 && ganhou() != 0);
    //Caso o jogador acerte uma mina, a mensagem de derrota será imprimida em vermelho, e o tabuleiro inteiro ficará vermelho também.
    if(tabuleiro[coordenadal][coordenadac].temMina == 1){
        srand(time(NULL)); //Gera um valor aleatório
        int msgAleatoria = rand()%10; //Faz com que o valor aleatório esteja entre 0 e 10
        //Para cada um dos valores, o jogo imprimirá uma mensagem de derrota aleatória
        switch(msgAleatoria){
            case 0 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tUm pequeno deslize e tudo foi pelos ares... Literalmente.\n");
            break;
            case 1 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tVocê virou churrasco!\n");
            break;
            case 2 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\t Ui! Você foi explodido em pedacinhos!\n");
            break;
            case 3 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tNão foi uma morte nada agradável...\n");
            break;
            case 4 : 
            printf("\033[0;31m\n\tChomp!\n");
            printf("\033[0;32m\n\tBom, não era uma mina... Mas um jacaré, e você virou janta!\n");
            break;
            case 5 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tVocê sequer teve a chance de dizer suas ultimas palavras...\n");
            break;
            case 6 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tO que é esse brilho vermelho? ... É... Talvez fosse melhor não ter descoberto...\n");
            break;
            case 7 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tVocê olhou para o céu e se perguntou se lá havia pão... E morreu!\n");
            break;
            case 8 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tTalvez você devesse ter prestado mais atenção...\n");
            break;
            case 9 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tVocê olhou para o lado por um segundo e pisou em uma mina... Doeu bastante\n");
            break;
            case 10 : 
            printf("\033[0;31m\n\tBOOM!\n");
            printf("\n\tTá pegando fogo bicho!\n");
            break;
        }
    } else {
        printf("\033[0;32m\n\tVocê venceu!\n"); //A mensagem de vitória será imprimida em ciano!
    }
    contador(seconds);
    exibirJogo();
}

int menu(){
    int opcao, end = 0, close = 0;
    do{
        printf("\n");
        printf("1 - Iniciar o jogo\n");
        printf("2 - Tutorial\n");
        printf("3 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1 :
            jogo();
            end = 1;
            break;
            case 2 :
            printf("\n");
            printf("Digite uma coordenada (Linha e coluna), depois que fizer isso, diversos números aparecerão, eles indicam a quantidade de minas próximas.\nExemplo: Caso o número 3 apareça, significa que existem 3 minas ao redor desse número, que podem estar acima, abaixo, dos lados ou nas diagonais desse número.\nDessa forma, não é uma boa opção tentar abrir um bloco que esteja ao lado de um número alto, pois a chance de explodir uma mina é consideravelmente maior.\nO jogo termina em derrota caso abra uma casa que contenha uma mina.\nVocê vence se conseguir abrir todas as casas que não contém minas.\nBoa sorte!\n");
            break;
            case 3:
            close = 1;
            end = 1;
            break;
            default:
            printf("Opção inválida!\n");
        }
    }while(end == 0);
    if (close == 1)
        return 0;
    else
        return 1;
}

void main() {
    int ndeminas = 40; //Essa variável altera a quantidade de minas no tabuleiro
    int continuar;
    do{
        iniciarTabuleiro();
        sortearMinas(ndeminas);
        contarMinas();
        printf("\n\t\t\t\t\t   Campo Minado\n");
        continuar = menu();
        if(continuar == 0)
            break;
        printf("\nDigite 1 para recomeçar: ");
        scanf("%d", &continuar);
    }while(continuar == 1);
}
