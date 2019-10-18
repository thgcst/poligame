#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#define GNUPLOT "\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"  -persist"

/************************** Declarando funcoes **************************************/
void gerarPolinomio(int grau);  //gera coeficientes randomicos
void gerarFase(int fase);
int retorno(int x, int grau); //retorna f(x)
void compare(int grau); //compara vetor coeficiente e vetor coef_chutes
void cadastro(void); // Função que cria o arquivo pessoal do usuário e armazena a fase atual
void coordenadas(int u, int v); //Guarda as coordenadas usadas pelo usuario
void grafico(void); //Gera o grafico
void introducao(void); // Mostra as instrucoes do jogo
void titulo(void); // Printa o titulo POLIGAME
void pontuar(void); // Soma a pontuacao da fase atual na pontuacao geral do jogo

/*************************** Variaveis globais ***************************************/

int coeficientes[11] = {0}; //polinomio grau no maximo 10
int coef_chutes[11] = {0};  //vetor que guarda os coeficientes chutados
int trigger = 0, fase = 1;
int erros = 0; // Conta quantas vezes o jogador ja errou
int pistas = 0; // Conta quantos f(x) o jogador pediu do jogo
int pontuacaoGeral = 0; // Pontuacao do jogador no jogo inteiro
int pontuacaoDaFase = 0; // Pontuacao do jogador na fase atual
int vidasExtras = 0; // Armazena quantas vidas extras ainda restam
char opcao = 'r';  // variavel auxiliar
char dificuldade = 'j'; // Dificuldade: facil ou dificil
char nome[50] = "", arq_coord[50] = "", nome_vidasextras[50] = ""; //nome pra cadastro do usuario
FILE *file;  //ponteiro pro arquivo que contem as fases
FILE *coord; //ponteiro pro arquivo que contem as coordenadas
FILE *arq_vidasExtras; //ponteiro pro arquivo que contem o numero de vidas extras



/**************************************************************************************/

int main() {

    titulo();

    cadastro(); // Função que cria o arquivo pessoal do usuário e armazena a fase atual.

    if(fase == 1){
        introducao();
    }

    if(opcao == 'r'){
        while(dificuldade != 'f' & dificuldade != 'd'){
            printf("\nVoce deseja jogar no modo Facil ou Dificil? (f/d): ");
            scanf(" %c", &dificuldade);
            printf("\n\n");
        }
    }


    while (trigger == 0){


        file = fopen(nome, "w"); // Abre o arquivo no modo Write, porque agora o usuário vai começar a jogar e o arquivo precisa ser atualizado.
        fprintf(file, "%d\n%d", fase, pontuacaoGeral);  // Escreve no arquivo a fase que o usuário acabou de entrar.
        fclose(file); // Salva e fecha o arquivo.

        arq_vidasExtras = fopen(nome_vidasextras, "r"); // Abre o arquivo de vidas extras no modo read e armazena na variavel vidasExtra.
        fscanf(arq_vidasExtras, "%d", &vidasExtras);
        fclose(arq_vidasExtras); // Salva e fecha o arquivo.

        coord = fopen(arq_coord, "w");
        fprintf(coord, "\n");
        fclose(coord);

        srand((unsigned int)time(NULL)); // semente pros numeros aleatorios
        gerarFase(fase);

    }


    file = fopen(nome, "w"); // Abre o arquivo no modo Write.
    fprintf(file, "1"); // Caso o usuário perca o jogo, salva "1" como fase atual para quando o usuário tornar a jogar, estar na primeira fase.
    fclose(file); // Salva e fecha o arquivo.

    return 0;

}

/************* Printa o Titulo*****************/

