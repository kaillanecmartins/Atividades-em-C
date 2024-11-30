#include <stdio.h>
#include <stdlib.h>
#define numLula 13
#define numBolso 22

typedef struct {
  int nr_zona, nr_secao, qt_aptos, qt_comparecimento, qt_abstencoes, nr_votavel, qt_votos;        
  char nm_votavel[20];             
} candidato;

typedef candidato elemento;

#include "tad_tree.h"

void adicionar(tree t, elemento e);
tree carregaDados(tree t, elemento e, char *arquivo);
int compara(elemento item1, elemento item2);
void imprimir(tree t);


void montaTela(){
  system("clear");
  printf("\t\t1 - Carregar dados em arvore\n");
  printf("\t\t2 - Listar por Zona Eleitoral\n");
  printf("\t\t3 - Informar a quantidade de votos dos dois candidatos a presidente(por zona)\n");
  printf("\t\t4 - Informar a quantidade de votos dos dois candidatos a presidente(por secao)\n");
  printf("\t\t5 - Informar quantas secoes cada Zona Eleitoral possue\n");
  printf("\t\t6 - Informar Zona Eleitoral em que o candidato obteve maior porcentagem de votos\n");
  printf("\t\t9 - Sair\n");
  printf("\t\tDigite a opcao: ");
}

int compara(elemento item1, elemento item2) {
  return item1.nm_votavel == item2.nm_votavel;
}

tree carregaDados(tree t, elemento e, char *arquivo) {
  FILE *file = fopen(arquivo, "r"); 

  if (file != NULL) {
    while (!feof(file)) { 
      fscanf(file, "%d%d%d%d%d%d%s%d", &e.nr_zona, &e.nr_secao, &e.qt_aptos, &e.qt_comparecimento, &e.qt_abstencoes, &e.nr_votavel, e.nm_votavel, &e.qt_votos);
      if (t != NULL){
        adicionar(t, e);
      }
      else {
        criaRaiz(&t, e);
      }
    }
    fclose(file);
    return t;
  }
}

void adicionar(tree t, elemento e) {
  if (e.nr_zona == t->info.nr_zona) { 
    if (t->dir == NULL){
      criarNodoDir(t, e);
    }            
    else{
      adicionar(t->dir, e);
    }     
  } else {
    if (t->esq == NULL) 
      criarNodoEsq(t, e);
    else
      adicionar(t->esq, e); 
  }
}

void imprimirZona(tree t, int zona){
  if(t != NULL){
    if(t->info.nr_zona == zona){
      printf("Secao:%d\t Aptos:%d\t Comparecimento:%d\t Abstencoes:%d\t Nome:%s\t N:%d\t Votos:%d\n", t->info.nr_secao, t->info.qt_aptos, t->info.qt_comparecimento, t->info.qt_abstencoes, t->info.nm_votavel, t->info.nr_votavel, t->info.qt_votos);
      imprimir(t->dir);
    }else{
      imprimirZona(t->esq, zona);
    }
  }
}

void imprimir(tree t) {
  if (t != NULL) {
    printf("Secao:%d\t Aptos:%d\t Comparecimento:%d\t Abstencoes:%d\t Nome:%s\t N:%d\t Votos:%d\n", t->info.nr_secao, t->info.qt_aptos, t->info.qt_comparecimento, t->info.qt_abstencoes, t->info.nm_votavel, t->info.nr_votavel, t->info.qt_votos);
    imprimir(t->dir);
  }
}

int pegaNumZona(){
  int z = 0;
  printf("\n\t\tInforme o numero da zona: ");
  scanf("%d", &z);
  return z;
}

int pegaNumSecao(){
  int s = 0;
  printf("\n\t\tInforme o numero da secao: ");
  scanf("%d", &s);
  return s;
}

void qtVotosZona(tree t, int zona, int *vt, int numCand){
  if(t != NULL){
    if(t->info.nr_zona == zona){
      if(t->info.nr_votavel == numCand){
        *vt += t->info.qt_votos;
      }
      qtVotosZona(t->dir, zona, vt, numCand);
    }else{
      qtVotosZona(t->esq, zona, vt, numCand);
    }
  }
}

void qtVotosSecao(tree t, int zona, int secao, int *vt, int numCand){
  if(t != NULL){
    if(t->info.nr_zona == zona){
      if(t->info.nr_secao == secao){
       if(t->info.nr_votavel == numCand){
        *vt = t->info.qt_votos;
         }
      }
      qtVotosSecao(t->dir, zona, secao, vt, numCand);
    }else{
      qtVotosSecao(t->esq, zona, secao, vt, numCand);
    }
  }
}

void qtSecoesporZona(tree t, int zona, int *sc){
  if(t != NULL){
    if(t->info.nr_zona == zona){
      *sc += 1; 
      qtSecoesporZona(t->dir, zona, sc);
      }else{
        qtSecoesporZona(t->esq, zona, sc);
      }
      
    }
  }

