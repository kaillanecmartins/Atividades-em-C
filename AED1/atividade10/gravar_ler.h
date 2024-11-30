int gravar_lista(lista_encadeada l);
int carregar_lista(lista_encadeada *l);

int carregar_lista(lista_encadeada *l) {
   FILE *arquivo;
   elemento e; int i=0;
   arquivo = fopen("dados.dat","rb");
   if (arquivo != NULL) {
      while(fread(&e, sizeof(elemento),1,arquivo)) {
         incluir_elemento(l, ++i, e); 
      }
      fclose(arquivo);
      return 1;
   }
   else
      return 0;
}

int gravar_lista(lista_encadeada l) {
   FILE *arquivo;
   elemento e;
   arquivo = fopen("dados.dat","wb");
   for (int i=1; i<=tamanho(l);i++) {
       obter_elemento(l,i,&e);
       fwrite(&e, sizeof(elemento),1,arquivo);     
   }
   fclose(arquivo);
}