void titulo(){

    printf("**********    *********    ***          ***    *********    *********    ****       ****    *********\n");
    Beep(600, 10);
    Sleep(100);
    printf("**********    *********    ***          ***    *********    *********    *****     *****    *********\n");
    Beep(600, 10);
    Sleep(100);
    printf("***    ***    ***   ***    ***          ***    ***          ***   ***    ******   ******    ***\n");
    Beep(600, 10);
    Sleep(100);
    printf("***    ***    ***   ***    ***          ***    ***          ***   ***    *** *** *** ***    ***\n");
    Beep(600, 10);
    Sleep(100);
    printf("**********    ***   ***    ***          ***    ***          ***   ***    ***  *****  ***    ******\n");
    Beep(600, 10);
    Sleep(100);
    printf("**********    ***   ***    ***          ***    ***   ****   *********    ***   ***   ***    ******\n");
    Beep(600, 10);
    Sleep(100);
    printf("***           ***   ***    ***          ***    ***   ****   *********    ***    *    ***    ***\n");
    Beep(600, 10);
    Sleep(100);
    printf("***           ***   ***    ***          ***    ***   ***    ***   ***    ***         ***    ***\n");
    Beep(600, 10);
    Sleep(100);
    printf("***           *********    *********    ***    *********    ***   ***    ***         ***    *********\n");
    Beep(600, 10);
    Sleep(100);
    printf("***           *********    *********    ***    *********    ***   ***    ***         ***    *********\n\n\n");
    Beep(600, 10);
    Sleep(1000);
    Beep(600,10);
}



/****************** Gera um arquivo que guarda as coordenadas ****************************/

void coordenadas(int u, int v){

    coord = fopen(arq_coord, "a");
    fprintf(coord, "%d  %d\n", u, v);
    fclose(coord);
}



/****************************** Introduz e da as regras do jogo *************************/

void introducao(){

    char intro = 'p';
    while( intro != 's' & intro != 'n'){
        printf("\nDeseja ver as instrucoes do jogo?(s/n): ");
        scanf(" %c", &intro);
    }

    if(intro ==  's'){
        printf("\n\n\n - Ola! Seja bem vindo ao POLIGAME, um jogo pra voce testar suas habilidades logico-matematicas!");
        Sleep(4500);
        printf("\n\n - O objetivo desse jogo eh que o jogador tente adivinhar quais sao os coeficientes de um\n   polinomio gerado aleatoriamente pelo computador.");
        Sleep(6000);
        printf("\n\n - Voce deve estar perguntando como vai fazer isso. Entao, na verdade eh simples, voce deve\n   simplesmente inserir valores de x que o jogo te dira quanto vale o f(x), de forma que voce consiga\n   descobrir o valor dos coeficientes fazendo algumas continhas.");
        Sleep(10000);
        printf("\n\n - Voce comeca na primeira fase com um polinomio de grau 1, e a cada fase que sobe, o grau do polinomio tambem sobe.");
        Sleep(6000);
        printf("\n\n - Ha dois niveis de dificuldade: \n     Facil: voce tem direito a 3 vidas extras\n     Dificil: voce tem direito a 1 vida extra");
        Sleep(6000);
        printf("\n\n - Fique atento, quanto mais valores de 'x' voce utilizar pra descobrir os coeficientes, menor sera sua pontuacao");
        Sleep(4500);
        printf("\n\n - No final de cada fase o jogo fara uma interpolacao de um polinomio usando os pontos que voce utilizou na fase\n   pra voce observar se os coeficientes do polinomio interpolador foram parecidos com os originais.");
        Sleep(8000);
        printf("\n\n - dica: os coeficientes vao de -10 ate 10 e o grau do polinomio eh no maximo 10.");
        Sleep(6000);
        printf("\n\n - E ai, entendeu? Entao vamos la!\n\n");
        Sleep(6000);
    }


}



/************************************* Cadastro ****************************************/

