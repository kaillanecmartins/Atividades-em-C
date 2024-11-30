typedef struct nodo *ptrNodo;
struct nodo {
	elemento elem;
  ptrNodo prox;
};

typedef struct {
	ptrNodo topo;
	int tamanho;
}pilha;

typedef pilha tipo_pilha;

int tamanhoPilha(pilha p){
  return p.tamanho;
}

void criarPilha(pilha *p) {
		p->tamanho = 0;
		p->topo  = NULL;
}


int pilhaVazia(pilha p) {
	 return (p.topo == NULL);
}


int empilharElemento(pilha *p, elemento e) {
   ptrNodo pnodo;
   pnodo = (ptrNodo)malloc(sizeof(struct nodo));
   if (pnodo==NULL) {
		return 0;
   }  else {
         pnodo->elem = e;
         pnodo->prox = p->topo;
         p->topo = pnodo;
         p->tamanho++;
         return 1;
   }
}

int desempilharElemento(pilha *p, elemento *e) {
   ptrNodo pnodo;
   if (pilhaVazia(*p))
        return 0;
   else
	{
        pnodo = p->topo;
        p->topo = p->topo->prox;
        *e = pnodo->elem;
        free(pnodo);
        p->tamanho--;
        return 1;
   }
}


int obterTopo(pilha p, elemento *e) {
	if (!pilhaVazia(p)) {
		*e = p.topo->elem;
		return 1;
	} else
   	return 0;
}