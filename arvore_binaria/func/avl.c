#include "avl.h"

No *rotacaoDireita (No *no){
    No *noRodado = no->filhoEsq;
    No *noAux = noRodado->filhoDir;

    noRodado->filhoDir = no;
    no->filhoEsq = noAux;

    return noRodado;
}

No *rotacaoEsquerda (No *no){
    No *noRodado = no->filhoDir;
    No *noAux = noRodado->filhoEsq;

    noRodado->filhoEsq = no;
    no->filhoDir = noAux;

    return noRodado;
}

int equilibrioAVL(No *no){
    if (!no) return 0; // retorna zero, caso seja um no nulo

    return alturaNo(no->filhoEsq) - alturaNo(no->filhoDir); // retorna positivo, se o lado esquerdo da arvore for mais alto que o lado direito. retorna negativo, caso contrario
}

No *addNoAVL2(Controle *ctrl, No *no, void *dados, int *resultado){//criada a funcao recursiva para testes
    if (!no){
        return criaNo(ctrl, dados, resultado);
    }

    int comparaDadosNo = ctrl->compara(no->dados,dados);

    if (comparaDadosNo > 0){
        no->filhoEsq = addNoAVL2(ctrl, no->filhoEsq, dados, resultado);
    }
    else if (comparaDadosNo < 0){
        no->filhoDir = addNoAVL2(ctrl, no->filhoDir, dados, resultado);
    }
    else { // se entrar neste Else, entao foi encontrado um No na arvore que ja possui o mesmo criterio de insercao
        return no; // retorna o no sem alteracoes
    }

    // se chegou aqui, entao o novo no foi incluso
    // agora, iremos percorrer o caminho de volta (pela recursao) balanceado cada no pai ate chegar na raiz
    int equilibrio = equilibrioAVL (no);

    if (equilibrio > 1){ // caso: lado ESQUERDO for mais alto, sera necessario uma rotacao a direita
        comparaDadosNo = ctrl->compara(dados, no->filhoEsq->dados); // valor positivo caso o dado salvo esteja a direita do filho esquerdo
        if (comparaDadosNo > 0){
            // neste caso, faremos a rotacao esquerda-direita
            no->filhoEsq = rotacaoEsquerda(no->filhoEsq);
        }
        
        return rotacaoDireita(no);
    }

    if (equilibrio < -1){ // caso: lado DIREITO for mais alto, sera necessario uma rotacao a esquerda
        comparaDadosNo = ctrl->compara(dados, no->filhoDir->dados); // valor positivo caso o dado salvo esteja a direita do filho direito
        if (comparaDadosNo < 0){
            // neste caso, faremos a rotacao direita-esquerda
            no->filhoDir = rotacaoDireita(no->filhoDir);
        }

        return rotacaoEsquerda(no);
    }

    // se chegou aqui, entao esta secao da arvore ja esta balanceada
    return no; // retorna o no
}

int addNoAVL(Controle *ctrl, void *dados){
    int resultado = 0;
    ctrl->raiz = addNoAVL2(ctrl, ctrl->raiz, dados, &resultado);
    return resultado;
}