void cadastro(){ // Função que cria o arquivo pessoal do usuário e armazena a fase atual.

    printf("Insira seu nome: ");
    scanf(" %s", nome);   // Recebe o nome do usuário
    strcpy(arq_coord, nome); //pra usar o arq_coord na funcao coordenadas
    strcpy(nome_vidasextras, nome);


    strcat(arq_coord, "(coordenadas).txt");
    strcat(nome_vidasextras, "(vidasExtras).txt");
    strcat(nome, ".txt"); // Concatena ".txt" depois do nome do usuário

    file = fopen(nome, "r");   // Abre o arquivo "nome.txt" no modo Read

    if(file == NULL){     // Se o arquivo "nome.txt" não existe
        fclose(file);    // Botei isso pra fechar só por segurança, pra evitar erros.
        file = fopen(nome, "w");   // Cria o arquivo "nome.txt" no modo Write.
        arq_vidasExtras = fopen(nome_vidasextras, "w"); // Cria o arquivo "nome (vidasExtras).txt" no modo Write.
    }
    else{    // Se o arquivo "nome.txt" já existe (ou seja, o usuário já jogou anteriormente)


        fscanf(file, "%d\n%d", &fase, &pontuacaoGeral);   // Pega o inteiro armazenado no arquivo principal e armazena na variável fase, e armazena tambem a pontuacao
        fscanf(arq_vidasExtras, "%d", &vidasExtras); // Pega o inteiro armazenado no arquivo das vidas extras e armazena na variavel do programa.

//        while(opcao != 'c' && opcao != 'r'){   // Esse while é só pra rodar enquanto o usuário não entrar com "c" e nem com "r"
//
//            printf("\nVoce parou na fase %d, deseja continuar(c) ou reiniciar(r) o progresso? ", fase);  // Mostra a fase que o usuário parou na ultima vez e pergunta se ele quer continuar de onde parou
//            scanf(" %c", &opcao); // recebe a resposta do usuário
//        }

        do{
            printf("\nVoce parou na fase %d, deseja continuar(c) ou reiniciar(r) o progresso? ", fase);  // Mostra a fase que o usuário parou na ultima vez e pergunta se ele quer continuar de onde parou
            scanf(" %c", &opcao); // recebe a resposta do usuário
        }while(opcao != 'c' && opcao != 'r');


        if( opcao == 'r'){ // Se o usuário escolher reiniciar, a fase volta a ser 1. Se escolher continuar, fase continua igual.
            fase = 1;
            pontuacaoGeral = 0;
        }

    }

    fclose(file); // Salva e fecha o arquivo.

}



/******************** Essa função gera os coeficientes dos polinomio *******************/

void gerarPolinomio(int grau){


    int i;

    for(i=0 ; i < grau+1 ; i++){
        if(i == 0){
            while(coeficientes[0] == 0){
                coeficientes[i] = (rand() % 21) - 10;
            }
        }

        else{
        coeficientes[i] = (rand() % 21) - 10;
        }
    }
}



/************************** Essa funcao gera as fases do jogo ****************************/

void gerarFase(int fase){


    int x;
    char continuar = 'a';  //trigger pra sair do loop dentro de um polinomio

    if(dificuldade == 'f'){
        vidasExtras = 3 - erros;
    }
    else if(dificuldade == 'd'){
        vidasExtras = 1 - erros;
    }

    arq_vidasExtras = fopen(nome_vidasextras, "w"); // Abre o arquivo no modo Write, para armazenar no arquivo o numero de vidas extras que lhe restam
    fprintf(arq_vidasExtras, "%d", vidasExtras);
    fclose(arq_vidasExtras); // Salva e fecha o arquivo.

    printf("\n%d fase (funcao de grau %d)  --  Vidas Extras: %d  --  Pontuacao: %d\n", fase, fase, vidasExtras, pontuacaoGeral);

    gerarPolinomio(fase);  //chama a funcao gerar polinomio de grau "fase"

    while(continuar != 's'){

        printf("\nInsira x: ");
        scanf("%d", &x);

        printf("f(%d) = %d\n", x, retorno(x, fase)); //retorna o f(x)
        coordenadas(x, retorno(x, fase));
        pistas++; // Acrescenta 1 no contador de pistas.

        printf("\nDeseja adivinhar o polinomio?(s/n): ");
        scanf(" %c", &continuar);


        while ( continuar != 's' && continuar != 'n'){
            printf("\n\nPor favor selecione s ou n.\nDeseja adivinhar o polinomio? :\n");
            scanf(" %c", &continuar);
        }
        printf("\n");
    }

    compare(fase);


}



/************************ Essa funcao retorna os valores de y do polinomio******************/

