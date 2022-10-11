#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "func/aluno.h"
#include "func/avl.h"
#include "func/garanteInt.h"

FILE *abreArq(char *path, char *modo);
Controle *leArquivo(Controle *ctrl, char *arqNome, int (*adicionarNo) (Controle*, void*));

//autor https://github.com/GiulianoD
int main(){
    char* entrada = "entradas/entradaAleatoria30000.txt";
    // para armazenar o tempo de execução do código
    double tempoExec;
    clock_t inicioExec, fimExec;

    Controle *ctrl;
    Controle *ctrlAVL;
    //inicia a estrutura de controle de arvore
    iniciaArvore(&ctrl,    sizeof(Aluno), compara, imprimeNo, imprimeNoF);
    iniciaArvore(&ctrlAVL, sizeof(Aluno), compara, imprimeNo, imprimeNoF);

    // primeiro alocamos a arvore nao balanceada
    inicioExec=clock(); //tempo inicial de alocacao de memoria da arvore NAO balanceada
    ctrl = leArquivo(ctrl, entrada, addNo);
    fimExec = clock(); //tempo final de alocacao de memoria da arvore NAO balanceada
    tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC; //converte a diferenca para segundos
    printf("Tempo para alocar a gBST (em segundos): %.4f\n", tempoExec); //imprime quanto tempo levou para executar a acao
    printf("Altura da gBST: %d\n", alturaNo(ctrl->raiz)); //imprime a altura da arvore

    // agora alocamos a balanceada
    inicioExec=clock(); //tempo inicial de alocacao de memoria da arvore NAO balanceada
    ctrlAVL = leArquivo(ctrlAVL, entrada, addNoAVL);
    fimExec = clock(); //tempo final de alocacao de memoria da arvore NAO balanceada
    tempoExec = (double)(fimExec - inicioExec) / CLOCKS_PER_SEC; //converte a diferenca para segundos
    printf("Tempo para alocar a AVL (em segundos): %.4f\n", tempoExec); //imprime quanto tempo levou para executar a acao
    printf("Altura da AVL: %d\n", alturaNo(ctrlAVL->raiz)); //imprime a altura da arvore

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

Controle *leArquivo(Controle *ctrl, char *arqNome, int (*adicionarNo) (Controle*, void*)){
    FILE *arq = abreArq(arqNome,"r");

    Aluno *alunoAux;
    int matAux;
    char *nomeAux = (char*) malloc (30);
    int notaAux;
    int totalEsperadoDeElementos;

    fscanf(arq, "%d\n", &totalEsperadoDeElementos);
    while (fscanf(arq, "%d;%[^;];%d\n", &matAux, nomeAux, &notaAux) != -1){
        alunoAux = criaAluno(matAux, nomeAux, notaAux);
        adicionarNo(ctrl, alunoAux);
    }
    
    fclose(arq);
    return ctrl;
}
