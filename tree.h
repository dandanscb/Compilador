/*
+−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−+
|		UNIFAL−Universidade Federal de Alfenas.							|
|		BACHARELADO EM CIENCIA DA COMPUTACAO.								|
|Trabalho . . : PARTE 1 − Construcao  Arvore  Sintatica |
|Disciplina .	: Compiladores 														|
|Professor . .: Luiz  Eduardo da  Silva									|	
|Aluno . . .  : Daniel de Andrade Escobar								|
|Data . . . . : 14/02/2019															|
+−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−+
*/

typedef struct no *ptno; 
struct no {
	int tipo;
	char* valor;
	ptno filho, irmao;
};

ptno criaNo (int, char *);
void adicionaFilho (ptno, ptno);
