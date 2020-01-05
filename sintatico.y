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


%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "utils.c"
#include "lexico.c"
#include "tree.c"

int yylex();
void yyerror(char *);

ptno raiz = NULL, pt, ptaux;
int auxiliar;

%}





%start programa 

//terminais
%token T_PROGRAMA
%token T_INICIO
%token T_FIM
%token T_IDENTIF
%token T_LEIA
%token T_ESCREVA
%token T_ENQTO
%token T_FACA
%token T_FIMENQTO
%token T_SE
%token T_ENTAO
%token T_SENAO
%token T_FIMSE
%token T_ATRIB
%token T_VEZES
%token T_DIV
%token T_MAIS
%token T_MENOS
%token T_MAIOR
%token T_MENOR
%token T_IGUAL
%token T_E
%token T_OU
%token T_V
%token T_F
%token T_NUMERO
%token T_NAO
%token T_ABRE
%token T_FECHA
%token T_LOGICO
%token T_INTEIRO
%token T_DECLARACAO_VARIAVEL
%token T_LISTA_VARIAVEL 
%token T_LISTA_COMANDO
%token T_VARIAVEL
%token T_LER_STRING

//Precedencia (da maior para a maior)
%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV


%%

//regras de produção
/*aqui vem as regras da gramatica*/
/*regra --------------------------> semantica*/

programa:
	cabecalho 
	{/*printf("\tINPP\n");*/}
	variaveis
	T_INICIO 
	lista_comandos
	T_FIM
	{/*printf("\tFIMP\n");*/
		printf("digraph{\n");
		printf("\tnode [ shape=record , height =.4];\n");
		raiz = criaNo(T_PROGRAMA, "");	
		adicionaFilho (raiz, $5);		
		adicionaFilho (raiz, $3);
		adicionaFilho (raiz, $1);
		mostra(raiz);
		mostraArvore(raiz);
		printf("}\n");
	}
	;

cabecalho: 
	T_PROGRAMA T_IDENTIF
	{
		pt = criaNo(T_IDENTIF, atomo);
		$$ = pt;
	}
	;

variaveis: 
	/* vazio */
	| declaracao_variaveis
	{
		$$ = $1;
	}
	;
	
declaracao_variaveis:
	declaracao_variaveis
	tipo
	{CONTA_VARS = 0;}
	lista_variaveis
	{
		pt = criaNo(T_DECLARACAO_VARIAVEL, "");
		adicionaFilho (pt, $1);				
		adicionaFilho (pt, $4);
		adicionaFilho (pt, $2);	
		$$ = pt;
	}
	| tipo
	{CONTA_VARS = 0;}
	lista_variaveis
	{
		//printf("\tAMEM\t%d\n", CONTA_VARS);
		pt = criaNo(T_DECLARACAO_VARIAVEL, "");
		adicionaFilho(pt, $1);
		adicionaFilho(pt, $3);
		$$ = pt;
	}
	;
	
tipo: 
	T_LOGICO
	{
		pt = criaNo(T_LOGICO,"logico");
		$$ = pt;
	}
	| T_INTEIRO
	{
		pt = criaNo(T_INTEIRO,"inteiro");
		$$ = pt;
	}
	;

lista_variaveis: 
	lista_variaveis
	T_IDENTIF
	{
		insere_variavel(atomo);
		CONTA_VARS++;
		pt = criaNo(T_LISTA_VARIAVEL, "");
		ptaux = criaNo(T_IDENTIF, atomo);
		adicionaFilho(pt, $1);
		adicionaFilho(pt, ptaux);
		$$ = pt;

	}
	| T_IDENTIF
	{
		insere_variavel(atomo);
		CONTA_VARS++;
		pt = criaNo(T_LISTA_VARIAVEL, "");
		ptaux = criaNo(T_IDENTIF, atomo);
		adicionaFilho(pt, ptaux);
		$$ = pt;
	}
	;
	
lista_comandos:
	{$$ = NULL;} //vazio
	| comando 
	lista_comandos
	{
		pt = criaNo(T_LISTA_COMANDO, "");
		adicionaFilho(pt, $2);
		adicionaFilho(pt, $1);
		$$ = pt;
	}
	;
	
