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

+-------------------------------------------------------------------+
|	Limites das estruturas																						|
+-------------------------------------------------------------------+
*/

#define TAM_TSIMB 100 
#define TAM_PSEMA 100 


/*
+-------------------------------------------------------------------+
|	Variáveis Globais																									|
+-------------------------------------------------------------------+
*/

int TOPO_TSIMB	= 0;
int TOPO_PSEMA	= 0;
int ROTULO	= 0;
int CONTA_VARS	= 0;
int POS_SIMB;

int aux;
int numLinha = 1;
char atomo[30];



/*
+-------------------------------------------------------------------+
|	Rotina trata erro																									|
+-------------------------------------------------------------------+
*/

void ERRO(char *msg,...){
	char formato [255];
	va_list arg;
	va_start (arg, msg);
	sprintf(formato, "\n%d: ", numLinha);
	strcat(formato, msg);
	strcat(formato, "\n\n");
	printf("\nERRO no programa");
	vprintf(formato, arg);
	va_end(arg);
	exit(1);
}




/*
+-------------------------------------------------------------------+
|	Tabela de Simbolos																								|
+-------------------------------------------------------------------+
*/



struct elem_tab_simbolos {
	char id[30];
	int desloca;
} TSIMB[TAM_TSIMB], elem_tab;




/*
+-------------------------------------------------------------------+
|	Pilha semantica																										|
+-------------------------------------------------------------------+
*/


int PSEMA[TAM_PSEMA];


/*
+-------------------------------------------------------------------+
|	Funcao que BUSCA um simbolo na tabela de simbolos.								|
|								RETORNA -1 se o simbolo nao esta na tabela					|
|		   RETORNA i, onde i é o indice do simbolo na tabela						|
|							 se o simbolo esta na tabela													|
+-------------------------------------------------------------------+
*/


int busca_simbolo(char *ident){
	int i = TOPO_TSIMB - 1;
	for(;strcmp(TSIMB[i].id, ident) && i >=0; i--);
	return i;
}



/*
+-------------------------------------------------------------------+
|	Funcao que INSERE um simbolo na tabela de simbolos.								|
|		Se ja existe um simbolo com mesmo nome e mesmo nivel						|
|		uma mensagem de erro é apresentada e o programa é interrompido	|								
+-------------------------------------------------------------------+
*/


void insere_simbolo (struct elem_tab_simbolos *elem){ 

	if(TOPO_TSIMB == TAM_TSIMB) {
		ERRO("OVERFLOW - Tabela de simbolos");
	}else{
		POS_SIMB = busca_simbolo(elem->id);
		if(POS_SIMB != -1){
			ERRO("Identificador [%s] duplicado", elem->id);
		}
		TSIMB [TOPO_TSIMB] = *elem;
		TOPO_TSIMB++;
	}
}


/*
+-------------------------------------------------------------------+
|	Funcao de insercao de uma varaivel na tabela de simbolosos				|
+-------------------------------------------------------------------+
*/

void insere_variavel(char *ident){
	strcpy(elem_tab.id, ident);
	elem_tab.desloca = CONTA_VARS;
	insere_simbolo(&elem_tab);
}


/*
+-------------------------------------------------------------------+
|	Rotinas para manutencao de PILHA SEMANTICA												|
+-------------------------------------------------------------------+
*/

void empilha(int n){
	if(TOPO_PSEMA == TAM_PSEMA){
		ERRO("OVERFLOW - Pilha Semantica");
	}
	PSEMA[TOPO_PSEMA++] = n;
}

int desempilha(){
	if(TOPO_PSEMA == 0){
		ERRO("UNDERFLOW - PIlha Semantica");
	}
	return PSEMA[--TOPO_PSEMA];
}


