#include <stdio.h>
#include <stdlib.h>

typedef struct no{
  int valor;
  struct no *esquerdo, *direito;
  short altura;
}No;

No* balancear(No *raiz);
No* inserir(No *raiz, int x);
No* novoNo(int x);
short maior(short a, short b);


No* novoNo(int x){
  No *novo = malloc(sizeof(No));

  if(novo){
    novo->valor = x;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    novo->altura = 0;
  }
  else{
    printf("\n ERRO ao alocar no em novoNo\n");
  }
  return novo;
}

short maior(short a, short b){
  return (a > b)? a: b;
}

short alturaDoNo(No *no){
  if(no == NULL){
    return -1;
  }else{
    return no->altura;
  }
}

short fatorDeBalanceamento(No *no){
  if(no){
    return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
  }else{
    return 0;
  }
}

No* rotacaoEsquerda(No *r){
  No *y, *f;
  y = r->direito;
  f = y->esquerdo;

  y->esquerdo = r;
  r->direito = f;

  r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
  y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

  return y;
}

No* rotacaoDireita(No *r){
  No *y, *f;

  y = r->esquerdo;
  f = y->direito;

  y->direito = r;
  r->esquerdo = f;

  r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
  y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

  return y;
}

No* rotacaoDireitaEsquerda(No *r){
  r->direito = rotacaoDireita(r->direito);
  return rotacaoEsquerda(r);
}

No* rotacaoEsquerdaDireita(No *r){
  r->esquerdo = rotacaoEsquerda(r->esquerdo);
  return rotacaoDireita(r);
}

No* inserir(No *raiz, int x){
  if(raiz == NULL){
    return novoNo(x);
  }else{
    if(x < raiz->valor){
      raiz->esquerdo = inserir(raiz->esquerdo, x);
    }else if(x > raiz->valor){
      raiz->direito = inserir(raiz->direito, x);
    }else{
      printf("\nInsercao nao realizada\nO elemento %d ja existe\n", x);
    }
  }

  raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

  raiz = balancear(raiz);

  return raiz;
}

No* balancear(No *raiz){
  short fb = fatorDeBalanceamento(raiz);

  //Rotação à esquerda
  if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0){
    raiz = rotacaoEsquerda(raiz);
  }

  //Rotação à direita
  else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0){
    raiz = rotacaoDireita(raiz);
  }

  //Rotação dupla à esquerda
  else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0){
    raiz = rotacaoEsquerdaDireita(raiz);
  }

  //Rotação dupla à direita
  else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0){
    raiz = rotacaoDireitaEsquerda(raiz);
  }

  return raiz;
}

No* remover(No *raiz, int chave){
  if(raiz == NULL){
    printf("Valor nao encontrado\n");
    return NULL;
  }else{
    if(raiz->valor == chave){
      if(raiz->esquerdo == NULL && raiz->direito == NULL){
        free(raiz);
        printf("Elemento folha removido: %d\n", chave);
        return NULL;
      }else{
        if(raiz->esquerdo != NULL && raiz->direito != NULL){
          No *aux = raiz->esquerdo;
          while(aux->direito != NULL){
            aux = aux->direito;
          }
          raiz->valor = aux->valor;
          aux->valor = chave;
          printf("Elemento trocado: %d\n", chave);
          return raiz;
        }else{
          No *aux;
          if(raiz->esquerdo != NULL){
            aux = raiz->esquerdo;
          }else{
            aux = raiz->direito;
          }
          free(raiz);
          printf("Elemento com 1 filho removido: %d\n", chave);
          return aux;
        }
      }
    } else{
      if(chave < raiz->valor){
        raiz->esquerdo = remover(raiz->esquerdo, chave);
      }else{
        raiz->direito = remover(raiz->direito, chave);
      }
    }

    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    raiz = balancear(raiz);
    return raiz;
  }
}

void imprimir(No *raiz, int nivel){
  int i;
  if(raiz){
    imprimir(raiz->direito, nivel + 1);
    printf("\n\n");
    
    for(i = 0; i < nivel; i++){
      printf("\t");
    }
    printf("%d", raiz->valor);
    imprimir(raiz->esquerdo, nivel + 1);
  }
}

