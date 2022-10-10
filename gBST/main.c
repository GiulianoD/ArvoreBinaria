#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "func/aluno.h"
#include "func/bTree.h"
#include "func/garanteInt.h"

FILE *abreArq(char *path, char *modo);
Controle *leArquivo(Controle *ctrl, char *arqNome);
int menuOpcoes(int *op);

//autor https://github.com/GiulianoD
int main(){
    // para armazenar o tempo de execução do código
    double tempoExec;
    clock_t inicioExec, fimExec;

    Controle *ctrl;
    //inicia a estrutura de controle de arvore
    iniciaArvore(&ctrl, sizeof(Aluno), compara, imprimeNo, imprimeNoF);

    inicioExec=clock(); //tempo inicial de alocacao de memoria da arvore

    //aloca a arvore na memoria
    ctrl = leArquivo(ctrl, "entradas/entradaAleatoria30000.txt");

    fimExec = clock(); //tempo final de alocacao de memoria da arvore
    tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC; //converte a diferenca para segundos
    printf("Tempo para alocar a arvore (em segundos): %.4f\n", tempoExec); //imprime quanto tempo levou para executar a acao

    //cria as variaveis auxiliares
    Aluno *alunoAux = criaAluno(0,"NULL",0);
    int matAux, notaAux;
    char *nomeAux = malloc(30);
    
    int op;
    do {
        menuOpcoes(&op);
        printf("\n");
        switch (op){
            case 1:
                inicioExec = clock();
                printf("Quantidade total de elementos na arvore: %d\n", ctrl->totalNos);
                printf("Altura da arvore: %d\n", alturaNo(ctrl->raiz));printf("\n");
                if (ctrl->totalNos == 0){
                    printf("A arvore esta vazia.\n");
                    break;
                }
                maiorNo(ctrl);printf("\n");
                menorNo(ctrl);printf("\n");
                piorCaso(ctrl);

                fimExec = clock();
                tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC;
                printf("Tempo de execucao (em segundos): %.4f", tempoExec);
                break;
            case 2:
                inicioExec = clock();

                printf("Digite a matricula do aluno que deseja encontrar na arvore: ");
                alunoAux->matricula = garanteInt();
                encontraNo(ctrl, alunoAux);

                fimExec = clock();
                tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC;
                printf("Tempo de execucao (em segundos): %.4f", tempoExec);
                break;
            case 3:
                inicioExec = clock();

                printf("Digite a matricula do aluno que deseja excluir da arvore: ");
                alunoAux->matricula = garanteInt();
                deletaNo(ctrl, alunoAux);

                fimExec = clock();
                tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC;
                printf("Tempo de execucao (em segundos): %.4f", tempoExec);
                break;
            case 4:
                inicioExec = clock();

                printf("Digite os dados do aluno que deseja incluir.\n");
                printf("Matricula: ");
                matAux = garanteInt();
                printf("Nome: ");
                scanf("%[^\n]", nomeAux);
                printf("Nota: ");
                notaAux = garanteInt();
                addNo(ctrl, criaAluno(matAux, nomeAux, notaAux));

                fimExec = clock();
                tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC;
                printf("Tempo de execucao (em segundos): %.4f", tempoExec);
                break;
            case 0:
                inicioExec = clock();

                salvarArvore(ctrl);

                fimExec = clock();
                tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC;
                printf("Tempo de execucao (em segundos): %.4f", tempoExec);
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
