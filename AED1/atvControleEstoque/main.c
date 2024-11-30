#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int codigoProduto, quantidade;
  char descricao[50], tipoEmbalagem[15], dtValidade[10];  
  float valorCompra, valorVenda; 
} produtos;

typedef produtos elemento;
const elemento VL_NULO = {0, 0, "", "", "", 0.0, 0.0};

#include "tad_fila2.h"
tipo_fila filaProduto;

#include "tad_pilha2.h"
tipo_pilha pilhaProduto;

void menu(){
  system("clear");
  printf("1 - Mostrar Pilha e Fila\n");
  printf("2 - Adicionar elemento Pilha e Fila\n");
  printf("3 - Remover elemento Pilha e Fila\n");
  printf("4 - Mostrar elemento\n");
  printf("5 - Sair\n");
}

void entra_codigo(int *cod){
  printf("Informe o codigo do produto: \n"); 
  fflush(stdin);
  scanf("%d", cod);
}

void entra_quantidade(int *qtd){
  printf("Informe a quantidade do produto: \n"); 
  fflush(stdin);
  scanf("%d", qtd);
}

void entra_descricao(char *desc){
  printf("Informe a descricao do produto: \n"); 
  fflush(stdin);
  scanf("%s", desc);
}

void entra_tipoEmbalagem(char *tipoEmb){
  printf("Informe o tipo da embalagem do produto: \n"); 
  fflush(stdin);
  scanf("%s", tipoEmb);
}

void entra_dtValidade(char *dataVal){
  printf("Informe a data de validade do produto: \n"); 
  fflush(stdin);
  scanf("%s", dataVal);
}

void entra_valCompra(float *valComp){
  printf("Informe o valor de compra do produto: \n"); 
  fflush(stdin);
  scanf("%f", valComp);
}

void entra_valVenda(float *valVen){
  printf("Informe o valor de venda do produto: \n"); 
  fflush(stdin);
  scanf("%f", valVen);
}

void adicionar(){
  system("clear");
  elemento elem = VL_NULO;
  if(!(filaCheia(filaProduto))){
    entra_codigo(&elem.codigoProduto);
    entra_quantidade(&elem.quantidade);
    entra_descricao(elem.descricao);
    entra_tipoEmbalagem(elem.tipoEmbalagem);
    entra_dtValidade(elem.dtValidade);
    entra_valCompra(&elem.valorCompra);
    entra_valVenda(&elem.valorVenda);
    if(entrarElemento(&filaProduto, elem) && empilharElemento(&pilhaProduto, elem)){
      printf("Produto incluido com sucesso!");
      printf("\n");
    }    
  }else
    printf("Não foi possível realizar tarefa!");
  printf("\n");
getchar();
}

void mostrarElemento(){
  system("clear");
  elemento elem;
  if(!(filaVazia(filaProduto) && pilhaVazia(pilhaProduto))){
    if(primeiroFila(filaProduto, &elem)){
      printf ("O primeiro da fila eh: %s\n", elem.descricao);
    }if(obterTopo(pilhaProduto, &elem)){
      printf ("O primeiro da pilha eh: %s\n", elem.descricao);
    }  
  }else{
    printf("Fila e Pilha vazia!\n");
  }
  getchar();
}

void mostrar_fila(){
  system("clear");
  elemento elem;
    if(!filaVazia(filaProduto)){
      printf("Fila:\n");
      for(int i = 1;i <= tamanho(filaProduto); i++){
        sairElemento(&filaProduto,&elem);
        printf("%d ", elem.codigoProduto);
        printf("%s ", elem.descricao);
        printf("%d ", elem.quantidade);
        printf("%s ", elem.dtValidade);
        printf("\n");
        entrarElemento(&filaProduto, elem);
      }
    }else{
      printf("\nNao ha produtos na fila!\n");
    }
      
  printf("\nPrecione enter para continuar!\n");
  getchar();
}

void mostrar_pilha(){
  system("clear");
  elemento elem;
    if(!pilhaVazia(pilhaProduto)){
      printf("Pilha:\n");
      for(int i = 1;i <= tamanhoPilha(pilhaProduto); i++){
        desempilharElemento(&pilhaProduto, &elem);
        printf("%d ", elem.codigoProduto);
        printf("%s ", elem.descricao);
        printf("%d ", elem.quantidade);
        printf("%s ", elem.dtValidade);
        printf("\n");
        empilharElemento(&pilhaProduto, elem);
      }
    }else{
      printf("\nNao ha produtos na pilha!\n");
    }
      
  printf("\nPrecione enter para continuar!\n");
  getchar();
}

void removerElemento(){
  system("clear");
  elemento elem;
  if(!(filaVazia(filaProduto) && pilhaVazia(pilhaProduto))){
    desempilharElemento(&pilhaProduto, &elem);
    sairElemento(&filaProduto, &elem);
    printf("Elementos removidos com sucesso!\n");
  }else{
    printf("Fila e Pilha vazias!\n");
  }
}
int main(void) {
  int op = 0;
  
  do{
    menu();
    scanf("%d", &op);

    switch(op){
      case 1:
        mostrar_fila();
        getchar();
        mostrar_pilha();
      break;

      case 2:
        adicionar();
      break;

      case 3:
        removerElemento();
        getchar();
      break;

      case 4: 
        mostrarElemento();
        getchar();
      break;

      case 5:
        printf("Saindo...\n");
      break;
      
      default:
         printf("Opção não disponível\n");
    }
  }while(op != 5);
  return 0;
}