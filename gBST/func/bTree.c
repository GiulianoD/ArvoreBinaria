typedef struct no {
    void *dados;
    struct no *filhoEsq, *filhoDir;
} No;

typedef struct controle {
    No *raiz;
    size_t size; //esta variavel representa o tamanho padrao dos dados a serem guardados por cada no
    int altura;
    int totalNos;
    int (*compara) (void*,void*);
    void (*imprimeElemento) (void*);
} Controle;

int iniciaArvore(Controle **ctrl, size_t tamanho, int (*compara) (void*,void*), void (*imprimeElemento) (void*)){
    (*ctrl) = (Controle *) malloc (sizeof(Controle));
    if (*ctrl == NULL) return 0;

    (*ctrl)->size = tamanho;
    (*ctrl)->totalNos = 0;
    (*ctrl)->raiz = NULL;
    (*ctrl)->compara = compara;
    (*ctrl)->imprimeElemento = imprimeElemento;

    return 1;
}

No *criaNo(Controle *ctrl, void *dados, int *resultado){
    No *novoNo = (No*) malloc (sizeof(No));
    if (!novoNo) *resultado = -1;
    novoNo->dados = malloc(ctrl->size);
    if (!novoNo->dados) *resultado = -1;

    memcpy(novoNo->dados, dados, ctrl->size);
    novoNo->filhoDir = NULL;
    novoNo->filhoEsq = NULL;
    ctrl->totalNos++;
    return novoNo;
}

No *addNoI(Controle *ctrl, No *raiz, void *dados, int *resultado){
    No **noAux = &raiz;
    int resultadoComparacao;
    while (*noAux){
        resultadoComparacao = ctrl->compara((*noAux)->dados,dados);

        if (resultadoComparacao > 0){
            noAux = &(*noAux)->filhoEsq;
        }
        else if (resultadoComparacao < 0){
            noAux = &(*noAux)->filhoDir;
        }
        else if(resultadoComparacao == 0){
            //caso entre aqui, entao a matricula a ser inserida, ja existe na arvore
            return raiz;
        }
    }
    //caso encontre um elemento==NULL, sai do WHILE
    *noAux = criaNo(ctrl, dados, resultado);
    return raiz;
}

No *addNoR(Controle *ctrl, No *no, void *dados, int *resultado){//criada a funcao recursiva para testes
    if (!no){
        return criaNo(ctrl, dados, resultado);
    }

    if (ctrl->compara(no->dados,dados) > 0){
        no->filhoEsq = addNoR(ctrl, no->filhoEsq, dados, resultado);
    }
    else if (ctrl->compara(no->dados,dados) < 0){
        no->filhoDir = addNoR(ctrl, no->filhoDir, dados, resultado);
    }

    return no;
}

int addNo(Controle *ctrl, void *dados){
    int resultado = 0;
    //ctrl->raiz = addNoR(ctrl, ctrl->raiz, dados, &resultado);
    ctrl->raiz = addNoI(ctrl, ctrl->raiz, dados, &resultado);
    return resultado;
}

void imprimeArvEmOrdemPt2(Controle *ctrl, No *elemento){
    if (!elemento) return;
    imprimeArvEmOrdemPt2(ctrl, elemento->filhoEsq);
    ctrl->imprimeElemento(elemento->dados);
    imprimeArvEmOrdemPt2(ctrl, elemento->filhoDir);
}

void imprimeArvEmOrdem(Controle *ctrl){
    imprimeArvEmOrdemPt2(ctrl, ctrl->raiz);
}

int editaElemento(Controle *ctrl, void *encontra, void *novosDados){
    No *noAux = ctrl->raiz;
    int comparado;

    while (noAux){
        comparado = ctrl->compara(noAux->dados, novosDados);

        if (comparado == 0){
            memcpy(novosDados, noAux->dados, ctrl->size);
            return 0;
        }
        if(comparado < 0) noAux = noAux->filhoDir;
        else              noAux = noAux->filhoEsq;
    }
    return -1;
}

No *deletaNoR(Controle *ctrl, No *arvore, void *remov, No *pai, int *resultado){
    if(!arvore) return NULL;

    No *arvoreAux = arvore;

    int compara = ctrl->compara(arvore->dados, remov);

    if      (compara < 0) arvore->filhoDir = deletaNoR(ctrl, arvore->filhoDir, remov, arvore, resultado);
    else if (compara > 0) arvore->filhoEsq = deletaNoR(ctrl, arvore->filhoEsq, remov, arvore, resultado);
    else{
        resultado = 0;
        if (arvore->filhoEsq == NULL){
            arvoreAux = arvore->filhoDir;
            free(arvore);
            arvore = NULL;
            ctrl->totalNos--;
            return arvoreAux;
        }
        if (arvore->filhoDir == NULL){
            arvoreAux = arvore->filhoEsq;
            free(arvore);
            arvore = NULL;
            ctrl->totalNos--;
            return arvoreAux;
        }
        No *pontoMinimo = arvore->filhoDir;
        while (pontoMinimo->filhoEsq) pontoMinimo = pontoMinimo->filhoEsq;
        arvore->dados = pontoMinimo->dados;
        arvore->filhoDir = deletaNoR(ctrl, arvore->filhoDir, arvore->dados, arvore, resultado);
    }
    return arvore;
}

int deletaNo(Controle *ctrl, void *remov){
    int resultado = 0;
    ctrl->raiz = deletaNoR(ctrl, ctrl->raiz, remov, ctrl->raiz, &resultado);
    return resultado;
}

int totalElementos(No *raiz){
	if (!raiz) return 0;
	return 1 + totalElementos(raiz->filhoEsq) + totalElementos (raiz->filhoDir);
}

int alturaElemento(No *raiz){
	if (!raiz) return 0;

	int alturaE = alturaElemento(raiz->filhoEsq);
	int alturaD = alturaElemento(raiz->filhoDir);

	if (alturaE > alturaD)
		return 1 + alturaE;
	return 1 + alturaD;
}

void maiorElemento(){

}

void menorElemento(){

}
