#include <stdio.h>
#include <stdlib.h>
#include "tad_treeAVL.h"

int main(void) {
  int opcao, valor;
  No *raiz = NULL;
  do{
    printf("\n\n\t0-Sair\n\t1-Inserir\n\t2-Remover\n\t3-Imprimir\n\n");
    scanf("%d", &opcao);

    switch(opcao){
      case 0:
        printf("Saindo...\n");
      break;
      
      case 1:
        printf("\tDigite o valor a ser inserido: ");
        scanf("%d", &valor);
        raiz = inserir(raiz, valor);
      break;

      case 2:
        printf("\tDigite o valor a ser removido: ");
        scanf("%d", &valor);
        raiz = remover(raiz, valor);
      break;

      case 3:
        imprimir(raiz, 1);
      break;

      default:
        printf("\nOpcao invalida\n");
    }
  }while(opcao != 0);

  return 0;
}