#include <stdio.h>
#include <stdlib.h>


/*

Implementar a Árvore de Sintaxe Abstrata da gramática abaixo:

	E -> E + T | T
	T -> T * F | F
	F -> D
	D -> 0 | 1 | ... | 9

Construir a árvore abstrata da expressão abaixo e realizar a avaliação da mesma

	w = 2 + 3 * 4



		+
	  /   \
	2	   \
			*
		   / \
		  3   4

*/

//define o tipo de operação dos nós operadores (adição ou multiplicação)
typedef enum OP { ADD, MUL, SUB, DIV }
	tipoOPERACAO;

//define o tipo de nó (operador (+*) ou constante (0-9))
typedef enum NO { OPERADOR, CONSTANTE }
	tipoNO;

//

/*
* define o tipo nó
* esq: filho esquerdo
* dir: filho direito
* tipoNO = operador ou constante
* valor = valor do nó (constante)
* tipoOPERACAO = tipo da operaçao (adição ou multiplicação)
*/
struct no {
	struct no * esq;
	struct no * dir;
	tipoNO tipo_no;
	int valor;
	tipoOPERACAO operacao;
};

//inicializando funções
struct no * criaNoValor(int v);
struct no * criaNoOperador(struct no * e, tipoOPERACAO o, struct no * d);
void liberaMemoria(struct no* raiz);
int analisaExpr(struct no *raiz);

//construtor
struct no * criaNoValor(int v){
	struct no * novoCONST = (struct no*) malloc(sizeof(struct no));

	novoCONST->dir = NULL;
	novoCONST->esq = NULL;
	novoCONST->tipo_no = CONSTANTE;
	novoCONST->valor = v;

	return novoCONST;
}

//construtor
struct no * criaNoOperador(struct no * e, tipoOPERACAO o, struct no * d){
	struct no * novoOP = (struct no*) malloc(sizeof(struct no));

	novoOP->dir = d;
	novoOP->esq = e;
	novoOP->tipo_no = OPERADOR;
	novoOP->operacao = o;

	return novoOP;
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
