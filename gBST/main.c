#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"
#include "bTree.h"
#include "garanteInt.c"

FILE *abreArq(char *path, char *modo);
Controle *leArquivo(Controle *ctrl, char *arqNome);
int menuOpcoes(int *op);

int main(){
    Controle *ctrl;
    iniciaArvore(&ctrl, sizeof(Aluno), compara, imprimeNo, imprimeNoF);
    ctrl = leArquivo(ctrl, "entradaBalanceada10.txt");
    //ctrl = leArquivo(ctrl, "entradaBalanceada200000.txt");
    //ctrl = leArquivo(ctrl, "entradaBalanceada800000.txt");
    //ctrl = leArquivo(ctrl, "entradaBalanceada2500000.txt");
    //ctrl = leArquivo(ctrl, "arvore.txt");
    
    imprimeArvEmNivel(ctrl);
    Aluno *alunoAux = criaAluno(0,"NULL",0);
    int matAux, notaAux;
    char *nomeAux = malloc(30);

    int op;
    do {
        menuOpcoes(&op);
        printf("\n");
        switch (op){
            case 1:
                printf("Quantidade total de elementos na arvore: %d\n", ctrl->totalNos);
                printf("Altura da arvore: %d\n", alturaNo(ctrl->raiz));printf("\n");
                maiorNo(ctrl);printf("\n");
                menorNo(ctrl);printf("\n");
                piorCaso(ctrl);
                break;
            case 2:
                printf("Digite a matricula do aluno que deseja encontrar na arvore: ");
                alunoAux->matricula = garanteInt();
                encontraNo(ctrl, alunoAux);
                break;
            case 3:
                printf("Digite a matricula do aluno que deseja excluir da arvore: ");
                alunoAux->matricula = garanteInt();
                deletaNo(ctrl, alunoAux);
                break;
            case 4:
                printf("Digite os dados do aluno que deseja incluir.\n");
                printf("Matricula: ");
                matAux = garanteInt();
                printf("Nome: ");
                scanf("%[^\n]", nomeAux);
                printf("Nota: ");
                notaAux = garanteInt();
                addNo(ctrl, criaAluno(matAux, nomeAux, notaAux));
                break;
            case 0:
                salvarArvore(ctrl);
                break;
            default:
                printf("Digite uma opcao valida.\n");
        }
        printf("\n");
    } while (op);

    return 0;
}

FILE *abreArq(char *path, char *modo){
    FILE *arq;
    arq = fopen(path, modo);

    if (!arq){
        printf("o seguinte arquivo nao foi encontrado encontrado, verifique se o nome esta correto e tente novamente.\n");
        printf("%s\n", path);
        exit(1);
    }
    return arq;
}

Controle *leArquivo(Controle *ctrl, char *arqNome){
    FILE *arq = abreArq(arqNome,"r");
    
    Aluno *alunoAux;
    int matAux;
    char *nomeAux = (char*) malloc (30);
    int notaAux;
    int totalEsperadoDeElementos;

    fscanf(arq, "%d\n", &totalEsperadoDeElementos);
    while (fscanf(arq, "%d;%[^;];%d\n", &matAux, nomeAux, &notaAux) != -1){
        alunoAux = criaAluno(matAux, nomeAux, notaAux);
        addNo(ctrl, alunoAux);
    }
    
    fclose(arq);
    return ctrl;
}

int menuOpcoes(int *op){
    printf("----------------------------------------------\n");
    printf("Menu de opcoes\n");
    printf("1: Exibir estatisticas\n");
    printf("2: Efetuar busca por matrIcula\n");
    printf("3: Excluir por matrIcula\n");
    printf("4: Incluir aluno\n");
    printf("0: Sair\n");
    printf("Digite o valor referente a sua escolha: ");
    *op = garanteInt();
}
