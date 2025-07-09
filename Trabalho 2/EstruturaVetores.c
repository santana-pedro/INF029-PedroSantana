#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

No *vetorPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/

int ehPosicaoValida(int posicao);

int criarEstruturaAuxiliar(int posicao, int tamanho){
    
    int retorno = 0;
    // se posição é um valor válido {entre 1 e 10}
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
        return retorno;
    }
    posicao--;
    // a posicao pode já existir estrutura auxiliar
    if(vetorPrincipal[posicao] != NULL){
        retorno = JA_TEM_ESTRUTURA_AUXILIAR;
        return retorno;
    }
    // o tamanho nao pode ser menor que 1
    if(tamanho < 1){
        retorno = TAMANHO_INVALIDO;
        return retorno;
    }
    vetorPrincipal[posicao] = malloc(sizeof(No));
    if(vetorPrincipal[posicao] == NULL){
        retorno = SEM_ESPACO_DE_MEMORIA;
        return retorno;
    }
    // deu tudo certo, crie
    else{
        vetorPrincipal[posicao]->elementos = 0;
        vetorPrincipal[posicao]->tamanho = tamanho;
        vetorPrincipal[posicao]->prox = NULL;
        retorno = SUCESSO;
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor){
    int retorno = 0;
    int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;

    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        retorno = POSICAO_INVALIDA;
    }
    else{
        // testar se existe a estrutura auxiliar
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->elementos < vetorPrincipal[posicao]->tamanho){
                //insere
                No *novo = malloc(sizeof(No));
                novo->conteudo = valor;
                novo->prox = NULL;
                No *copia = vetorPrincipal[posicao];
                while(copia->prox != NULL){
                    copia = copia->prox;
                }
                copia->prox = novo;
                vetorPrincipal[posicao]->elementos++;
                retorno = SUCESSO;
            }
            else{
                retorno = SEM_ESPACO;
            }
        }
        else{
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao){
    int retorno;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao -= 1;
        No *copia = vetorPrincipal[posicao]->prox;
        No *anterior = vetorPrincipal[posicao];
        if(copia != NULL){
            while(copia->prox != NULL){
                anterior = copia;
                copia = copia->prox;
            }
            free(copia);
            anterior->prox = NULL;
            vetorPrincipal[posicao]->elementos--;
            retorno = SUCESSO;
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else
        retorno = POSICAO_INVALIDA;
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
    int retorno;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL && vetorPrincipal[posicao]->elementos > 0){
            No *apagar, *copia = vetorPrincipal[posicao]->prox;
            while(copia->prox != NULL && copia->prox->conteudo != valor){
                copia = copia->prox;
            }
            if(copia->prox->conteudo == valor){
                if(copia->prox->prox != NULL){
                    apagar = copia->prox;
                    copia->prox = copia->prox->prox;
                    free(apagar);
                    apagar = NULL;
                }
                else{
                    apagar = copia->prox;
                    copia->prox = NULL;
                    free(apagar);
                    apagar = NULL;
                }
                vetorPrincipal[posicao]->elementos--;
                retorno = SUCESSO;
            }
            else{
                retorno = NUMERO_INEXISTENTE;
            }
        }
        else{
            if(vetorPrincipal[posicao] == NULL)
                retorno = SEM_ESTRUTURA_AUXILIAR;
            if(vetorPrincipal[posicao]->elementos <= 0)
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
        }
    }
    else
        retorno = POSICAO_INVALIDA;
    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao){
    int retorno = 0;
    if(posicao < 1 || posicao > 10){
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->elementos > 0){
                No *copia = vetorPrincipal[posicao]->prox;
                int contador = 0;
                while(copia != NULL){
                    vetorAux[contador] = copia->conteudo;
                    copia = copia->prox;
                    contador++;
                }
                retorno = SUCESSO;
            }
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){

    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->elementos > 0){
                No *copia = vetorPrincipal[posicao]->prox;
                int contador = 0;
                while(copia != NULL){
                    vetorAux[contador] = copia->conteudo;
                    copia = copia->prox;
                    contador++;
                }
                for(int i = 0; i < contador; i++){
                    for(int j = 0; j < contador; j++){
                        if(vetorAux[i] < vetorAux[j]){
                            int troca = vetorAux[j];
                            vetorAux[j] = vetorAux[i];
                            vetorAux[i] = troca;
                        }
                    }
                }
                retorno = SUCESSO;
            }
            else{
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            }
        }
        else
            retorno = SEM_ESTRUTURA_AUXILIAR;
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int retorno = 0;
    int contador = 0;

    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            if(vetorPrincipal[i]->elementos > 0){
                No *copia = vetorPrincipal[i]->prox;    
                while(copia != NULL){
                    vetorAux[contador] = copia->conteudo;
                    copia = copia->prox;
                    contador++;
                }
                retorno = SUCESSO;
            }
        }
    }
    if(retorno != SUCESSO){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int retorno = 0;
    int contador = 0;

    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            if(vetorPrincipal[i]->elementos > 0){
                No *copia = vetorPrincipal[i]->prox;    
                while(copia != NULL){
                    vetorAux[contador] = copia->conteudo;
                    copia = copia->prox;
                    contador++;
                }
                retorno = SUCESSO;
            }
        }
    }
    if(retorno != SUCESSO){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    else if(retorno == SUCESSO){
        for(int i = 0; i < contador; i++){
            for(int j = 0; j < contador; j++){
                if(vetorAux[i] > vetorAux[j]){
                    int troca = vetorAux[j];
                    vetorAux[j] = vetorAux[i];
                    vetorAux[i] = troca;
                }
            }
        }
    }
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            int tamanhoAtual = vetorPrincipal[posicao]->tamanho;
            int tamanhoDesejado = tamanhoAtual + novoTamanho;
            if(tamanhoDesejado >= 1){
                vetorPrincipal[posicao]->tamanho = tamanhoDesejado;
                if(vetorPrincipal[posicao]->elementos > tamanhoDesejado){
                    while(vetorPrincipal[posicao]->elementos > tamanhoDesejado){
                        excluirNumeroDoFinaldaEstrutura(posicao + 1);
                    }
                }
            }
            else{
                retorno = NOVO_TAMANHO_INVALIDO;
            }
        }
        else{
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao){
    int retorno = 0;
    if(ehPosicaoValida(posicao) == SUCESSO){
        posicao--;
        if(vetorPrincipal[posicao] != NULL){
            if(vetorPrincipal[posicao]->elementos > 0){
                retorno = vetorPrincipal[posicao]->elementos;
            }
            else{
                retorno = ESTRUTURA_AUXILIAR_VAZIA;
            }
        }
        else{
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    }
    else{
        retorno = POSICAO_INVALIDA;
    }

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote(){
    int retorno = 0;
    No *listaGeral = malloc(sizeof(No));
    if(listaGeral == NULL){
        return NULL;
    }
    listaGeral->prox = NULL;
    No *copiaListaGeral = listaGeral;
    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            if(vetorPrincipal[i]->elementos > 0){
                No *copiaParcial = vetorPrincipal[i]->prox;
                while(copiaParcial != NULL){
                    No *novoNo = malloc(sizeof(No));
                    if(novoNo == NULL){
                        destruirListaEncadeadaComCabecote(&listaGeral);
                        return NULL;
                    }
                    novoNo->conteudo = copiaParcial->conteudo;
                    novoNo->prox = NULL;
                    copiaListaGeral->prox = novoNo;
                    copiaListaGeral = novoNo;
                    copiaParcial = copiaParcial->prox;
                }
                retorno = SUCESSO;
            }
        }
    }
    if(retorno == SUCESSO){
        return listaGeral;
    }
    else if(retorno = 0){
        free(listaGeral);
        return NULL;
    }
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    if(inicio->prox != NULL){
        No *copia = inicio->prox;
        int contador = 0;
        while(copia != NULL){
            vetorAux[contador] = copia->conteudo;
            copia = copia->prox;
            contador++;
        }
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio){
    No *copia = *inicio;
    No *proximo;
    while(copia != NULL){
        proximo = copia->prox;
        free(copia);
        copia = proximo;
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar(){
    for(int i = 0; i < TAM; i++){
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar(){
    for(int i = 0; i < TAM; i++){
        if(vetorPrincipal[i] != NULL){
            No *copia = vetorPrincipal[i];
            No *proximo;
            while(copia != NULL){
                proximo = copia->prox;
                free(copia);
                copia = proximo;
            }
        }
        vetorPrincipal[i] = NULL;
    }
}
