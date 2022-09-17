#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bTree.h"
#include "aluno.h"

FILE *abreArq(char *path, char *modo);
Controle *leArquivo(Controle *ctrl, char *arqNome);
/*
Após a leitura e construção da árvore em memória seu programa deve exibir um menu dando as seguintes opções:

Exibir estatísticas – Deve exibir a quantidade total de elementos, a altura da árvore, o maior e o menor elemento e o pior caso de busca.
Efetuar busca por matrícula: o programa solicitará a matrícula do aluno, buscará o aluno e imprimirá na tela os dados do aluno (se encontrado) e a quantidade de elementos que foram percorridos até encontrá-lo.  
Excluir por matrícula: o programa solicitará uma matrícula e excluíra o aluno, imprimindo na tela os dados do aluno excluído ou uma mensagem falando que não o encontrou.
Incluir aluno: o programa solicitará matrícula, nome e nota do aluno e o incluirá na árvore.
Sair: o programa deve percorrer a árvore usando caminhamento "em ordem" e gerar um arquivo em que cada linha apresentará a matrícula, o nome e a nota de um aluno, sempre separados por ;. 

*/
int main(){
    Controle *ctrl;
    iniciaArvore(&ctrl, sizeof(Aluno), compara, imprimeNo);
    ctrl = leArquivo(ctrl, "entradaBalanceada10.txt");

    Aluno *alunoAux = criaAluno(0,"NULL",0);
    alunoAux->matricula = 2000000002;

    deletaNo(ctrl, alunoAux);

    return 0;
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
        //printf("Aluno cadastrado: %s, da matricula: %d, tem a nota %d.\n", nomeAux, matAux, notaAux);
        alunoAux = criaAluno(matAux, nomeAux, notaAux);
        addNo(ctrl, alunoAux);
    }
    //printf("Total de nos aguardados: %d\n", totalEsperadoDeElementos);
    //printf("Total de nos  guardados: %d\n", ctrl->totalNos);
    //printf("Total de nos  da funcao: %d\n", totalNo(ctrl->raiz));
    fclose(arq);
    return ctrl;
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