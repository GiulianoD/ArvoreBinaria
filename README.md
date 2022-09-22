# GenericBST
Generic Binary Search Tree em C

Repositório criado para salvar o trabalho proposto por meu professor victoriocarvalho durante a disciplina de Técnicas de Programação Avançada, durante o semestre 2022/2.

Sobre o código:
Como a árvore genérica aceita qualquer tipo de dado, criei a biblioteca "aluno" para seguir o modelo de dados previamente proposto, contendo o formato da estrutura a ser guardada (struct aluno) e as funções<br/>
  • criaAluno(int,char*,int) : retorna um ponteiro de estrutura do tipo Aluno contendo os dados passados como parametro;<br/>
  • compara(void*,void*) : retorna o resultado da comparação entre as variáveis 'matricula' de duas estruturas de Aluno;<br/>
  • imprimeElemento(void*) :  imprime as informações referentes à estrutura Aluno passada como parâmetro.

P.S.: o arquivo .java presente no repositório é o programa de criação de arquivos de teste (@author victoriocarvalho). Todo o resto do projeto está feito em C.
