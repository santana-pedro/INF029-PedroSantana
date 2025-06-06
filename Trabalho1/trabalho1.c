// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "trabalho1.h"
#include <stdlib.h>
#include <string.h>

DataQuebrada quebrarData(char data[]){
  DataQuebrada datas;
  char sDia[3], sMes[3], sAno[5];
  int contD = 0, contM = 0, contA = 0, contB = 0;
  for(int i = 0; data[i] != '\0'; i++){
    if(data[i] == '/'){
      if(contB == 0){
        sDia[contD] = '\0';
      }
      if(contB == 1){
        sMes[contM] = '\0';
      }
      contB++;
    }
    if(contB == 0 && data[i] != '/'){
      sDia[contD] = data[i];
      contD++;
    }
    if(contB == 1 && data[i] != '/'){
      sMes[contM] = data[i];
      contM++;
    }
    if(contB == 2 && data[i] != '/'){
      sAno[contA] = data[i];
      contA++;
    }
  }
  sAno[contA] = '\0';
  datas.iDia = atoi(sDia);
  datas.iMes = atoi(sMes);
  datas.iAno = atoi(sAno);
  return datas;
}

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */

 int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */

 int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */

 int q1(char data[]){
  int datavalida = 1;
  DataQuebrada dataAvaliar;
  dataAvaliar = quebrarData(data);
  //verificar data
  if(dataAvaliar.iMes < 1 || dataAvaliar.iMes > 12){
    datavalida = 0;
  }
  if(dataAvaliar.iDia < 1 || dataAvaliar.iDia > 31){
    datavalida = 0;
  }
  if(dataAvaliar.iAno < 1){
    datavalida = 0;
  }
  else if(dataAvaliar.iAno % 4 != 0 && dataAvaliar.iMes == 2){
    if(dataAvaliar.iDia > 28){
      datavalida = 0;
    }
  }
  else if(dataAvaliar.iAno % 4 == 0 && dataAvaliar.iAno % 100 != 0 && dataAvaliar.iMes == 2){
    if(dataAvaliar.iDia > 29){
      datavalida = 0;
    }
  }
  else if(dataAvaliar.iAno % 4 == 0 && dataAvaliar.iAno % 100 == 0 && dataAvaliar.iAno % 400 == 0 && dataAvaliar.iMes == 2){
    if(dataAvaliar.iDia > 29){
      datavalida = 0;
    }
  }
  else if(dataAvaliar.iAno % 4 == 0 && dataAvaliar.iAno % 100 == 0 && dataAvaliar.iAno % 400 != 0 && dataAvaliar.iMes == 2){
    if(dataAvaliar.iDia > 28){
      datavalida = 0;
    }
  }

  //printf("%s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
}


/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */

