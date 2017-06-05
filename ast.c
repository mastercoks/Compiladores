novoTERM#include <stdio.h>
#include <stdlib.h>


/*

Implementar a Árvore de Sintaxe Abstrata da gramática abaixo:

	E -> E + T | T
	T -> T * F | F
	F -> D
	D -> 0 | 1 | ... | 9

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
typedef enum TOKEN { T_IF, T_THEN, T_ENDIF, T_WHILE, T_DO, T_ENDDO, T_READ, T_WRITE, T_MENOR, T_MAIOR, T_IGUAL, T_ABREP, T_FECHAP, T_ADD, T_SUB, T_MULT, T_DIV, T_ATRIB, T_PeV, T_ID, T_NUM }
tipoTOKEN;

//define os tipos de nó (agrupando terminais)
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
	*char valor;
	tipoTOKEN tipo_token;
};

//inicializando funções
struct no * criaNoTerminal(*char valor);
struct no * criaNoNaoTerminal(struct no * e, tipoOPERACAO o, struct no * d);
int analisaExpr(struct no *raiz);

//construtor
struct no * criaNoTerminal(*char v, tipoTOKEN t){
	struct no * novoTERM = (struct no*) malloc(sizeof(struct no));

	novoTERM->dir = NULL;
	novoTERM->esq = NULL;
	novoTERM->tipo_no = TERMINAL;
	novoTERM->valor = v;
	novoTERM->tipo_token = t;

	return novoTERM;
}

//construtor
struct no * criaNoNaoTerminal(struct no * e, tipoTOKEN t, *char v, struct no * d){
	struct no * novoNAO_TERM = (struct no*) malloc(sizeof(struct no));

	novoNAO_TERM->dir = d;
	novoNAO_TERM->esq = e;
	novoNAO_TERM->tipo_no = NAO_TERMINAL;
	novoNAO_TERM->valor = v;
	novoNAO_TERM->tipo_token = t;

	return novoNAO_TERM;
}

int analisaExpr (struct no *r) {
	if (r->tipo_no == CONSTANTE){
//if (r->tipo_no == TERMINAL){

//}

//else if (r->tipo_no == )
		return r->valor;
	}
	else {
			if (r->operacao == ADD) {
				return (analisaExpr(r->esq) + analisaExpr(r->dir));
			}
			else {
				return (analisaExpr(r->esq) * analisaExpr(r->dir));
			}
		}

	}




int main(){

	struct no * raiz = criaNoOperador(criaNoValor(2), MUL, criaNoValor(200));
	//struct no * raiz =
	//	criaNoOperador(criaNoValor(2), ADD, criaNoOperador((criaNoValor(3)), MUL, criaNoValor(4)));

	printf("%d\n",analisaExpr(raiz));
return 0;
}
