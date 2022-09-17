typedef struct aluno
{
	int matricula;
    char *nome;
    int nota;
}Aluno;

Aluno *criaAluno(int mat, char *nome, int nota){
    Aluno *novoAluno = (Aluno *) malloc (sizeof(Aluno));

    novoAluno->matricula = mat;
    novoAluno->nome = malloc(30);
    strcpy(novoAluno->nome, nome);
    novoAluno->nota = nota;

    return novoAluno;
}

int compara(void* a, void* b){
	Aluno *a1= (Aluno*) a;
    Aluno *a2= (Aluno*) b;
	return a1->matricula - a2->matricula;
}

void imprimeNo(void* a){
    Aluno *a1= (Aluno*) a;
    printf("Estudante: %s\n", a1->nome);
    printf("Matricula: %d\n", a1->matricula);
    printf("Nota: %d\n", a1->nota);
}