#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        	        char letra;
    		       } elemento;

#include "arvore.h"

const elemento VL_NULO = {'\0'};

void imprimeArvore(tree a) {
    if (a != NULL){
       printf(" %c\n",a->info.letra);
       imprimeArvore(a->esq);
       imprimeArvore(a->dir);
    }
}

int comparaelementos(elemento item1, elemento item2) {
   if (item1.letra == item2.letra)
      return 0;
   else 
      if (item1.letra > item2.letra) 
         return 1;
      else
         return -1;
}

int main(){
    tree a, cabeca;
    elemento e;

    define(&a);
    criaRaiz(&a, VL_NULO);

    FILE *ptr;

    int i, j, k = 0;

    char cod[10];
    char morse[100];
    
    cabeca = a;

    ptr = fopen("morse.txt","r");
    while (fgets(cod,sizeof(cod),ptr)!=NULL){
    	k=strlen(cod);
      e.letra = cod[0];
      for (j = 1; j<=k; j++){
            if (cod[j]=='.'){
                if (a->esq != NULL){
                    a = a->esq;
                }
                else {
                    criarNodoEsq(a, VL_NULO);
                    a = a->esq;
                }
            }
            if (cod[j]=='-'){
                if (a->dir != NULL){
                    a = a->dir;
                }
                else{
                    criarNodoDir(a, VL_NULO);
                    a = a->dir;
                }
            }
     }
	   a->info = e;
     a=cabeca;
  }
  fclose(ptr);

  //Imprimir a mensagem que está no arquivo mensagem.txt
  ptr = fopen("mensagem.txt","r");
  while (!feof(ptr)) {
        a=cabeca;
	      fscanf(ptr,"%s",morse);
        k = strlen(morse);
        for (i=0; i<=k; i++){
           if (morse[i]=='.'){
              a=a->esq;
           }
           if (morse[i]=='-'){
              a=a->dir;
           }
           if (morse[i]=='/'){
              printf(" ");
           } 
        }
        putchar(a->info.letra);
  }
  printf("\n");
  fclose(ptr);
}