/* REPRESENTAÇÃO DA ESTRUTURA LINEAR */
#define MAX 100 /*Tamanho máximo para Listas*/
typedef struct {
                  int tamanho;			
                  elemento lista[MAX];
  		} tipo_lista;

typedef tipo_lista lista_array;

int inicializa_lista(lista_array *la);
int tamanho(lista_array la);
int obter_elemento(lista_array la, int i, elemento *e);
int incluir_elemento(lista_array *la, int i, elemento e);
int alterar_elemento(lista_array *la, int i, elemento e);
int excluir_elemento(lista_array *la, int i);

inicializa_lista (lista_array *la) {
   la->tamanho = 0;
}

int tamanho(lista_array la) {
     return la.tamanho;
}


int incluir_elemento(lista_array *la, int i, elemento e) {
  int j;
  if ((i <= la->tamanho+1 ) && (i>0) && (la->tamanho < MAX))
  {
	for (j=la->tamanho-1; j>=i-1;j--)
                 la->lista[j+1]=la->lista[j];
       la->lista[i-1] = e;
       la->tamanho++;
       return 1;
  }
  else
       return 0;  /*Posicao i invalida*/
}

int obter_elemento(lista_array la, int i, elemento *e) {
     if ((i <= la.tamanho) && (i > 0)) {
     		*e = la.lista[i-1];
         	return 1;
     }
     else {
     		*e = VL_NULO;
		return 0;
     }
}

int alterar_elemento(lista_array *la, int i, elemento e) {
     if ((i <= la->tamanho) && (i > 0)) {
		la->lista[i-1] = e;
         	return 1;
     }
     else
        	return 0;
}

int excluir_elemento(lista_array *la, int i) {
	int j;
   	if ((i <= la->tamanho) && (i > 0)) {
		for (j=i-1; j<(la->tamanho-1); j++)
      			la->lista[j]=la->lista[j+1];
		la->tamanho--;
      		return 1;
   }
   else
        return 0;  /*Posicao i invalida*/
}

// int carregar_lista(lista_array *la, int i){
//   int j;
//   if (i > 0) {
// 	   for (j=1;j<=i;i++) {
// 	         fread("\n%d %d %s", &i, &elem.codigo, elem.nome);
//       }
//    }
// }

int gravar_lista(lista_array *la, int i){

  
}
