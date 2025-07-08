#include <stdio.h>
#include <stdlib.h>

#include "EstruturaVetores.h"

int menu();

void dobrar(int *x){
    *x = *x * 2;
}

int menu(){
    int op;
    printf("Digite as opção desejada\n");
    printf("0 - Sair\n");
    printf("1 - Inserir\n");
    printf("2 - Excluir\n");
    printf("3 - Listar uma estrutura\n");
    printf("4 - Dobrar Numero\n");
    printf("5 - Criar estrutura \n");
    scanf("%d", &op);
    return op;
}

int main(){
    inicializar();
    int op;
    int sair = 0;
    int ret;
    while(!sair){
        op = menu();
        switch(op){
            case 0:{
                sair = 1;
                finalizar();
                break;
            }
            case 1:{ 
                //inserir
                //TODO
                ret = inserirNumeroEmEstrutura(5, 25);
                if (ret == SUCESSO){
                    printf("Inserido com sucesso");
                }
                else if (ret == SEM_ESPACO){
                    printf("Sem Espaço");
                }
                else if (ret == SEM_ESTRUTURA_AUXILIAR){
                    printf("Sem estrutura Auxiliar");
                }
                break;
            }
            case 2:{ 
                //excluir
                //TODO
                break;
            }

            case 3:{ 
                //recuperar dados estrutura auxiliar
                int posicao, retorno;
                printf("Qual a estrutura a ser listada (1..10)?");
                scanf("%d", &posicao);

                int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

                if (qtd == POSICAO_INVALIDA){
                    printf("Posição inválida");
                }
                else{ // existe elemento
                    int vetorAux[qtd];

                    retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);

                    if (retorno == SUCESSO){
                        //imprimir para os dados para o usuário
                        int i = 0;
                        for (; i < qtd; i++){
                            printf("%d", vetorAux[i]);
                        }
                    }
                }
                break;
            }
            case 4:{ 
                //dobrar
                //ler um numero
                int valor;
                scanf("%i", &valor);
                dobrar(&valor);
                //passar para um funcao (void dobrar(...)) que recebe o numero e dobra (EstruturaVetores.c)
                printf("%i", valor);
                break;
            }
            default:{
                printf("opcao inválida\n");
            }
            case 5:{
                //criar estrutura
                int posicao, tamanho, retorno;
                printf("Qual a posição (1 - 10) e o tamanho da estrutura a ser criada?\n");
                scanf("%d %d", &posicao, &tamanho);
                retorno = criarEstruturaAuxiliar(posicao, tamanho);
                if(retorno == JA_TEM_ESTRUTURA_AUXILIAR){
                    printf("Já há estrutura auxiliar nessa posição\n");
                }
                if(retorno == POSICAO_INVALIDA){
                    printf("Posição inválida, por favor insira uma posição entre 1 e 10\n");
                }
                if(retorno == TAMANHO_INVALIDO){
                    printf("Tamanho inválido, por favor insira um tamanho positivo, maior que 0\n");
                }
                if(retorno == SEM_ESPACO_DE_MEMORIA){
                    printf("Sem espaço de memória\n");
                }
                if(retorno == SUCESSO){
                    printf("SUCESSO! Estrutura auxiliar criada de tamanho %d na posicao %d\n", tamanho, posicao);
                }
                break;
            }
        }
    }
    return 0;
}
