#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int cod_terminal;
  int data;
  int hora;
  char placa[9];
  int cod_empresa;
  float media_min;
} onibus;
typedef onibus elemento;

const elemento VL_NULO = {0, 0, 0, " ", 0, 0};

#include "tad_lst2.h"

tipo_lista lista_bus;

void menu();
int carregar_lista();
int listar();
int media_tempo();
int valor_por_empresa();

void menu() {
  printf("\tMenu \n");
  printf("1 - carregar lista\n");
  printf("2 - listar dados\n");
  printf("3 - media tempo das viagens dos veículos\n");
  printf("4 - valor a receber por empresa\n");
  printf("9 - sair\n\n");

  printf("Digite a opcao: ");
}

int carregar_lista(lista_encadeada *la) {
  FILE *arquivo;
  elemento e;
  int i = 0, tam;
  arquivo = fopen("2019-09-06.dat", "r");
  while (!feof(arquivo)) {
    fscanf(arquivo, "%d", &e.cod_terminal);
    fscanf(arquivo, "%d", &e.data);
    fscanf(arquivo, "%d", &e.hora);
    fscanf(arquivo, "%s", e.placa);
    fscanf(arquivo, "%d", &e.cod_empresa);
    incluir_elemento(la, ++i, e);
  }
  fclose(arquivo);
  printf("Carregado com sucesso!\n");
  printf("\n<tecle ENTER para continuar>");
  getchar();
  getchar();
  return 1;
}

int listar(lista_encadeada la) {
  int i, tam;
  elemento elem;
  printf("\n");
  tam = tamanho(la);
  if (tam > 0) {
    for (i = 1; i <= tam; i++) {
      if (obter_elemento(la, i, &elem))
        printf("%d %d %d %s %d\n", elem.cod_terminal, elem.data, elem.hora,
               elem.placa, elem.cod_empresa);
    }
    printf("\n<tecle ENTER para continuar>");
    getchar();
    getchar();
    return 1;
  } else
    printf("Lista vazia");
    printf("\n<tecle ENTER para continuar>");
    getchar();
    getchar();
  return 0;
}

int media_tempo(lista_encadeada la) {
  int i, tam;
  elemento elem;
  float valor1 = 0, valor2 = 0, valor3 = 0;
  printf("\n");
  tam = tamanho(la);
  if (tam > 0) {
    for (i = 1; i <= tam; i++) {
      if (obter_elemento(la, i, &elem)) {
        if (elem.placa == "NHO1587") {
          valor1 = elem.hora + valor1;
          elem.media_min = (valor1);
          alterar_elemento(&la, i, elem);
        } else if (elem.placa == "MPO0902") {
          valor2 = elem.hora + valor2;
          elem.media_min = (valor2);
          alterar_elemento(&la, i, elem);
        } else {
          valor3 = elem.hora + valor3;
          elem.media_min = (valor3);
          alterar_elemento(&la, i, elem);
        }
      }
      printf("A media em min do Veiculo: %s eh: %.2f\n", elem.placa,
             ((elem.media_min / 100) * 60));
    }
    printf("\n<tecle ENTER para continuar>");
    getchar();
    getchar();
    return 1;
  } else
    printf("Lista vazia");
  printf("\n<tecle ENTER para continuar>");
  getchar();
  getchar();
  return 0;
}

int valor_por_empresa(lista_encadeada la) {
  int i, tam;
  elemento elem;
  float valor1, valor2;
  printf("\n");
  tam = tamanho(la);
  if (tam > 0) {
    for (i = 1; i <= tam; i++) {
      if (obter_elemento(la, i, &elem))
        if (elem.cod_empresa == 1) {
          valor1 = valor1 + 100;
        } else
          valor2 = valor2 + 100;
    }
    printf("Valor total da empresa 1: R$ %.2f\n", valor1);
    printf("Valor total da empresa 2: R$ %.2f\n", valor2);
    printf("\n<tecle ENTER para continuar>");
    getchar();
    getchar();
    return 1;
  } else
    printf("Lista vazia");
  printf("\n<tecle ENTER para continuar>");
  getchar();
  getchar();
  return 0;
}

int main() {
  inicializa_lista(&lista_bus);
  int op;
  do {
    menu();
    scanf("%d", &op);
    switch (op) {
    case 1:
      carregar_lista(&lista_bus);
      printf("\n");
      break;
    case 2:
      listar(lista_bus);
      printf("\n");
      break;
    case 3:
      media_tempo(lista_bus);
      printf("\n");
      break;
    case 4:
      valor_por_empresa(lista_bus);
      printf("\n");
      break;
    case 9:
      printf("Saindo...");
      break;
    default:
      menu();
      printf("\n");
      break;
    }
  } while (op != 9);
  return 0;
}