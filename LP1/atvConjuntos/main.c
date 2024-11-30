#include <stdio.h>
#include <stdlib.h>
#define MAX 100

// autora: Kaillane Martins

int main()
{

    int vetA[MAX], vetB[MAX], uniao[MAX + MAX], intersecao[MAX], simetriaAB[MAX + MAX], difBA[MAX + MAX], num;
    FILE *fileA, *fileB;

    fileA = fopen("A.dat", "r");
    fileB = fopen("B.dat", "r");

    // colocando conteúdos dos arquivos nos vetores
    for (int i = 0; i < MAX; i++)
    {
        if (fscanf(fileA, "%d", &vetA[i]) == EOF)
        {
            vetA[i] = -1;
        }
    }
    for (int i = 0; i < MAX; i++)
    {
        if (fscanf(fileB, "%d", &vetB[i]) == EOF)
        {
            vetB[i] = -1;
        }
    }

    fclose(fileA);
    fclose(fileB);

    // exibindo vetores
    printf("\nConjunto A: (");
    for (int i = 0; i < MAX; i++)
    {
        if (vetA[i] != -1)
            printf(" %d ", vetA[i]);
    }
    printf(")\n\n");
    printf("Conjunto B: (");
    for (int i = 0; i < MAX; i++)
    {
        if (vetB[i] != -1)
            printf(" %d ", vetB[i]);
    }
    printf(")\n\n");

    // inicializando vetor interseção
    for (int i = 0; i < MAX; i++)
    {
        intersecao[i] = -1;
    }
    // operação união
    for (int i = 0; i < MAX; i++)
    {
        uniao[i] = vetA[i];
    }
    for (int i = 0; i < MAX; i++)
    {
        uniao[i + MAX] = vetB[i];
    }
    for (int i = 0; i < (MAX + MAX); i++)
    {
        for (int j = i + 1; j < (MAX + MAX); j++)
        {
            if (uniao[i] == uniao[j] && uniao[i] != -1)
            {
                intersecao[i] = uniao[j]; // separando interseção
                uniao[j] = -1;
            }
        }
    }
    // operação simetria
    for (int i = 0; i < MAX + MAX; i++)
    {
        simetriaAB[i] = uniao[i];
    }
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (intersecao[i] == simetriaAB[j])
            {
                simetriaAB[j] = -1;
            }
        }
    }
    // operação diferença
    for (int i = 0; i < MAX + MAX; i++)
    {
        difBA[i] = uniao[i];
    }
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (vetA[i] == difBA[j])
            {
                difBA[j] = -1;
            }
        }
    }
    do
    {
        printf("************* MENU **************\n");
        printf("...Escolha uma operacao...\n");
        printf("1 - União dos conjuntos\n");
        printf("2 - Intersecao dos conjuntos\n");
        printf("3 - Simetria dos conjuntos\n");
        printf("4 - Diferenca entre os conjuntos\n");
        printf("5 - Par ordenado dos conjuntos\n");
        printf("6 - Sair\n");
        printf("**********************************\n");
        scanf("%d", &num);
        if (num == 1)
        {
            // exibindo união
            printf("\nUniao de A e B: ");
            printf("(");
            for (int i = 0; i < (MAX + MAX); i++)
            {
                if (uniao[i] != -1)
                    printf(" %d ", uniao[i]);
            }
            printf(")\n\n");
        }
        if (num == 2)
        {
            // exibindo interseção
            printf("\nIntersecao de A e B: ");
            printf("(");
            for (int i = 0; i < MAX; i++)
            {
                if (intersecao[i] != -1)
                    printf(" %d ", intersecao[i]);
            }
            printf(")\n\n");
        }
        if (num == 3)
        {
            // exibindo simetria
            printf("\nSimetria entre A e B:\n");
            printf("(");
            for (int i = 0; i < (MAX + MAX); i++)
            {
                if (simetriaAB[i] != -1)
                    printf(" %d ", simetriaAB[i]);
            }
            printf(")\n\n");
        }
        if (num == 4)
        {
            // exibindo diferença
            printf("\nB - A:\n");
            printf("(");
            for (int i = 0; i < (MAX + MAX); i++)
            {
                if (difBA[i] != -1)
                    printf(" %d ", difBA[i]);
            }
            printf(")\n\n");
        }
        if (num == 5)
        {
            // operando e exibindo os pares ordenados
            printf("\nPares Ordenados:\n");
            printf("{");
            for (int i = 0; i < MAX; i++)
            {
                if (vetA[i] != -1)
                {
                    for (int j = 0; j < MAX; j++)
                    {
                        if (vetB[j] != -1)
                        {
                            printf("\n(%d, %d)", vetA[i], vetB[j]);
                        }
                    }
                }
            }
            printf("}\n\n");
        }
        if (num > 5 || num < 1)
        {
            printf("...saindo...\n");
        }

    } while (num > 0 && num < 6);

    return 0;
}