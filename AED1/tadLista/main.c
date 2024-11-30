#include <stdio.h>
#include <stdlib.h>

typedef struct {
                   long codigo;
                   char nome[80];
		} cliente;
typedef cliente elemento;

/* DECLARACOES GLOBAIS DE CONSTANTES */
const elemento VL_NULO = {0, ""};

#include "tad_lst2.h"

tipo_lista lista;

void monta_tela() {
	printf("\n0 - listar");
   	printf("\n1 - incluir");
   	printf("\n2 - alterar");
   	printf("\n3 - excluir");
//   	printf("\n4 - alterar saldo");
   	printf("\n9 - sair e salvar\n");
}

char escolhe_opcao() {
	return getchar();
}

int posicao_para_alterar(int tam) {
	int pos;
	if (tam > 0) {
   		do {
			printf("\nEm qual posicao vc deseja alterar");
         		scanf("%d",&pos);
      		} while ((pos<0) || (pos>lista.tamanho+1));
	return pos;
   }
   else
      	return 1;
}

int posicao_para_incluir(int tam) {
	int pos;
	if (tam > 0) {
   		do {
			printf("\nEm qual posicao vc deseja incluir");
         		scanf("%d",&pos);
      		} while ((pos<0) || (pos>lista.tamanho+1));
	return pos;
   }
   else
      	return 1;
}

int posicao_para_excluir(int tam){
  int pos;
  if(tam>0){
    do{
      printf("\nQual posicao deseja excluir: ");
      scanf("%d", &pos);
    }while((pos<0) || (pos>lista.tamanho+1));
  }
  return pos;
}

limpa_tela() {
	system("clear");
}

entra_codigo(long *codigo) {
	printf("\nQual o codigo do cliente? "); fflush(stdin); scanf("%d", codigo);
}

entra_nome(char *nome) {
	printf("\nQual o nome do cliente? "); fflush(stdin); scanf("%s", nome);
}

void incluir() {
	int pos; elemento elem=VL_NULO;
	limpa_tela();
	entra_codigo(&elem.codigo);
	entra_nome(&elem.nome);
	pos = posicao_para_incluir(tamanho(lista));
   	if (incluir_elemento(&lista,pos,elem))
       		printf("Elemento incluído com sucesso!");
	getchar();
}

void excluir(){
  int pos; 
  elemento elem;
  limpa_tela();
  pos = posicao_para_excluir(tamanho(lista));
  obter_elemento(lista, pos, &elem);
  printf("\n%d - %d - %s", pos, elem.codigo, elem.nome);
  getchar();
  if(excluir_elemento(&lista, pos))
    printf("\nElemento excluido com sucesso!");
  getchar();
}

void listar() {
  FILE *file;
  file = fopen("dados.bin", "rb");
	int i, tam; elemento elem;
	limpa_tela(); printf("\n");
  // if(!feof(file)){
    
  // }
  // for (i=1;i<=MAX;i++) {
	 //      if (obter_elemento(lista,i,&elem)){
          
  //       }
	         
  //          printf("%d - %d - %s", i, elem.codigo, elem.nome);
  //     } 
  
  
  //  /*if (tam > 0) {
     
	   
  //  }
  //  else
  //     printf("Lista vazia");*/
   printf("\n<tecle ENTER para continuar>");getchar();getchar();
}

void alterar() {
	int pos; elemento elem=VL_NULO;
	limpa_tela();
	listar();
	pos = posicao_para_alterar(tamanho(lista));
	entra_codigo(&elem.codigo);
	entra_nome(&elem.nome);
   	if (alterar_elemento(&lista,pos,elem))
       		printf("Elemento alterado com sucesso!");
	getchar();
}

int main() {
	char opcao;
	inicializa_lista(&lista);
	//carregar_lista(&lista);
   do {
        limpa_tela();	
   	monta_tela();
        opcao = escolhe_opcao();
   	switch (opcao) {
      	case '0':
         	listar();
            break;
      	case '1':
         	incluir();
            break;
      	case '2':
        	alterar();
            break;
      	case '3':
         excluir();
            break;
         case '9':
	      gravar_lista(lista);
         	exit(1);
            break;
      }
   } while (1);
}
