#ifndef ALUNO_H_
#define ALUNO_H_

#include "func/aluno.c"

Aluno *criaAluno(int mat, char *nome, int nota);
int compara(void* a, void* b);
void imprimeElemento(void* a);

#endif