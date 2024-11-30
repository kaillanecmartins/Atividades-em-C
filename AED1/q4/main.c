#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct aluno {
  int sequencial;
  int matricula;
  char nome[100];
} aluno;

int main(void) {

  aluno alunos[MAX];
  int sequencial = 0, condicao, i = 0, pesquisa, sequencialAux, matriculaAux, aux;
  char nomeAux[100];
  FILE *file;

  file = fopen("alunos.txt", "r");

  // carregando alunos
  while (!feof(file)) {
    fscanf(file, "%d %d %s", &alunos[i].sequencial, &alunos[i].matricula, alunos[i].nome);
    aux = alunos[i].sequencial;
    i++;
  }
  fclose(file);

  do{
    printf("\n----------MENU----------\n");
    printf("1 - Cadastrar aluno\n2 - Editar aluno\n3 - Deletar aluno\n4 - Ordenar alunos\n5 - Pesquisar alunos\n6 - Ler dados de arquivo\n7 - Sair e gravar\n");
    scanf("%d", &condicao);

    switch (condicao) {

    case 1:
      printf("Informe o nome do aluno: ");
      scanf("%s", alunos[i].nome);
      printf("Informe a matricula do aluno: ");
      scanf("%d", &alunos[i].matricula);
      alunos[i].sequencial = aux + 1;
      i++;
      break;

    case 2:
      printf("\nInforme a matricula do aluno que deseja editar: ");
      scanf("%d", &pesquisa);
      for (int j = 0; j < MAX; j++) {
        if (alunos[j].matricula == pesquisa) {
          printf("\nDigite o novo nome: ");
          scanf("%s", alunos[j].nome);
          printf("\nDigite a nova matricula: ");
          scanf("%d", &alunos[j].matricula);
        }
      }
      break;

    case 3:
      printf("\nInforme a matricula do aluno que deseja deletar: ");
      scanf("%d", &pesquisa);
      for (int j = 0; j < MAX; j++) {
        if (alunos[j].matricula == pesquisa) {
          memset(alunos[j].nome, 0, 100);
          alunos[j].matricula = 0;
          alunos[j].sequencial = 0;
        }
      }
      break;

    case 4:
      /* printf("\n1 - Ordenar por sequencial\n2 - Ordenar por nome\n3 - Ordenar "
             "por matricula\n");
      scanf("%d", &pesquisa);
      if (pesquisa == 1) {
      }
      if (pesquisa == 2) {
        for (int k = 1; k < MAX; k++) {

          for (int j = 1; j < MAX; j++) {
            // verifica se tem que ser depois, se for troca de posição
            if (strcmp(alunos[j - 1].nome, alunos[j].nome) > 0) {
              strcpy(nomeAux, alunos[j - 1].nome);
              strcpy(alunos[j - 1].nome, alunos[j].nome);
              strcpy(alunos[j].nome, nomeAux);
            }
          }
        }
      }
      if (pesquisa == 3) {

      } else {
        printf("\nopcao de ordenacao nao valida\n");
      }*/

      break;

    case 5:
      printf("\n1 - Pesquisar por nome\n2 - Pesquisar por matricula\n");
      scanf("%d", &pesquisa);
      if (pesquisa == 1) {
        printf("Informe o nome do aluno: ");
        scanf("%s", nomeAux);
        for (int j = 0; j < i; j++) {
          if (strcmp(nomeAux, alunos[j].nome) == 0) {
            printf("\nNome: %s\nMatricula: %d\nSequencial: %d", alunos[j].nome, alunos[j].matricula, alunos[j].sequencial);
          }
        }
        }
        if (pesquisa == 2) {
          printf("\nInforme a matricula do aluno: ");
          scanf("%d", &matriculaAux);
          for (int j = 0; j < MAX; j++) {
            if (matriculaAux == alunos[j].matricula) {
              printf("\nNome: %s\nMatricula: %d\nSequencial: %d", alunos[j].nome, alunos[j].matricula, alunos[j].sequencial);
            }
          }
        }
        break;

      case 6:
        file = fopen("alunos.txt", "r");

        printf("Dados dos alunos:\n");

        while (!feof(file)) {
          fscanf(file, "%d %d %s", &sequencialAux, &matriculaAux, nomeAux);
          printf("%d %d %s\n", sequencialAux, matriculaAux, nomeAux);
        }

        fclose(file);
        break;

      case 7:
        
        file = fopen("alunos.txt", "w");

        for (int j = 0; j < i; j++) {
          if(alunos[j].matricula != 0){
            fprintf(file, "%d %d %s\n", alunos[j].sequencial, alunos[j].matricula, alunos[j].nome);
          }
        }
        printf("\ndados salvos com sucesso!\n");
        break;

      default:
        printf("\nopcao nao disponivel");
        break;
      }
    }while (condicao != 7);

    fclose(file);
    return 0;
  }