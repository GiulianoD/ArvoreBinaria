#ifndef ALUNO_H_
#define ALUNO_H_

typedef struct aluno
{
	int matricula;
    char *nome;
    int nota;
}Aluno;

#include "aluno.c"

Aluno *criaAluno(int mat, char *nome, int nota);
int compara(void* a, void* b);
void imprimeNo(void* a);
void imprimeNoF(void* a, void *b);

#endif