#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

  int cont = 0, qtdHomens = 0, qtdMulheres = 0, maiorIdade = 0, idade;
  char sexo, nome[20];
  FILE *fileE, *fileS;
  
  fileE = fopen("Entrada.txt", "r");
  fileS = fopen("Saida.txt", "w");

  fscanf(fileE, "%d\t", &cont);
  for(int i = 0; i < cont; i++){
    fscanf(fileE, "%c\t", &sexo);
    fscanf(fileE, "%s\t", nome);
    fscanf(fileE, "%d\t", &idade);
    if(sexo == 'F' || sexo == 'f'){
      qtdMulheres++;
    }
    if(sexo == 'M' || sexo == 'm'){
      qtdHomens++;
    }
    if(maiorIdade < idade){
      maiorIdade = idade;
    }
  }

  fprintf(fileS, "O numero de mulheres: %d\nO numero de homens: %d\nA idade da pessoa mais velha eh: %d", qtdMulheres, qtdHomens, maiorIdade);
  
  fclose(fileE);
  fclose(fileS);
  
  return 0;
}