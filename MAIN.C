#include<stdio.h>
#include "utypes.h"
#include "VTEXTO.h"
#include <go32.h> 
#include <sys/farptr.h>
#include<stdlib.h>
#include<locale.h>
Byte const core[] = {BLUE_FOREG,GREEN_FOREG,RED_FOREG};
Byte const back[] ={BLUE_BACK,GREEN_BACK,RED_BACK};
Byte const FOREGROUND_COLORS[] = {BLUE_FOREG, GREEN_FOREG, RED_FOREG};
Byte const BACKGROUND_COLORS[] = {BLUE_BACK, GREEN_BACK, RED_BACK};
char const *cores[] = {"Azul", "Verde", "Vermelho"};
void menu();
void frame();
void print_caracter();
void print_numero();
void print_string();
int *escolha_posicao();
Byte escolha_cor_fundo();
Byte escolha_cor_letra();
int read_string(char *str, int tam);

int main(void){
 menu();
  return 0;
}

void print_caracter(){
    char ch[2];
    Byte cor_letra, cor_fundo;
    int *posicao;
    int i;

    printf("\n");
    printf("**********************************\n");
    printf("\tINSIRA O CARATERE       \n");
    printf("**********************************\n");
    printf("Caratere: "); scanf("%s", ch);

    printf("\n");

    cor_letra = escolha_cor_letra();

    printf("\n");
    cor_fundo = escolha_cor_fundo();

    printf("\n");
    posicao = escolha_posicao();

    system("cls");
    if( !printCharAt(ch[0], posicao[0] - 1, posicao[1] - 1, (cor_letra | cor_fundo) )) {
        printf("Error: Ocorreu um erro na especificacao.Tente de novo!");
    }

    if( posicao[1] < HEIGHT )
        for(i = 0; i < HEIGHT - 1; ++i) {
            printf("\n");
        }

    printf("Press<ENTER TO OUT>\n");
	getchar();
    getchar();

    free(posicao);
 }
void frame(){
    char str[100];
    Byte cor_letra, cor_fundo;
    int *posicao;
    int width;
    int height;
	int i;

    printf("\n**********************************\n");
    printf("\tINSIRA O TITULO        \n");
    printf("**********************************\n");
    printf("Titulo: "); read_string(str, 100);

    printf("\n");

    cor_letra = escolha_cor_letra();

    printf("\n");
    cor_fundo = escolha_cor_fundo();

    printf("\n");
    posicao = escolha_posicao();

    printf("\n");
    printf("**********************************\n");
    printf("\tDIMENSAO DO FRAME   \n");
    printf("**********************************\n");
    printf("WIdth: "); scanf("%d", &width);
    printf("Height: "); scanf("%d", &height);

    printf("%s", str);
    system("cls");
    if( !drawFrame(str, (cor_letra | cor_fundo), posicao[0] - 1, posicao[1]-1, width, height )) {
        printf("\nError: Ocorreu um erro na especificacao\n Volte a tentar!");
    }
    if( posicao[1] < HEIGHT )
        for(i = 0; i < HEIGHT - 1; ++i) {
            printf("\n");
        }
    printf("Press<ENTER TO OUT>\n");
    getchar();
    getchar();

    free(posicao);
}

int read_string(char *str, int tam)
{
    getchar();

    fgets(str, tam, stdin);

    int lenght = 0;

    while(str[lenght]) {
        if(str[lenght+ 1] == '\0')
            str[lenght] = '\0';
        else
            ++lenght;
    }
    return lenght;
}

Byte escolha_cor_letra() {
    int escolha;
    int opcao;
    Byte piscar;
    Byte intensidade;
    int i;

    printf("**********************************\n");
    printf("\tCOR DO CARATERE   \n");
    printf("**********************************\n");

    for(i = 0; i < TAM_COLORS; ++i) {
        printf(">%d. %-27s >\n", i+1, cores[i]);
    }

    printf("**********************************\n");
    printf("Escolha: "); scanf("%d", &escolha);

    if(escolha < 1 && escolha > 4) {
        printf("\nError: A opcao escolhida eh invalida.Tenta de novo!\n\n");

        return escolha_cor_letra();
    }

    printf("\n");
    printf("**********************************\n");
    printf("\tINTESIDADE DA COR DA LETRA   \n");
    printf("**********************************\n");
    printf("\t\t 1. Clara                       \n");
    printf("\t\t 2. Escura                      \n");
    printf("**********************************\n");
    printf("Escolha: "); scanf("%d",&opcao);

    while( opcao < 1 && opcao > 2 ) {
        printf("Error: Opcao invalida\n");
        printf("Escolha: "); scanf("%d",&opcao);
    }

    if( opcao == 1 )
        intensidade = STRONG;
    else
        intensidade = 0;

    printf("\n");
    printf("**********************************\n");
    printf("\tTIPO DA COR\n");
    printf("**********************************\n");
    printf("\t\t 1. Brilho\n");
    printf("\t\t 2. Sem Brilho\n");
    printf("**********************************\n");
    printf("Escolha: "); scanf("%d", &opcao);

    while( opcao < 1 && opcao > 2 ) {
        printf("Error: Opcao invalida\n");
        printf("Escolha: "); scanf("%d",&opcao);
    }

    if(opcao == 1)
        piscar = BLINK;
    else
        piscar = 0;

    return (FOREGROUND_COLORS[escolha - 1] | intensidade | piscar);
}

