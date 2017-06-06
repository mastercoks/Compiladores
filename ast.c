#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*

Construir a árvore abstrata da rotina abaixo e realizar a avaliação da mesma

	read coks;
	coks = 3;

printf("%s", r->valor);
printf(";\n");



						     program
					      	 /
								stmt_seq
						   /			\
				stmt_seq			stmt
					/						 /
				stmt				  /
				 /					 /
		 read_stmt		assign_stmt
		 	 /		\				/    \
		T_READ	T_ID	 T_ID   exp
													 /
											simple_exp
													/
											termo
								  			/
										 fator
									  	/
									 T_NUM

*/

// define os tokens terminais
//typedef enum TOKEN { T_IF, T_THEN, T_ENDIF, T_WHILE, T_DO, T_ENDDO, T_READ, T_WRITE, T_MENOR, T_MAIOR, T_IGUAL, T_ABREP, T_FECHAP, T_ADD, T_SUB, T_MULT, T_DIV, T_ATRIB, T_PeV, T_ID, T_NUM }
//tipoTOKEN;

//define os tipos de nó (agrupando terminais)
//se mudanças se confirmarem: adicionar tokens das rotinas auxiliares
typedef enum NO { TERMINAL, PROGRAM, STMT_SEQ, STMT, IF_STMT, WHILE_STMT, ASSIGN_STMT, READ_STMT, WRITE_STMT, EXP, SIMPLE_EXP, TERMO, FATOR }
	tipoNO;

/*
* define o tipo nó
* esq: filho esquerdo
* dir: filho direito
* tipo_no = define regras de produção (nós)
* valor = valor do nó (a ser impresso quando estourado)
* tipo_token = tipo dos tokens terminais
*/
struct no {
	struct no * esq;
	struct no * dir;
	tipoNO tipo_no;
	char *valor;
	//tipoTOKEN tipo_token;
};

//inicializando funções
struct no * criaNoTerminal(char *valor);
struct no * criaNoNaoTerminal(struct no * e, tipoNO n, char *v, struct no * d);
char* analisaExpr(struct no *raiz);

//construtor
struct no * criaNoTerminal(char *v){
	struct no * novoTERM = (struct no*) malloc(sizeof(struct no));

	novoTERM->dir = NULL;
	novoTERM->esq = NULL;
	novoTERM->tipo_no = TERMINAL;
	novoTERM->valor = v;

	return novoTERM;
}

//construtor
struct no * criaNoNaoTerminal(struct no * e, tipoNO n, char *v, struct no * d){
	struct no * novoNAO_TERM = (struct no*) malloc(sizeof(struct no));

	novoNAO_TERM->dir = d;
	novoNAO_TERM->esq = e;
	novoNAO_TERM->tipo_no = n;
	novoNAO_TERM->valor = v;

	return novoNAO_TERM;
}

char *concat(char* s1, char* s2){
    char *ns = malloc(strlen(s1) + strlen(s2) + 1);
    ns[0] = '\0';
    strcat(ns, s1);
    strcat(ns, s2);
    return ns;
}

//*char ao inves de int?
char* analisaExpr (struct no *r) {
		switch (r->tipo_no) {
			case TERMINAL:
				return (r->valor);
			case PROGRAM:
				return concat(analisaExpr(r->esq), r->valor);
			case STMT_SEQ:
				if (!strncmp(r->valor, ";\n",1)) {
					return concat(concat(analisaExpr(r->esq), r->valor), analisaExpr(r->dir));
					}
					else {
						return (analisaExpr(r->esq));
					}

			case STMT:
				return (analisaExpr(r->esq));

			//case if a discutir com coqueiro
			//case if_stmt:		{return (analisaExpr(r->esq) + r->valor);}

			//case while a discutir com coqueiro
			//case while_stmt	{return (analisaExpr(r->esq) + r->valor);}

			case ASSIGN_STMT:
				return concat(concat(analisaExpr(r->esq), r->valor),analisaExpr(r->dir));
			case READ_STMT:
				return concat(analisaExpr(r->esq), analisaExpr(r->dir));
			case WRITE_STMT:
				return concat(analisaExpr(r->esq), analisaExpr(r->dir));
			case EXP:
				if (!strncmp(r->valor, "",0)) {
					return (analisaExpr(r->esq));
				}
				else {
					return concat(concat(analisaExpr(r->esq), r->valor),analisaExpr(r->dir));
				}

			case SIMPLE_EXP:
				if (!strncmp(r->valor, "",0)) {
					return (analisaExpr(r->esq));
				}
				else {
					return concat(concat(analisaExpr(r->esq), r->valor),analisaExpr(r->dir));
				}

			case TERMO:
				if (!strncmp(r->valor, "",0)) {
					return (analisaExpr(r->esq));
				}
				else {
					return concat(concat(analisaExpr(r->esq), r->valor),analisaExpr(r->dir));
				}


			//case fator a ser discutido com coqueiro
			case FATOR:				{
				return (analisaExpr(r->esq));
			}

			default:
				exit(0);
				break;
		} //fim do swtich
}