int retorno(int x, int grau){
    int i, retorno = 0;

    for(i = 0; i <= grau; i++){
        retorno += coeficientes[i]*pow(x,grau - i); // Preenche o polinomio do maior pro menor grau.
    }

    return retorno;
}



/*********************** Essa funcao compara o polinomio e o chute **************************/

void  compare(int grau){

    int i, coef, contador = 0;
    int *p, *q;

    printf("Insira os coeficientes do polinomio do termo de maior grau pro de menor grau:\n"); //
    for (i=0; i < grau + 1; i++){
        scanf("%d", &coef);
        coef_chutes[i] = coef;
    }

    p = &coeficientes[0]; //p aponta pro endereco de memoria da primeira posicao do vetor dos coeficientes
    q = &coef_chutes[0];  //q aponta pro endereco de memoria da primeira posicao do vetor dos coeficientes chutados pelo usuario

    for(i=0; i < grau+1; i++){
        if (*p == *q){
            contador++;
            p++;
            q++;
        }
    }


    if (contador == grau+1){ // Acertou todos os coeficientes do polinÙmio

        pontuar(); // Se o jogador passar de fase ele pontua

        fase++;

        file = fopen(nome, "w"); // Abre o arquivo no modo Write, porque agora o usuário vai começar a jogar e o arquivo precisa ser atualizado.
        fprintf(file, "%d\n%d", fase, pontuacaoGeral);  // Escreve no arquivo a fase que o usuário acabou de entrar.
        fclose(file); // Salva e fecha o arquivo.

        fase--;

        printf("\n\nVoce acertou! +%d Pontos\n\n", pontuacaoDaFase);

        Sleep(2000);
        printf("Vamos analisar o grafico plotado a partir das coordendadas que voce usou, interpolando por uma funcao de grau %d", fase);
        Sleep(4000);
        grafico();
        Sleep(10000);

        printf("\n\nVamos pra proxima fase\n\n");

        fase++;

    }


    else { // Errou pelo menos um dos coeficientes do polinomio

        arq_vidasExtras = fopen(nome_vidasextras, "w"); // Abre o arquivo no modo Write, porque agora o usuário vai começar a jogar e o arquivo precisa ser atualizado.
        fprintf(arq_vidasExtras, "%d", vidasExtras);  // Escreve no arquivo a fase que o usuário acabou de entrar.
        fclose(arq_vidasExtras); // Salva e fecha o arquivo.

        erros++;
        
        printf("\n\nVoce errou :(\n\n");
        
        printf("O polinomio era:\n"); // Mostra o polinomio
        for(i=0; i < grau + 1; i++){
            printf("+%dx^%d", coeficientes[i], grau - i);
        }
        
        Sleep(2000);
        printf("\n\nVamos ver como era o grafico da funcao interpolando por uma funcao de grau %d\n\n", fase);
        Sleep(4000);
        grafico();
        Sleep(10000);

    }

    if((dificuldade == 'f' & erros == 4) | (dificuldade == 'd' & erros == 2)){

        trigger = 1; //Isso faz o while do main parar.
    }


    printf("\n\n");
}



/**************************Gera o grafico baseado nas coordenadas*******************************/

