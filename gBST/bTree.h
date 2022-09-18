#ifndef BTREE_H_
#define BTREE_H_

#include "func/bTree.c"

int iniciaArvore(Controle **ctrl, size_t tamanho, int (*compara) (void*,void*), void (*imprimeElemento) (void*), void (*imprimeElementoF) (void*,void*));
int addNo(Controle *ctrl, void *dados);
void imprimeArvEmOrdem(Controle *ctrl);
void imprimeArvEmNivel(Controle *ctrl);
int editaNo(Controle *ctrl, void *encontra, void *novosDados);
int deletaNo(Controle *ctrl, void *remov);
int totalNo(No *raiz);
int alturaNo(No *raiz);
int encontraNo(Controle *ctrl, void *encontra);
int maiorNo(Controle *ctrl);
int menorNo(Controle *ctrl);
void salvarArvore(Controle *ctrl);
void piorCaso(Controle *ctrl);

#endif
