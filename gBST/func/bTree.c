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
    void (*imprimeNo) (void*);
    void (*imprimeNoF) (void*, void*);
} Controle;

int iniciaArvore(Controle **ctrl, size_t tamanho, int (*compara) (void*,void*), void (*imprimeNo) (void*), void (imprimeNoF) (void*,void*)){
    (*ctrl) = (Controle *) malloc (sizeof(Controle));
    if (*ctrl == NULL) return 0;

    (*ctrl)->size = tamanho;
    (*ctrl)->totalNos = 0;
    (*ctrl)->raiz = NULL;
    (*ctrl)->compara = compara;
    (*ctrl)->imprimeNo = imprimeNo;
    (*ctrl)->imprimeNoF = imprimeNoF;

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
            printf("Elemento nao inserido na arvore. Ja existe um No que atende ao criterio desejado.\n");
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

// void imprimeArvEmOrdemI(Controle *ctrl, No *elemento){
//     //No *noAux = ctrl->raiz;
//     No *s = NULL; // ?
//     int emExecucao = 1;

//     while (emExecucao){
//         if (elemento){
            
//             elemento = elemento->filhoEsq;
//         }
//     }
// }

int totalNo(No *raiz){
	if (!raiz) return 0;
	return 1 + totalNo(raiz->filhoEsq) + totalNo(raiz->filhoDir);
}

int alturaNo(No *raiz){
	if (!raiz) return -1;

	int alturaE = alturaNo(raiz->filhoEsq);
	int alturaD = alturaNo(raiz->filhoDir);

	if (alturaE > alturaD)
		return 1 + alturaE;
	return 1 + alturaD;
}

void imprimeArvEmOrdemR(Controle *ctrl, No *elemento){
    if (!elemento) return;
    imprimeArvEmOrdemR(ctrl, elemento->filhoEsq);
    ctrl->imprimeNo(elemento->dados);
    imprimeArvEmOrdemR(ctrl, elemento->filhoDir);
}

void imprimeArvEmOrdem(Controle *ctrl){
    imprimeArvEmOrdemR(ctrl, ctrl->raiz);
}

void imprimeArvEmNivelAux(Controle *ctrl, No *elemento, int nivel){
    if (!elemento) return;
    if (nivel == alturaNo(elemento)){
        ctrl->imprimeNo(elemento->dados);
        return;
    }
    imprimeArvEmNivelAux(ctrl, elemento->filhoEsq, nivel);
    imprimeArvEmNivelAux(ctrl, elemento->filhoDir, nivel);
}

void imprimeArvEmNivel(Controle *ctrl){
    int nivel = alturaNo(ctrl->raiz);
    for (; nivel > 0; nivel--)
        imprimeArvEmNivelAux(ctrl, ctrl->raiz, nivel);
}

int encontraNo(Controle *ctrl, void *encontra){
    int resultado = 0;
    int distancia = 0;
    int comparado;
    No *noAux = ctrl->raiz;

    while (noAux){
        comparado = ctrl->compara(noAux->dados, encontra);

        if (comparado ==0){
            printf("%d Elementos foram percorridos para encontrar o elemento:\n", distancia);
            ctrl->imprimeNo(noAux->dados);
            return 1;
        }
        if (comparado > 0) noAux = noAux->filhoEsq;
        else               noAux = noAux->filhoDir;
        distancia++;
    }
    printf("Nao foi encontrado nenhum No que atendesse ao criterio de busca.\n");
    return -1;
}

int editaNo(Controle *ctrl, void *encontra, void *novosDados){
    No *noAux = ctrl->raiz;
    int comparado;

    while (noAux){
        comparado = ctrl->compara(noAux->dados, encontra);

        if (comparado == 0){
            memcpy(novosDados, noAux->dados, ctrl->size);
            return 0;
        }
        if(comparado < 0) noAux = noAux->filhoDir;
        else              noAux = noAux->filhoEsq;
    }
    return -1;
}

No *deletaNoI(Controle *ctrl, No *raiz, void *remov, int *resultado){
    if(!raiz) return NULL;
    No *noAux = raiz;
    No *noPai = NULL;

    int result = ctrl->compara(noAux->dados, remov);
    
    while (noAux && result) {
        noPai = noAux;
        if (result > 0)
            noAux = noAux->filhoEsq;
        else
            noAux = noAux->filhoDir;
        if (noAux)
            result = ctrl->compara(noAux->dados, remov);
    }
 
    if (!noAux) {
        //se chegou aqui, nao encontrou o No a ser removido
        printf("Nao foi encontrado nenhum No com o criterio de exclusao.\n");
        return raiz;
    }
    //se chegou aqui, entao encontrou o no a ser deletado
    //agora precisamos saber quantos filhos ele tem
    resultado = 0;
    printf("Dados do aluno excluido:\n");
    ctrl->imprimeNo(noAux->dados);
    ctrl->totalNos--;
    if (!noAux->filhoEsq || !noAux->filhoDir) {
        No *noNovo;
        if (!noAux->filhoEsq)
            noNovo = noAux->filhoDir;
        else
            noNovo = noAux->filhoEsq;
        if (noPai == NULL)
            return noNovo;
 
        if (noAux == noPai->filhoEsq)
            noPai->filhoEsq = noNovo;
        else
            noPai->filhoDir = noNovo;

        free(noAux);
        noAux = NULL;
    }

    //se chegou aqui, entao o No a ser deletado tem 2 filhos
    else {
        No *paiTemp = NULL;
        No *noTemp;

        noTemp = noAux->filhoDir;
        while (noTemp->filhoEsq) {
            paiTemp = noTemp;
            noTemp = noTemp->filhoEsq;
        }
 
        if (paiTemp)
            paiTemp->filhoEsq = noTemp->filhoDir;
 
        else
            noAux->filhoDir = noTemp->filhoDir;
 
        noAux->dados = noTemp->dados;
        free(noTemp);
        noTemp = NULL;
    }
    return raiz;
}

No *deletaNoR(Controle *ctrl, No *arvore, void *remov, int *resultado){
    if(!arvore) return NULL;

    No *arvoreAux = arvore;

    int compara = ctrl->compara(arvore->dados, remov);
    int aindaFaltaRemover = 1;

    if      (compara < 0) arvore->filhoDir = deletaNoR(ctrl, arvore->filhoDir, remov, resultado);
    else if (compara > 0) arvore->filhoEsq = deletaNoR(ctrl, arvore->filhoEsq, remov, resultado);
    else if (compara == 0) {
        if (aindaFaltaRemover){
            aindaFaltaRemover=0;
            printf("Dados do aluno excluido:\n");
            ctrl->imprimeNo(arvore->dados);
        }
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
        arvore->filhoDir = deletaNoR(ctrl, arvore->filhoDir, arvore->dados, resultado);
    }
    return arvore;
}

int deletaNo(Controle *ctrl, void *remov){
    int resultado = 0;
    ctrl->raiz = deletaNoI(ctrl, ctrl->raiz, remov, &resultado);
    return resultado;
}

int maiorNo(Controle *ctrl){
    No *noAux = ctrl->raiz;
    if (!noAux) return -1;
    while (noAux->filhoDir) noAux = noAux->filhoDir;
    printf("Dados do maior No encontrado:\n");
    ctrl->imprimeNo(noAux->dados);
    return 1;
}

int menorNo(Controle *ctrl){
    No *noAux = ctrl->raiz;
    if (!noAux) return -1;
    while (noAux->filhoEsq) noAux = noAux->filhoEsq;
    printf("Dados do menor No encontrado:\n");
    ctrl->imprimeNo(noAux->dados);
    return 1;
}

void salvarArvoreR(Controle *ctrl, No *elemento, FILE *fp){
    if (!elemento) return;
    salvarArvoreR(ctrl, elemento->filhoEsq, fp);
    ctrl->imprimeNoF(elemento->dados, fp);
    salvarArvoreR(ctrl, elemento->filhoDir, fp);
}

void salvarArvore(Controle *ctrl){
    No *noAux = ctrl->raiz;
    FILE *fp = fopen("arvore.txt","w");
    fprintf(fp, "%d\n", ctrl->totalNos);
    salvarArvoreR(ctrl, ctrl->raiz, fp);
    fclose(fp);
}

void piorCasoR(Controle *ctrl, No *elemento, int alturaMax, int alturaAtual, int *encontrou){
    if(alturaAtual ==alturaMax){
        //encontrou o pior caso
        printf("Dados do pior caso:\n");
        ctrl->imprimeNo(elemento->dados);
        *encontrou = 1;
        return;
    }
    
    if (elemento->filhoEsq)
        piorCasoR(ctrl, elemento->filhoEsq, alturaMax, alturaAtual+1, encontrou);
    
    if (*encontrou) return;
    
    if (elemento->filhoDir)
        piorCasoR(ctrl, elemento->filhoDir, alturaMax, alturaAtual+1, encontrou);

}

void piorCaso(Controle *ctrl){
    int encontrou = 0;
    piorCasoR(ctrl, ctrl->raiz, alturaNo(ctrl->raiz), 1, &encontrou);
}