void grafico (){

    char  l1[50] = "plot '";  //primeira a linha a ser printada no GNUPLOT
    strcat(l1, arq_coord);
    strcat(l1, "' using 1:2\n"); //plot 'nome(coordendas).txt' using 1:2

    char l2[50] = "f(x) = ";//segunda a linha a ser printada no GNUPLOT

    char l3[50] = "fit f(x) '";//terceira a linha a ser printada no GNUPLOT
    strcat(l3, arq_coord);

    char l4[100] = "plot f(x) title 'ajuste', '";//quarta a linha a ser printada no GNUPLOT
    strcat(l4, arq_coord);
    strcat(l4, "' title 'pares chutados' linetype 7 linecolor -1\n");// plot f(x) title 'ajuste', 'nome(coordenadas).txt' title 'pares chutados'

    switch (fase){
        case 1: //caso fase 1 interpola polinomio de grau 1
            strcat(l2, "a*x + b\n");
            strcat(l3, "' via a,b\n");
            break;

        case 2:// caso fase 2 interpola polinomio de grau 2
            strcat(l2, "a*x**2 + b*x +c\n");
            strcat(l3, "' via a,b,c\n");
            break;

        case 3:// caso fase 3 interpola polinomio de grau 3
            strcat(l2, "a*x**3 + b*x**2 + c*x + d\n");
            strcat(l3, "' via a,b,c,d\n");
            break;

        case 4://caso fase 4 interpola polinomio de grau 4
            strcat(l2, "a*x**4 + b*x**3 + c*x**2 + d*x + e\n");
            strcat(l3, "' via a,b,c,d,e\n");
            break;

        case 5://case fase 5 interpola polinomio de grau 5
            strcat(l2, "a*x**5 + b*x**4 + c*x**3 + d*x**2 + e*x + f\n");
            strcat(l3, "' via a,b,c,d,e,f\n");
            break;

        case 6: //case fase 6 interpola polinomio de grau 6
            strcat(l2, "a*x**6 + b*x**5 + c*x**4 + d*x**3 + e*x**2 + f*x + g\n");
            strcat(l3, "' via a,b,c,d,e,f,g\n");
            break;

        case 7: //case fase 7 interpola polinomio de grau 7
            strcat(l2, "a*x**7 + b*x**6 + c*x**5 + d*x**4 + e*x**3 + f*x**2 + g*x + h\n");
            strcat(l3,"' via a,b,c,d,e,f,g,h\n");
            break;

        case 8: //case fase 8 interpola polinomio de grau 8
            strcat(l2, "a*x**8 + b*x**7 + c*x**6 + d*x**5 + e*x**4 + f*x**3 + g*x**2 + h*x + i\n");
            strcat(l3, "' via a,b,c,d,e,f,g,h,i\n");
            break;

        case 9:// case 9 interpola polinomio de grau 9
            strcat(l2, "a*x**9 + b*x**8 + c*x**7 + d*x**6 + e*x**5 + f*x**4 + g*x**3 + h*x**2 + i*x + j\n");
            strcat(l3, "' via a,b,c,d,e,f,g,h,i,j\n");
            break;

        default://case fase >=10 interpola polinomio de grau 10
            strcat(l2, "a*x**10 + b*x**9 + c*x**8 + d*x**7 + e*x**6 + f*x**5 + g*x**4 + h*x**3 + i*x**2 + j*x + k\n");
            strcat(l3, "' via a,b,c,d,e,f,g,h,i,j,k\n");
            break;
    }

    FILE *gp; //ponteiro pro gnuplot
    gp = popen(GNUPLOT, "w"); //funçao abre um PIPE pra se comunicar com o GNUPLOT e trata ele como se fosse um arquivo
    if (gp == NULL) {
        printf("Erro ao abrir pipe para o GNU plot");
    }
    fprintf(gp, "set xlabel 'eixo x'\n");
    fprintf(gp, "set ylabel 'eixo y'\n");
    fprintf(gp, l1); // plot 'nome(coordendads).txt' using 1:2
    fprintf(gp, l2); // f(x) = (polinomio de algum grau)
    fprintf(gp, l3); // fit f(x) 'nome(coordendas).txt' via a,b,c....
    fprintf(gp, l4); // plot f(x) title 'ajuste', 'nome(coordendads).txt title 'pares chutados' linetype 7 linecolor -1 (bolas pretas)
    fclose(gp);

}



/************************** Manipula a pontuacao atual do usuario *******************************/

void pontuar(){ // A pontuacao se baseia em: pontuacao = 10 - (numero de chutes - (grau do polinomio + 1))
    if(pistas - (fase + 1) <= 0){
            pontuacaoDaFase = 10;
        }
    else if((pistas - (fase+1)) >= 10){
            pontuacaoDaFase = 0;
        }
    else{
            pontuacaoDaFase = 11 - pistas + fase;
        }

    pistas = 0;

    pontuacaoGeral += pontuacaoDaFase;
}


