#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct poltrona {
  char nome[50];
  float valor;
  int status;
} poltrona;

int main(void) {

  poltrona mat[MAX][MAX];
  int escolha, linha, coluna, status, r;
  char nome[50];
  float totalBilheteria = 0.0;
  FILE *file;

  file = fopen("bdTeatro.bin", "rb");

  // carregando matriz
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      fread(&mat[i][j], sizeof(poltrona), 1, file);
    }
  }
  fclose(file);

  // iniciando programa
  do {
    printf("\n--------MENU--------\n");
    printf("1 - Exibir status das poltronas\n2 - Reservar\n3 - Comprar\n4 - "
           "Editar status\n5 - Bloquear\n6 - Pesquisar Cliente\n7 - Calcular "
           "total bilheteria\n9 - Sair e salvar\n");
    scanf("%d", &escolha);
    printf("\n");

    switch (escolha) {
    case 1:
      printf("status das poltronas:\n");
      for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
          printf("[ %d ]\t", mat[i][j].status);
        }
        printf("\n");
      }
      break;

    case 2:
      printf("\nLinha da poltrona que deseja reservar: ");
      scanf("%d", &linha);
      printf("\nColuna da poltrona que deseja reservar: ");
      scanf("%d", &coluna);
      printf("\nquem deseja reservar? ");
      scanf("%s", mat[linha - 1][coluna - 1].nome);

      if (mat[linha - 1][coluna - 1].status == 1) {
        mat[linha - 1][coluna - 1].status = 3;
        printf("\npoltrona reservada com sucesso!\n");
      } else {
        if (mat[linha - 1][coluna - 1].status == 2) {
          printf("\na poltrona nao pode ser reservada, pois esta vendida\n");
        }
        if (mat[linha - 1][coluna - 1].status == 3) {
          printf(
              "\na poltrona nao pode ser reservada, pois ja esta reservada\n");
        }
        if (mat[linha - 1][coluna - 1].status == 4) {
          printf("\na poltrona nao pode ser reservada, pois esta bloqueada\n");
        }
      }
      break;

    case 3:
      printf("\nLinha da poltrona que deseja comprar: ");
      scanf("%d", &linha);
      printf("\nColuna da poltrona que deseja comprar: ");
      scanf("%d", &coluna);
      printf("\nquem deseja comprar? ");
      scanf("%s", mat[linha - 1][coluna - 1].nome);

      if (mat[linha - 1][coluna - 1].status == 1) {
        mat[linha - 1][coluna - 1].status = 2;
        printf("\npoltrona vendida com sucesso!\n");
      } else {
        if (mat[linha - 1][coluna - 1].status == 2) {
          printf("\na poltrona nao pode ser comprada, pois foi esta vendida\n");
        }
        if (mat[linha - 1][coluna - 1].status == 3) {
          printf("\na poltrona nao pode ser comprada, pois esta reservada\n");
        }
        if (mat[linha - 1][coluna - 1].status == 4) {
          printf("\na poltrona nao pode ser comprada, pois esta bloqueada\n");
        }
      }
      break;

    case 4:
      printf("\nLinha da poltrona que deseja editar: ");
      scanf("%d", &linha);
      printf("\nColuna da poltrona que deseja editar: ");
      scanf("%d", &coluna);
      printf("\nPara qual status deseja alterar? ");
      scanf("%d", &status);
      printf("\nPara qual nome deseja alterar? ");
      scanf("%s", mat[linha - 1][coluna - 1].nome);
      printf("\nPara qual valor deseja alterar? ");
      scanf("%f", &mat[linha - 1][coluna - 1].valor);

      mat[linha - 1][coluna - 1].status = status;
      printf("\nStatus alterado com sucesso\n");
      break;

    case 5:
      printf("\nLinha da poltrona deseja bloquear: ");
      scanf("%d", &linha);
      printf("\nColuna da poltrona deseja bloquear: ");
      scanf("%d", &coluna);
      mat[linha - 1][coluna - 1].status = 4;
      printf("\npoltrona bloqueada com sucesso!\n");
      break;

    case 6:
      printf("\nNome que deseja pesquisar: ");
      scanf("%s", nome);
      for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
          r = strcmp(mat[i][j].nome, nome);
          if(r == 0){
            printf("\nPoltrona: [%d][%d]\nStatus: %d", i + 1, j + 1, mat[i][j].status); 
            r = 1;
          }
        }
      }
      break;

    case 7:
      for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
          if(mat[i][j].status == 2){
            totalBilheteria = totalBilheteria + mat[i][j].valor; 
          }
        }
      }
      printf("Valor total da bilheteria: %.2f", totalBilheteria);
      break;

    case 9:
      printf("...salvando dados...\n");
      break;
      
    default:
      printf("\nopcao nao disponivel\n");
      
    }
  } while (escolha != 9);
  file = fopen("bdTeatro.bin", "wb");
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      fwrite(&mat[i][j], sizeof(poltrona), 1, file);
    }
  }
  printf("...Encerrado com sucesso...");

  fclose(file);
  return 0;
}