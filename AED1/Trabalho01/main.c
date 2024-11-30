#include <stdio.h>
#include <stdlib.h>

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
  printf("\t\t0 - Carregar dados em arvore\n");
  printf("\t\t1 - Listar por ordem de comparecimento\n");
  printf("\t\t9 - Sair\n");
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
  if (e.qt_comparecimento < t->info.qt_comparecimento) { 
    if (t->esq == NULL){
      criarNodoEsq(t, e);
    }            
    else{
      adicionar(t->esq, e);
    }     
  } else {
    if (t->dir == NULL) 
      criarNodoDir(t, e);
    else
      adicionar(t->dir, e); 
  }
}

void imprimir(tree t) {
  if (t != NULL) {
    imprimir(t->esq);
    printf("Comparecimento:%d\t Abstencoes:%d\t Aptos:%d\t Zona:%d\t Secao:%d\t Nome:%s\t N:%d\t Votos:%d\n", t->info.qt_comparecimento, t->info.qt_abstencoes, t->info.qt_aptos, t->info.nr_zona, t->info.nr_secao, t->info.nm_votavel, t->info.nr_votavel, t->info.qt_votos);
    imprimir(t->dir);
  }
}

int main(void) {
  tree t;
  define(&t);
  elemento e;
  int opcao = 0;

  do{
    montaTela();
    scanf("%d", &opcao);
    getchar();
    
    switch(opcao){
    case 0:
      system("clear");
      t = carregaDados(t, e, "dados.txt");
      printf("Dados carregados com sucesso\n");
      getchar();
    break;

    case 1:
      system("clear");
      printf("Ordem de comparecimento:\n");
      imprimir(t);
      getchar();
    break;

    case 9:
      system("clear");
      printf("saindo...\n");
    break;

      default:
      system("clear");
      printf("opcao nao existe\n");
      getchar();
  }
  }while(opcao != 9);
  return 0;
}