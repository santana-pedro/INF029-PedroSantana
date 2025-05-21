#include <stdio.h>
#include <string.h>
#define TRUE -1
#define FALSE -2

typedef struct Velha{
    int preenchido; //0 e 1
    char tipo; //X e O
}Velha;
Velha velha[3][3];

void zerarTabuleiro(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            velha[j][i].preenchido = 0;
        }
    }
} 

int verificarTabuleiroJogada(int letra, int num){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(j == letra && i == num){
                if(velha[j][i].preenchido == 1){
                    return FALSE;
                }
                else if(velha[j][i].preenchido == 0){
                    return TRUE;
                }
            }
        }
    }
}

int verificarTabuleiroResultado(char tipo){
    //HORIZONTAL
    //VERTICAL
    //DIAGONAL
}

int main(){
    zerarTabuleiro();
    int letra, num;
    char celulaInteresse[2];

    //JOGADA X
    printf("Jogador X, informe a célula de interesse (Ex: A3): ");
    fgets(celulaInteresse, 2, stdin);
    celulaInteresse[strcspn(celulaInteresse, "\n")] = '\0';
    if(celulaInteresse[0] >= 97 && celulaInteresse[0] <= 122){
        celulaInteresse[0] -= 32;
    }
    letra = celulaInteresse[0] - 65;
    num = celulaInteresse[1] - 49;
    if(verificarTabuleiroJogada(letra, num) == TRUE){
        velha[letra][num].preenchido = 1;
        velha[letra][num].tipo = 'O';
    }

    //JOGADA O
    printf("Jogador O, informe a célula de interesse (Ex: A3): ");
    fgets(celulaInteresse, 2, stdin);
    celulaInteresse[strcspn(celulaInteresse, "\n")] = '\0';
    if(celulaInteresse[0] >= 97 && celulaInteresse[0] <= 122){
        celulaInteresse[0] -= 32;
    }
    letra = celulaInteresse[0] - 65;
    num = celulaInteresse[1] - 49;
    if(verificarTabuleiroJogada(letra, num) == TRUE){
        velha[letra][num].preenchido = 1;
        velha[letra][num].tipo = 'O';
    }
    
    return 0;
}