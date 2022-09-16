#ifndef BTREE_H_
#define BTREE_H_

#include "func/bTree.c"

int iniciaArvore(Controle **ctrl, size_t tamanho, int (*compara) (void*,void*), void (*imprimeElemento) (void*));
int addNo(Controle *ctrl, void *dados);
void imprimeArvEmOrdem(Controle *ctrl);
int editaElemento(Controle *ctrl, void *encontra, void *novosDados);
int deletaNo(Controle *ctrl, void *remov);
int totalElementos(No *raiz);
int alturaElemento(No *raiz);

#endif
