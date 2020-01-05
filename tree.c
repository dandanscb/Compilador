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

ptno criaNo(int tipo, char* valor){
	ptno n = (ptno) malloc (sizeof(struct no));
	n->valor = (char *) malloc (strlen(valor)*sizeof(char)+1);
	n->tipo = tipo;
	strcpy(n->valor, valor);
	n->filho = NULL;
	n->irmao = NULL;
	return n;
}

void adicionaFilho(ptno pai, ptno filho){
	if(filho){
		filho->irmao = pai->filho;
		pai->filho = filho;	
	}
}

void mostra(ptno raiz){
	ptno p;
	switch(raiz->tipo){
		case T_PROGRAMA:					printf("\tn%p [label = \" programa | %s\"];\n", raiz, raiz->valor); break;
		case T_IDENTIF: 					printf("\tn%p [label = \" identificador | %s\"];\n", raiz, raiz->valor); break;
		case T_DECLARACAO_VARIAVEL:	printf("\tn%p [label = \" declaracao de variaveis | %s\"];\n", raiz, raiz->valor); break;
		case T_LISTA_VARIAVEL:			printf("\tn%p [label = \" lista variaveis | %s\"];\n", raiz, raiz->valor); break;
		case T_LISTA_COMANDO:				printf("\tn%p [label = \" lista comandos | %s\"];\n", raiz, raiz->valor); break;
		case T_LEIA:    					printf("\tn%p [label = \" leitura | %s\"];\n", raiz, raiz->valor); break;  
		case T_ESCREVA: 					printf("\tn%p [label = \" escrita | %s\"];\n", raiz, raiz->valor); break;  
		case T_ENQTO:   					printf("\tn%p [label = \" repeticao | %s\"];\n", raiz, raiz->valor); break;  
		case T_SE:      					printf("\tn%p [label = \" selecao | %s\"];\n", raiz, raiz->valor); break; 
		case T_ATRIB:   					printf("\tn%p [label = \" atribuicao | %s\"];\n", raiz, raiz->valor); break;  
		case T_VEZES:   					printf("\tn%p [label = \" multiplica | %s\"];\n", raiz, raiz->valor); break;  
		case T_DIV:     					printf("\tn%p [label = \" divisao | %s\"];\n", raiz, raiz->valor); break;  
		case T_MAIS:    					printf("\tn%p [label = \" soma | %s\"];\n", raiz, raiz->valor); break;  
		case T_MENOS:   					printf("\tn%p [label = \" subtrai | %s\"];\n", raiz, raiz->valor); break;  
		case T_MAIOR:   					printf("\tn%p [label = \" compara maior | %s\"];\n", raiz, raiz->valor); break;  
		case T_MENOR:   					printf("\tn%p [label = \" compara menor | %s\"];\n", raiz, raiz->valor); break;  
		case T_IGUAL:   					printf("\tn%p [label = \" compara igual | %s\"];\n", raiz, raiz->valor); break;  
		case T_E:       					printf("\tn%p [label = \" conjuncao | %s\"];\n", raiz, raiz->valor); break;  
		case T_OU:      					printf("\tn%p [label = \" dinjuncao | %s\"];\n", raiz, raiz->valor); break;  
		case T_V:       					printf("\tn%p [label = \" | %s\"];\n", raiz, raiz->valor); break;  
		case T_F:       					printf("\tn%p [label = \" | %s\"];\n", raiz, raiz->valor); break;  
		case T_NUMERO:  					printf("\tn%p [label = \" numero | %s\"];\n", raiz, raiz->valor); break;  
		case T_NAO:     					printf("\tn%p [label = \" negacao (NAO) | %s\"];\n", raiz, raiz->valor); break;  
		case T_ABRE:    					printf("\tn%p [label = \" | %s\"];\n", raiz, raiz->valor); break;  
		case T_FECHA:   					printf("\tn%p [label = \" | %s\"];\n", raiz, raiz->valor); break;  
		case T_LOGICO:  					printf("\tn%p [label = \" tipo | %s\"];\n", raiz, raiz->valor); break;  
		case T_INTEIRO: 					printf("\tn%p [label = \" tipo | %s\"];\n", raiz, raiz->valor); break; 
		case T_LER_STRING:				printf("\tn%p [label = \" texto | %s\"];\n", raiz, raiz->valor); break;
		case T_VARIAVEL:					printf("\tn%p [label = \" variavel | %s\"];\n", raiz, raiz->valor); break;
	}
	p = raiz->filho;
	while(p) {
		mostra(p);
		p = p->irmao;
	}
	/*TBD ligacoes de pais com filhos*/
}

void mostraArvore(ptno raiz){
	ptno filho = raiz->filho;
	while(filho){
		printf("\tn%p -> n%p;\n", raiz, filho);	
		mostraArvore(filho);
		filho = filho->irmao;
	}
}

