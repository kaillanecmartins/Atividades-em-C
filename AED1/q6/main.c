#include <stdio.h>
#include <stdlib.h>
#define MAX 98

typedef struct letra{
char l;
int num;
}letra;

int main(void) {

  letra letras[MAX];
  int idMaior = 0, auxNum = 0;
  char nomeArq[100], c, maiorL;
  FILE *fileD, *fileE;

  fileD = fopen("letras.dat", "r");

  //carregando dados

  for(int i = 0; i < MAX; i++){
    fscanf(fileD, "%c", &letras[i].l);
  }

  printf("Informe o nome do arquivo que deseja verificar: ");
  scanf("%s", nomeArq);
  
  fileE = fopen(nomeArq, "r");
  
  while(!feof(fileE)){
    fscanf(fileE, "%c", &c);
    for(int i = 0; i < MAX; i++){
      if(letras[i].l == c){
        letras[i].num++;
      }
    }
  }
  fclose(fileE);
   auxNum = letras[0].num;
  for(int i = 0; i < MAX; i++){
    if(letras[i].num > auxNum){
      idMaior = i;
    }
  }
  maiorL = letras[idMaior].l;

  fileE = fopen(nomeArq, "a");
  fprintf(fileE,"\nCaractere que repete mais vezes: %c", maiorL);
  return 0;
}