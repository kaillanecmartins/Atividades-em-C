#include <stdio.h>
#include <stdlib.h>

typedef struct{
   char nome[20];
   char data[10];
}documento;

typedef documento elemento;
const elemento VL_NULO = {"", ""};

#include "tad_pilha2.h"
#include "gravar_ler.h"
tipo_pilha pilhaDocs;

void montaMenu(){
  system("clear");
  printf("-----MENU-----\n");
  printf("1 - Carregar pilha\n");
  printf("2 - Mostrar pilha\n");
  printf("3 - Mostrar pendente\n");
  printf("4 - Remover documento\n");
  printf("5 - Adicionar documento\n");
  printf("6 - Sair e salvar\n");
}

void entra_nome(char *nome){
  printf("Informe o nome do documento: \n"); 
  fflush(stdin);
  scanf("%s", nome);
}

void entra_data(char *data){
  printf("Informe a data do documento: \n"); 
  fflush(stdin);
  scanf("%s", data);
}

void adicionar(){
  system("clear");
  elemento elem = VL_NULO;
  entra_nome(elem.nome);
  entra_data(elem.data);
  if(empilharElemento(&pilhaDocs, elem)){
    printf("\nElemento incluido com sucesso!\n");
  }
}

void remover(){
  system("clear");
  elemento elem = VL_NULO;
  if(!(pilhaVazia(pilhaDocs))){
    desempilharElemento(&pilhaDocs, &elem);
    printf("Documento removido com sucesso!\n");
  }else{
    printf("\npilha vazia\n");
  }
}

void mostrar_pilha(){
  system("clear");
  elemento elem;
  tipo_pilha temp;

  criarPilha(&temp);
    if(!pilhaVazia(pilhaDocs)){
      while(!pilhaVazia(pilhaDocs)){
        desempilharElemento(&pilhaDocs, &elem);
        printf("nome: %s - data: %s\n", elem.nome, elem.data);
        empilharElemento(&temp,elem);
    }
    while(!pilhaVazia(temp)){
      desempilharElemento(&temp,&elem);
      empilharElemento(&pilhaDocs,elem);
    }
    }else{
      printf("\nNao ha documentos na pilha!\n");
    }
      
  printf("\nPrecione enter para continuar!\n");
  getchar();
}

void mostrarElemento(){
  system("clear");
  elemento elem;
  if(!(pilhaVazia(pilhaDocs))){
    if(obterTopo(pilhaDocs, &elem)){
      printf ("O documento pendente eh: %s\n", elem.nome);
    }  
  }else{
    printf("Pilha vazia!\n");
  }
  getchar();
}

int main(void) {
  int op = 0;

  do{
    montaMenu();
    scanf("%d", &op);

    switch(op){
      criarPilha(&pilhaDocs);
      case 1:  
        carregar_pilha(&pilhaDocs);
        printf("dados carregados com sucesso!\n");
        getchar();
        getchar();
      break;

      case 2:
        mostrar_pilha();
        getchar();
        getchar();
      break;

      case 3:
        mostrarElemento();
        getchar();
      break;

      case 4:
        remover();
        getchar();
      break;

      case 5:
        adicionar();
        getchar();
      break;

      case 6:
        gravar_pilha(pilhaDocs);
        printf("saindo...\n");
      break;

      default:
        printf("opcao nao disponivel");
    }
  }while(op < 6);
  return 0;
}