void contaZonas(tree t, int *numZonas){
  if(t != NULL){
    if(t->esq == NULL){
     *numZonas = t->info.nr_zona; 
    }
    contaZonas(t->esq, numZonas);
  }
}

void maiorPercen(tree t, int numZonas){
  int zona = 1, qtdLula = 0, qtdBoso = 0, zonaPercenLula = 0, zonaPercenBoso = 0, Candidato = 0;
  int qtd_comp = 0;
  float percenLula = 0.0, percenBoso = 0.0, maiorPercenL = 0.0, maiorPercenB = 0.0;

  
  printf("\t\tDigite o numero do candidato: ");
  scanf("%d", &Candidato);
  
  while(zona <= numZonas){
  
    if(t != NULL){
      
      qtVotosZona(t, zona, &qtdLula, 13);
      qtVotosZona(t, zona, &qtdBoso, 22);
      
        
        qtd_comp = t->info.qt_comparecimento;
        percenLula = qtdLula / qtd_comp;
        percenBoso = qtdBoso / qtd_comp;
        
        if(percenLula > maiorPercenL){
          maiorPercenL = percenLula;
          zonaPercenLula = zona;
        }
        if(percenBoso > maiorPercenB){
          maiorPercenB = percenBoso;
          zonaPercenBoso = zona;  
        
      }
    }
    qtd_comp = 0;
    qtdLula = 0;
    qtdBoso = 0;
    percenLula = 0.0;
    percenBoso = 0.0;
    zona++;
  }
    if(Candidato == 13){
      printf("\t\tA zona com maior percentual de votos no Candidato LULA é: %d\n", zonaPercenLula);
    }
    if(Candidato == 22){
      printf("\t\tA zona com maior percentual de votos no Candidato BOLSONARO é: %d\n", zonaPercenBoso);
    }
    else if(Candidato != 13 && Candidato != 22){
      printf("\t\tNumero Inválido!\n");
    }
}

int main(void) {
  tree t;
  define(&t);
  elemento e;
  int zona, qtv = 0, secao, numCand = 0, numZonas = 0, maiorPerc = 0, maiorVoto = 0;
  int opcao = 0;

  do{
    montaTela();
    scanf("%d", &opcao);
    getchar();
    
    switch(opcao){
      //funciona
    case 1:
      system("clear");
      t = carregaDados(t, e, "dados.txt");
      printf("\t\tDados carregados com sucesso!\n");
      getchar();
    break;

      //funciona
    case 2:
      system("clear");
      printf("\n");
      zona = pegaNumZona();
      printf("\nDados da Zona %d:\n", zona);
      imprimirZona(t, zona);
      getchar();
      getchar();
    break;

      //funciona
    case 3:
      system("clear");
      printf("\n");
      zona = pegaNumZona();
      qtVotosZona(t, zona, &qtv, numLula);
      if(qtv != 0){
        printf("\t\tVotos Lula na zona %d: %d\n", zona, qtv);
        qtv = 0;  
      }else{
        printf("\n\t\tEsta zona nao existe\n");
      }
      qtVotosZona(t, zona, &qtv, numBolso);
      if(qtv != 0){
        printf("\t\tVotos Bolsonaro na zona %d: %d\n", zona, qtv);
        qtv = 0;  
      }
      getchar();
      getchar();
    break;

      //funciona
    case 4:
      system("clear");
      printf("\n");
      zona = pegaNumZona();
      secao = pegaNumSecao();
      qtVotosSecao(t, zona, secao, &qtv, numLula);
      if(qtv != 0){
        printf("\n");
        printf("\t\tVotos Lula na secao %d: %d\n", secao, qtv);
        qtv = 0;  
      }else{
        printf("\n\t\tEsta zona ou secao nao existe\n");
      }
      qtVotosSecao(t, zona, secao, &qtv, numBolso);
      if(qtv != 0){
        printf("\t\tVotos Bolsonaro na secao %d: %d\n", secao, qtv);
        qtv = 0;  
      }
      getchar();
      getchar();
    break;

      //funciona
    case 5:
      system("clear");
      contaZonas(t, &numZonas);
      zona = 1;
      while(zona <= numZonas){
        qtSecoesporZona(t, zona, &qtv);
        if(qtv != 0){
          printf("\t\tNa zona %d tem %d secoes\n", zona, qtv/4);
        }
        zona ++;
        qtv = 0;
      }
      getchar();
    break;
      
    case 6:
      system("clear");
      contaZonas(t, &numZonas);
      maiorPercen(t, numZonas);
      getchar();
      getchar();
    break;
      
    case 9:
      system("clear");
      printf("\t\tsaindo...\n");
    break;

      default:
      system("clear");
      printf("opcao nao existe\n");
      getchar();
  }
  }while(opcao != 9);
  return 0;
}