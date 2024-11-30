#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct {
    char cargo[MAX];
    int num;
    char nome[MAX];
    char partido[MAX];
    int qtdvotos;
}candidatos;

typedef candidatos elemento;
const elemento VL_NULO = {"",0,"","",0};

#include "tad_lst2.h"
#include "gravar_ler.h"

tipo_lista lista;
int op;

//chamada das funcoes

void carregar_menu();
void chama_cargo();
void chama_num();
void chama_nome();
void chama_partido();
void chama_num_voto();
void chama_qtdvoto();
int posicao();
void listar_qtdvotos();
void listar();
void cadastrar();
void editar();
void excluir();
void votar();

void carregar_menu(){
    printf("--------MENU--------\n");
    printf("1 - Ler arquivo\n");
    printf("2 - Listar candidatos e Qtd de votos\n");
    printf("3 - Cadastrar candidato\n");
    printf("4 - Editar dados do candidato\n");
    printf("5 - Excluir candidato\n");
    printf("6 - Votar\n");
    printf("7 - Tamanho da lista\n");
    printf("9 - Salvar e sair\n");

    scanf("%d", &op);
}

void chama_cargo(char *cargo){
    printf("Informe o cargo do canditato: "); 
    fflush(stdin);
    scanf("%s",cargo);
}

void chama_num(int *num){
    printf("Informe o numero do cadidato: "); 
    fflush(stdin);
    scanf("%d", num);
}

void chama_nome(char *nome){
    printf("Informe o nome do canditato: "); 
    fflush(stdin);
    scanf("%s",nome);
}

void chama_partido(char *partido){
    printf("Informe o partido do canditato: "); 
    fflush(stdin);
    scanf("%s",partido);
}

void chama_num_voto(int *num){
    printf("Informe o numero do cadidato que deseja votar: "); fflush(stdin);
    scanf("%d", num);
}

void chama_qtdvoto(int *num){
    printf("Informe a quantidade de votos desse candidato: "); fflush(stdin);
    scanf("%d", num);
}

int posicao(int tam){
    int pos;
    if(tam > 0){
        do{
            printf("Informe a posicao do canditado: ");
            scanf("%d", &pos);
        } while((pos < 0) || (pos > lista.tamanho+1));
        return pos;
    }else
        return 1;
}

void listar_qtdvotos(){
    int tam; 
    elemento elem;
    system("clear");
    tam = tamanho(lista);
    if(tam > 0){
        for(int i = 1; i<= tam; i++){
            if(obter_elemento(lista,i,&elem))
                printf("Cargo: %s  \nNome: %s  \nQuantidade de votos: %d\n\n", elem.cargo, elem.nome, elem.qtdvotos);
        }
    }else 
        printf("Lista vazia!");
}

void listar(){
    int tam;
    elemento elem;
    system("clear");
    tam = tamanho(lista);
    if(tam>0){
        for(int i=1; i<=tam;i++){
            if(obter_elemento(lista,i,&elem))
                printf("%d- Cargo: %s  \nNome: %s  \nNumero: %d  \nPartido: %s\n\n", i, elem.cargo, elem.nome, elem.num, elem.partido);
        }
    }
    else
        printf("Lista vazia!");
        printf("\n");
    
}

void cadastrar(){
    int pos, tam; elemento elem= VL_NULO;
    system("clear");
    tam= tamanho(lista);
    chama_cargo(&elem.cargo);
    chama_nome(&elem.nome);
    chama_num(&elem.num);
    chama_partido(&elem.partido);
    pos = posicao(tamanho(lista));
    if(incluir_elemento(&lista,pos,elem))
        printf("Cadastrado com sucesso!");
}

void editar(){
    system("clear");
    listar();
    int pos, editvoto =0; 
    elemento elem = VL_NULO;
    pos = posicao(tamanho(lista));
    chama_cargo(&elem.cargo);
    chama_nome(&elem.nome);
    chama_num(&elem.num);
    chama_partido(&elem.partido);
      if(alterar_elemento(&lista,pos,elem))
        printf("Canditado editado com sucesso!");    
}

void excluir(){
    system("clear");
    listar();
    int pos;
    pos = posicao(tamanho(lista));
    if(excluir_elemento(&lista,pos)){
        printf("Candidato excluido!");
        printf("\n");
    }
}

void votar(){
    system("clear");
    listar();
    char nome[30]; 
    int titulo, tam,numvoto;
    elemento elem;
    tam = tamanho(lista);
    if(tam>0){
        chama_num_voto(&numvoto);
        for (int i= 1; i<=tam; i++){
            if(obter_elemento(lista,i,&elem)){
                if(numvoto == elem.num){
                    elem.qtdvotos++;
                    alterar_elemento(&lista,i,elem);
                    printf("Voto computado com sucesso!");
                }
            }
        }
    }
    
}

int main(){
    inicializa_lista(&lista);
    
    do{
        printf("\n");
        carregar_menu();
        system("clear");
        switch (op){
        case 1:
            carregar_lista(&lista);
            printf("\n");
            printf("Lista carregada com sucesso!");
            printf("\n");
            break;
        case 2:
            listar_qtdvotos();
            printf("\n");
            break;
        case 3:
            cadastrar();
            printf("\n");
            break;
        case 4:
            editar();
            printf("\n");
            break;
        case 5:
            excluir();
            printf("\n");
            break;
        case 6:
            printf("--------Lista de Candidatos de Aguas Claras--------\n");
            votar();
            printf("\n");
            break;
        case 7:
            tamanho_quantidade_nodos(lista);
            printf("\n<tecle ENTER para continuar>");
            getchar();
            getchar();
            printf("\n");
            break;
        case 9:
            gravar_lista(lista);
            printf("\n");
            break;
        default:
            printf("Opcao nao disponivel\n\n");
            carregar_menu();
            printf("\n");
            break;
        }
    } while(op != 9);
    return 0;
}