Byte escolha_cor_fundo() {
    int escolha;
	int i;

    printf("**********************************\n");
    printf("\tECOLHA A COR DO FUNDO     \n");
    printf("**********************************\n");
   
    for(i = 0; i < TAM_COLORS; ++i) {
        printf("> %d. %-27s >\n", i+1, cores[i]);
    }

    printf("**********************************\n");
    printf("Escolha: "); scanf("%d", &escolha);

    if(escolha < 1 && escolha > 4) {
        printf("\nA opcao invalida. Tente de novo.\n\n");

        return escolha_cor_fundo();
    }

    return BACKGROUND_COLORS[escolha - 1];
}

int *escolha_posicao() {
    int *posicao =  (int *) calloc(2, sizeof(int));

    printf("**********************************\n");
    printf("\tINSIRA A POSICAO DA TELA     \n");
    printf("**********************************\n");
    printf("X: "); scanf("%d", &posicao[0]);
    printf("Y: "); scanf("%d", &posicao[1]);

    return posicao;
}
void menu(){
        int escolha;
        do{
		system("cls");
		printf("**********************************\n");
                printf("              **MENU**             \n");
		printf("**********************************\n");
                printf("\t 1. Print Caratere\n");
                printf("\t 2. Print String\n");
                printf("\t 3. Print Numero\n");
                printf("\t 4. Draw Frame\n");
                printf("\t 0. OUT\n");
		printf("**********************************\n");
                printf("\t Escolha: "); scanf("%d", &escolha);

        switch(escolha) {
            case 1:
                 print_caracter();
                break;
            case 2:
                print_string();
                break;
            case 3:
                print_numero();
                break;
            case 4:
                frame();
                break;
            case 0:
                {
                    char ch[2];

                    system("cls");
                    printf("\ntem certeza que quer sair? [S/N]: ");
                    scanf("%s", ch);

                    if(ch[0] == 'S' || ch[0] == 's') {
                        printf("\nEnded...\n");
                        exit(0);
                    }
                }
                break;
            default:
                fprintf(stderr,"\nError: Ocorreu um erro na especificacao. Tente de novo\n");
                exit(0);
        }
    }
    while(true);
}

void print_string()
{
    char str[100];
    Byte cor_letra, cor_fundo;
    int *posicao;
    int i;

    printf("\n");
    printf("*********************************\n");
    printf("\tINSIRA A STRING\n");
    printf("**********************************\n");
    printf("String: "); read_string(str, 100);

    printf("\n");

    cor_letra = escolha_cor_letra();

    printf("\n");
    cor_fundo = escolha_cor_fundo();

    printf("\n");
    posicao = escolha_posicao();

    printf("%s", str);

    system("cls");
    if( !printStringAt(str, posicao[0] - 1, posicao[1] - 1, (cor_letra | cor_fundo) )) {
        printf("Error: Ocorreu um erro na especificacao.Tente de novo!");
    }

    if( posicao[1] < HEIGHT )
        for(i = 0; i < HEIGHT - 1; ++i) {
            printf("\n");
        }

    printf("Press<ENTER TO OUT>\n");
    getchar();
    getchar();

    free(posicao);
}
void print_numero(){
    int num;
    Byte cor_letra, cor_fundo;
    int *posicao;
	int i;

    printf("\n");
    printf("**********************************\n");
    printf("\tINSIRA O NUMERO\n");
    printf("**********************************\n");
    printf("Numero: "); scanf("%d", &num);

    printf("\n");

    cor_letra = escolha_cor_letra();

    printf("\n");
    cor_fundo = escolha_cor_fundo();

    printf("\n");
    posicao = escolha_posicao();

    system("cls");
    if( !printIntAt(num, posicao[0] - 1, posicao[1] - 1, (cor_letra | cor_fundo) )) {
        printf("Error: Ocorreu erro na especificacao. Tente de novo!");
    }

    if( posicao[1] < HEIGHT )
        for(i = 0; i < HEIGHT - 1; ++i) {
            printf("\n");
        }

    printf("Press<ENTER TO OUT>\n");
    getchar();
    getchar();

    free(posicao);
}



