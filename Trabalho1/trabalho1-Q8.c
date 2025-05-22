#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE -1
#define FALSE -2

typedef struct Velha{
    int preenchido; //0 e 1
    char tipo; //X e O
}Velha;
Velha velha[3][3];
int totalP = 0;

void zerarTabuleiro(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            velha[j][i].preenchido = 0;
            velha[j][i].tipo = '#';
        }
    }
} 

int verificarTabuleiroJogada(int letra, int num){
    if(letra < 0 || letra > 2 || num < 0 || num > 2){
        return FALSE;
    }
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

int verificarTabuleiroResultado(char jogadorTp){
    struct Resultado{
        char tipo; //X ou O
        int venceu;
    }resultado;
    resultado.venceu = 0;
    int achouVencedor = 0;
    //HORIZONTAL
    for(int i = 0; i < 3; i++){
        if(velha[i][0].preenchido == 1){
            int iguais = 0;
            for(int j = 1; j < 3; j++){
                if(velha[i][j].preenchido == 1 && velha[i][j].tipo == velha[i][0].tipo){
                    iguais++;
                }
            }
            if(iguais == 2){
                resultado.venceu = 1;
                resultado.tipo = velha[i][0].tipo;
                break;
            }
        }
        if(resultado.venceu == 1){
            achouVencedor = 1;
            break;
        }
    }
    //VERTICAL
    for(int i = 0; i < 3; i++){
        if(velha[0][i].preenchido == 1){
            int iguais = 0;
            for(int j = 1; j < 3; j++){
                if(velha[j][i].preenchido == 1 && velha[j][i].tipo == velha[0][i].tipo){
                    iguais++;
                }
            }
            if(iguais == 2){
                resultado.venceu = 1;
                resultado.tipo = velha[0][i].tipo;
                break;
            }
        }
        if(resultado.venceu == 1){
            achouVencedor = 1;
            break;
        }
    }
    //DIAGONAL
    for(int i = 0; i < 3; i++){
        if(velha[i][i].preenchido == 1){
            int iguais = 0;
            for(int j = i + 1; j < 3; j++){
                if(velha[j][j].preenchido == 1 && velha[j][j].tipo == velha[i][i].tipo){
                    iguais++;
                }
            }
            if(iguais == 2){
                resultado.venceu = 1;
                resultado.tipo = velha[i][i].tipo;
                achouVencedor = 1;
            }
            break;
        }
    }
    for(int i = 2; i >= 0; i--){
        if(velha[i][i].preenchido == 1){
            int iguais = 0;
            for(int j = i - 1; j >= 0; j--){
                if(velha[j][j].preenchido == 1 && velha[j][j].tipo == velha[i][i].tipo){
                    iguais++;
                }
            }
            if(iguais == 2){
                resultado.venceu = 1;
                resultado.tipo = velha[i][i].tipo;
                achouVencedor = 1;
            }
            break;
        }
    }
    if(achouVencedor == 1)
        return 1;
    else 
        return 0;
}

void jogadaX(){
    int letra, num;
    char celulaInteresse[10];
    printf("Jogador X, informe a célula de interesse (Ex: A3): ");
    fgets(celulaInteresse, 10, stdin);
    if(celulaInteresse[0] >= 97 && celulaInteresse[0] <= 122){
        celulaInteresse[0] -= 32;
    }
    letra = celulaInteresse[0] - 65;
    num = celulaInteresse[1] - 49;
    if(verificarTabuleiroJogada(letra, num) == TRUE){
        velha[letra][num].preenchido = 1;
        velha[letra][num].tipo = 'X';
        totalP++;
    }
    else if(verificarTabuleiroJogada(letra, num) == FALSE){
        jogadaX();
    }
}

void jogadaO(){
    int letra, num;
    char celulaInteresse[10];
    printf("Jogador O, informe a célula de interesse (Ex: A3): ");
    fgets(celulaInteresse, 10, stdin);
    if(celulaInteresse[0] >= 97 && celulaInteresse[0] <= 122){
        celulaInteresse[0] -= 32;
    }
    letra = celulaInteresse[0] - 65;
    num = celulaInteresse[1] - 49;
    if(verificarTabuleiroJogada(letra, num) == TRUE){
        velha[letra][num].preenchido = 1;
        velha[letra][num].tipo = 'O';
        totalP++;
    }
    else if(verificarTabuleiroJogada(letra, num) == FALSE){
        jogadaO();
    }
}

void imprimirTabuleiro(){
    for(int i = 0; i < 3; i++){
        printf("%c ", i + 65);
        for(int j = 0; j < 3; j++){
            printf("%c ", velha[i][j].tipo);
        }
        printf("\n");
    }
}

int main(){
    //INICIO
    zerarTabuleiro();
    //JOGO
    int final = 0;
    char str;
    while(final == 0){
        imprimirTabuleiro();
        if(totalP == 9){
            break;
        }
        jogadaX();
        str = 'X';
        imprimirTabuleiro();
        final = verificarTabuleiroResultado(str);
        if(final == 1){
            printf("Jogador do tipo: %c ganhou \n", str);
            break;
        }
        if(totalP == 9){
            break;
        }
        jogadaO();
        str = 'O';
        final = verificarTabuleiroResultado(str);
        if(final == 1){
            imprimirTabuleiro();
            printf("Jogador do tipo: %c ganhou \n", str);
            break;
        }
    }
    if(final == 0){
        printf("O resultado do jogo foi velha \n");
    }
    return 0;
}