comando: 
	entrada_saida
	{
		$$ = $1;
	}
	| repeticao
	{
		$$ = $1;
	}
	| selecao 
	{
		$$ = $1;
	}
	| atribuicao
	{
		$$ = $1;
	}
	;
	
entrada_saida: 
	leitura
	{
		$$ = $1;
	}
	| escrita
	{
		$$ = $1;
	}
	;

leitura: 
	T_LEIA
	T_IDENTIF
	{
	  	pt = criaNo(T_LEIA, "");
		ptaux = criaNo(T_IDENTIF, atomo);
		adicionaFilho(pt, ptaux);
		$$ = pt;
	}
	;

escrita:
	T_ESCREVA 
	expressao
	{ 
		pt = criaNo(T_ESCREVA, "");
		adicionaFilho(pt, $2);
		$$ = pt;
	}
	;
	
repeticao: 
	T_ENQTO
	expressao 
	T_FACA
	lista_comandos
	T_FIMENQTO
	{
		pt = criaNo(T_ENQTO, "");
		adicionaFilho(pt, $4);
		adicionaFilho(pt, $2);
		$$ = pt;
	}
	;
	
selecao: 
	T_SE 
	expressao
	T_ENTAO
	lista_comandos
	T_SENAO
	lista_comandos
	T_FIMSE
	{
		pt = criaNo(T_SE, "");
		adicionaFilho(pt, $6);
		adicionaFilho(pt, $4);
		adicionaFilho(pt, $2);
		$$ = pt;
	}
	;

atribuicao: 
	T_IDENTIF
	{
		pt = criaNo(T_IDENTIF, atomo);
		$$ = pt;
	}
	T_ATRIB
	expressao
	{
		pt = criaNo(T_ATRIB, "");
		adicionaFilho(pt, $4);
		adicionaFilho(pt, $2);
		$$ = pt;
	}
	;

expressao
	: expressao T_VEZES expressao
	{
		pt = criaNo(T_VEZES, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;		 				
	}
	| expressao T_DIV expressao
	{
		pt = criaNo(T_DIV, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;		 				
	}
	| expressao T_MAIS expressao
	{
		pt = criaNo(T_MAIS, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;		 				
	}
	| expressao T_MENOS expressao
	{
		pt = criaNo(T_MENOS, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;		 				
	}
	| expressao T_MAIOR expressao
	{
		pt = criaNo(T_MAIOR, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;		 				
	}
	| expressao T_MENOR expressao
	{
		pt = criaNo(T_MENOR, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;		 				
	}
	| expressao T_IGUAL expressao
	{
		pt = criaNo(T_IGUAL, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;		 				
	}
	| expressao T_E expressao
	{
		pt = criaNo(T_E, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;
	}
	| expressao T_OU expressao
	{
		pt = criaNo(T_OU, "");
		adicionaFilho(pt, $3);
		adicionaFilho(pt, $1);
		$$ = pt;
	}
	| termo
	{
		$$ = $1;
	}
	;

termo: 
	T_IDENTIF
	{
		pt = criaNo(T_VARIAVEL, atomo);
		$$ = pt;
	}
	| T_NUMERO
	{
		pt = criaNo(T_NUMERO, atomo);
		$$ = pt;
	}
	| T_V
	{
		pt = criaNo(T_V, "");
		$$ = pt;
	}
	| T_F
	{
		pt = criaNo(T_F, "");
		$$ = pt;
	}
	| T_NAO termo
	{
		pt = criaNo(T_NAO, "");
		adicionaFilho(pt, $2);
		$$ = pt;
	}
	| T_ABRE expressao T_FECHA
	{
		$$ = $2;
	}
	| T_LER_STRING
	{
		sprintf(atomo, "_const%d", auxiliar);
		auxiliar++;
		pt = criaNo(T_LER_STRING, atomo);
		$$ = pt;
	}
	;

%%

/*
+-------------------------------------------------------------+
| 		CORPO PRINCIPAL DO PROGRAMA 					 								  |	
+-------------------------------------------------------------+
*/


int yywrap (){
return 1;
}

void yyerror (char *s)
{
	ERRO("ERRO SINTATICO");
}

int main(){
	return yyparse();
}
