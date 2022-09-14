#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bTree.h"
#include "aluno.h"

int main(){

    Aluno *eu;
    Controle *ctrlArvre;

    iniciaArvore(&ctrlArvre, sizeof(Aluno), compara, imprimeElemento);

    eu = criaAluno(23, "giuliano", 5);
    addNoR(ctrlArvre, eu);
    eu = criaAluno(10, "giuliano", 5);
    addNoR(ctrlArvre, eu);
    eu = criaAluno(4, "giuliano", 5);
    addNoR(ctrlArvre, eu);
    eu = criaAluno(344, "giuliano", 5);
    addNoR(ctrlArvre, eu);
    eu = criaAluno(2, "giuliano", 5);
    addNoR(ctrlArvre, eu);
    eu = criaAluno(54, "giuliano", 5);
    addNoR(ctrlArvre, eu);
    eu = criaAluno(75, "giuliano", 5);
    addNoR(ctrlArvre, eu);

    imprimeArvEmOrdem(ctrlArvre);

    return 0;
}
