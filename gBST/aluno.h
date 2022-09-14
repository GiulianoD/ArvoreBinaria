#ifndef ALUNO_H_
#define ALUNO_H_

#include "func/aluno.c"

Aluno *criaAluno(int mat, char *nome, float nota);
int compara(void* a, void* b);
void imprimeElemento(void* a);

#endif