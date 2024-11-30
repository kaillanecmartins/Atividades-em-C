int gravar_pilha(pilha p);
int carregar_pilha(pilha *p);

int carregar_pilha(pilha *p) {
   FILE *arquivo;
   elemento e; int i=0;
   arquivo = fopen("docs.dat","rb");
   if (arquivo != NULL) {
      while(fread(&e, sizeof(elemento),1,arquivo)) {
         empilharElemento(p, e); 
      }
      fclose(arquivo);
      return 1;
   }
   else
      return 0;
}

int gravar_pilha(pilha p) {
   FILE *arquivo;
   elemento e;
   arquivo = fopen("docs.dat","wb");
   while(!pilhaVazia(p)){
       desempilharElemento(&p,&e);
       fwrite(&e, sizeof(elemento),1,arquivo);
   }
   fclose(arquivo);
}