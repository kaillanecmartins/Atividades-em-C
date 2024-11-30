#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  float bonus;
  char nome[40];
} cliente;

typedef cliente elemento;

#include "tad_tree1.h"

void pause();
void limpa_tela() { system("clear"); }
int altura(tree t);

float soma_bonus(tree t) {
  if (t != NULL) {
    return (t->info.bonus + soma_bonus(t->esq) + soma_bonus(t->dir));
  } else
    return 0;
}

void monta_tela(tree a) {
  printf("\n0 - visualizar [%d clientes - R$ %.2f em bonus total]", contaNos(a),
         soma_bonus(a));
  printf("\n1 - incluir");
  printf("\n2 - contador de nós");
  printf("\n3 - somar conteúdo dos nós");
  printf("\n4 - altura");
  printf("\n5 - completa");
  printf("\n9 - sair\n");
}

char escolhe_opcao() { return getchar(); }

int comparaelementos(elemento item1, elemento item2) {
  return strcmp(item1.nome, item2.nome);
}

int estritamente_binaria(tree t) {
  if (t != NULL) {
    if (((t->esq != NULL && t->dir != NULL) ||
         (t->esq == NULL && t->dir == NULL)))
      return estritamente_binaria(t->esq) && estritamente_binaria(t->dir);
  } else
    return 0;
  return 1;
}

int completa(tree t) {
  if (t == NULL) {
    return 1;
  } else {
    if (altura(t->esq) == altura(t->dir)) {
      return 1;
    }
  }
  return 0;
}

int espelhada(tree t) {}

int arvore_completa(tree t) {
  if (t != NULL) {
    if (t->esq != NULL && t->dir != NULL) {
      return estritamente_binaria(t->esq) && estritamente_binaria(t->dir);
    }
  } else {
    return 0;
  }
  return 1;
}

void incluir(tree *arv) {
  char nome_cliente[40];
  char nome_pai[40];
  char opcao;
  float bonus_cliente;
  elemento e_cliente, e_pai;

  printf("Digite um nome de cliente para incluir: ");
  scanf("%s", nome_cliente);
  setbuf(stdin, NULL);
  printf("Digite o bonus para esse cliente: ");
  scanf("%f", &bonus_cliente);
  strcpy(e_cliente.nome, nome_cliente);
  e_cliente.bonus = bonus_cliente;
  if (vazia(*arv)) {
    criaRaiz(arv, e_cliente);
    printf("Primeiro elemento da árvore incluido (raiz)! ");
  } else {
    printf("Digite o nome do cliente pai (cliente que indicou): ");
    scanf("%s", nome_pai);
    setbuf(stdin, NULL);
    strcpy(e_pai.nome, nome_pai);
    if (localiza(*arv, e_pai) == NULL) {
      printf("Não encontrado!");
    } else {
      printf("Inserir à direita (D) ou à esquerda (E)? ");
      opcao = escolhe_opcao();
      setbuf(stdin, NULL);
      if (opcao == 'D' || opcao == 'd') {
        if (adicionarDirPai(*arv, e_pai, e_cliente))
          printf("Elemento incluido com sucesso");
        else
          printf("ja existe um outro item na sub-arvore direita ");
      } else {
        if (adicionarEsqPai(*arv, e_pai, e_cliente))
          printf("Elemento incluido com sucesso");
        else
          printf("ja existe um outro item na sub-rvore esquerda ");
      }
    }
    getchar();
  }
  printf("\n\n Digite <enter> para continuar");
  getchar();
}

void salvaItens(tree t, FILE *arq) {
  if (t != NULL) {
    fprintf(arq, "%s\n", t->info.nome);
    salvaItens(t->esq, arq);
    salvaItens(t->dir, arq);
  }
}

void salvaArquivo(tree t) {
  FILE *arq;
  arq = fopen("arquivo.txt", "w");
  salvaItens(t, arq);
  fclose(arq);
}

int contaNos(tree t) {
  if (t != NULL)
    return (1 + contaNos(t->esq) + contaNos(t->dir));
  else
    return 0;
}

int altura(tree t) {
  if (t == NULL) {
    return -1;
  } else {
    int esq = altura(t->esq);
    int dir = altura(t->dir);
    if (esq > dir)
      return esq + 1;
    else
      return dir + 1;
  }
}

void imprimeArvore(tree a, int nivel) {
  if (a != NULL) {
    for (int i = 1; i <= nivel; i++, printf("."))
      ;
    printf(" %s %.2f\n", a->info.nome, a->info.bonus);
    imprimeArvore(a->esq, nivel + 1);
    imprimeArvore(a->dir, nivel + 1);
  }
}

void pause() {
  printf("\nDigite <enter> para continuar");
  getchar();
  getchar();
}

int main() {
  char opcao;
  tree arv;
  define(&arv);
  //	carregar_arvore(&lista);
  do {
    limpa_tela();
    monta_tela(arv);
    opcao = escolhe_opcao();
    switch (opcao) {
    case '0':
      imprimeArvore(arv, 0);
      pause();
      break;
    case '1':
      incluir(&arv);
      break;
    case '2':
      printf("QTD de nós = %d", contaNos(arv));
      pause();
      break;
    case '3':
      printf("Soma do conteúdo dos nós = %0.2f ", soma_bonus(arv));
      pause();
      break;
    case '4':
      if (arv != NULL) {
        printf("Altura = %d", altura(arv));
      } else {
        printf("Altura = %d", altura(arv) + 1);
      }
      pause();
      break;
    case '5':
      printf("%d", completa(arv));
      pause();
      break;
    case '9':
      salvaArquivo(arv);
      exit(1);
      break;
    }
  } while (1 != 2);
}