DiasMesesAnos q2(char datainicial[], char datafinal[]){
  //calcule os dados e armazene nas três variáveis a seguir
  DiasMesesAnos dma;
  if (q1(datainicial) == 0){
    dma.retorno = 2;
    return dma;
  }else if (q1(datafinal) == 0){
    dma.retorno = 3;
    return dma;
  }else{
    //verifique se a data final não é menor que a data inicial
    if(datafinal < datainicial){
      dma.retorno = 4;
      return dma;
    }
    else{
      //pegar as datas
      DataQuebrada dataI = quebrarData(datainicial);
      DataQuebrada dataF = quebrarData(datafinal);
      //calcule a distancia entre as datas
      int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
      if((dataF.iAno % 4 == 0 && dataF.iAno % 100 != 0) || (dataF.iAno % 400 == 0)){
        diasMes[1] = 29;
      }
      //AJUSTAR DIAS
      if(dataF.iDia < dataI.iDia){
        dataF.iMes -= 1;
        if(dataF.iMes == 0){
          dataF.iMes = 12;
          dataF.iAno -= 1;
        }
        dataF.iDia += diasMes[dataF.iMes - 1];
      }
      //AJUSTAR MESES
      if(dataF.iMes < dataI.iMes){
        dataF.iAno -= 1;
        dataF.iMes += 12;
      }
      dma.qtdDias = dataF.iDia - dataI.iDia;
      dma.qtdMeses = dataF.iMes - dataI.iMes;
      dma.qtdAnos = dataF.iAno - dataI.iAno;
      dma.retorno = 1;
      return dma;
    }
  }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */

 int q3(char *texto, char c, int isCaseSensitive){
  int qtdOcorrencias = 0;
  if(isCaseSensitive == 1){
    for(int i = 0; texto[i] != '\0'; i++){
      if(texto[i] == c){
        qtdOcorrencias++;
      }
    }
  }
  if(isCaseSensitive != 1){
    c = tolower(c);
    for(int i = 0; texto[i] != '\0'; i++){
      texto[i] = tolower(texto[i]);
      if(texto[i] == c){
        qtdOcorrencias++;
      }
    }
  }
  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */

 int q4(char *strTexto, char *strBusca, int posicoes[30]){
  int qtdOcorrencias = 0, qtdChar, posFinal, contPos = 0;
  for(int i = 0; i < strlen(strTexto); i++){
    qtdChar = 0;
    posFinal = 0;
    if(strBusca[qtdChar] == strTexto[i]){
      qtdChar++;
      for(int j = i + 1; j < i + strlen(strBusca); j++){
        if(strBusca[qtdChar] == strTexto[j]){
            qtdChar++;
            posFinal = j;
        }
      }
      if(qtdChar == strlen(strBusca)){
        posicoes[contPos] = i + 1;
        contPos++;
        qtdOcorrencias++;
        posicoes[contPos] = posFinal + 1;
        contPos++;
      }
    }
  }
  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num){
  int invert[10], contador = 0, multiplicador, parametro;
  while(num > 9){
    invert[contador] = num % 10;
    num /= 10;
    contador++;
  }
  for(int i = 0; i < contador; i++){
    multiplicador = 10;
    parametro = contador - 1;
    while(parametro != i){
      multiplicador *= multiplicador;
      parametro--;
    }
    num += invert[i] * multiplicador;
  }
  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca){
  int qtdOcorrencias = 0, contador = 0, parametro = numerobusca, divisor = 10;
  while(parametro > 0){
    parametro /= 10;
    contador++;
  }
  for(int i = 0; i < contador - 1; i++){
    divisor *= 10;
  }
  while(numerobase > 0){
    if(numerobusca == numerobase % divisor){
      qtdOcorrencias++;
    }
    numerobase /= 10;
  }
  
  return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5]){
  int achou, contP;
  //HORIZONTAL
    //INDO
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 10; j++){
      contP = 0;
      for(int h = j; h < j + 5; h++){
        if(matriz[i][h] != palavra[contP]){
          achou = 0;
          break;
        }
        contP++;
        if(contP == 5){
          achou = 1;
          break;
        }
      }
      if(achou == 1){
        break;
      }
    }
    if(achou == 1){
      break;
    }
  }

    //VOLTANDO
  if(achou == 0){
    for(int i = 8; i >= 0; i--){
      for(int j = 10; j >= 0; j--){
        contP = 0;
        for(int h = j; h >= j - 5; h--){
          if(matriz[i][h] != palavra[contP]){
            achou = 0;
            break;
          }
          contP++;
          if(contP == 5){
            achou = 1;
            break;
          }
        }
        if(achou == 1){
          break;
        }
      }
      if(achou == 1){
        break;
      }
    }
  }
  //VERTICAL
    //INDO
  if(achou == 0){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 10; j++){
        contP = 0;
        for(int h = j; h < j + 5; h++){
          if(matriz[h][i] != palavra[contP]){
            achou = 0;
            break;
          }
          contP++;
          if(contP == 5){
            achou = 1;
            break;
          }
        }
        if(achou == 1){
          break;
        }
      }
      if(achou == 1){
        break;
      }
    }
  }
    //VOLTANDO
  if(achou == 0){
    for(int i = 8; i >= 0; i--){
      for(int j = 10; j >= 0; j--){
        contP = 0;
        for(int h = j; h >= j - 5; h--){
          if(matriz[h][i] != palavra[contP]){
            achou = 0;
            break;
          }
          contP++;
          if(contP == 5){
            achou = 1;
            break;
          }
        }
        if(achou == 1){
          break;
        }
      }
      if(achou == 1){
        break;
      }
    }
  }
  //DIAGONAL
    //INDO
  if(achou == 0){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 10; j++){
        contP = 0;
        for(int h = j, k = i; h < j + 5 && k < i + 5; h++, k++){
          if(matriz[h][k] != palavra[contP]){
            achou = 0;
            break;
          }
          contP++;
          if(contP == 5){
            achou = 1;
            break;
          }
        }
        if(achou == 1){
          break;
        }
      }
      if(achou == 1){
        break;
      }
    }
  }
    //VOLTANDO
  if(achou == 0){
    for(int i = 8; i >= 0; i--){
      for(int j = 10; j >= 0; j--){
        contP = 0;
        for(int h = j, k = i; h >= j - 5 && k >= i - 5; h--, k--){
          if(matriz[h][k] != palavra[contP]){
            achou = 0;
            break;
          }
          contP++;
          if(contP == 5){
            achou = 1;
            break;
          }
        }
        if(achou == 1){
          break;
        }
      }
      if(achou == 1){
        break;
      }
    }
  }
  return achou;
 }

