#include "ast.h"

struct no * criaNoTerminal(char* v){
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = NULL;
	no->tipo_no = TERMINAL;
	no->valor = (char *) malloc(sizeof(char));
	strcpy(no->valor, v);
	no->lista = NULL;

	return no;
}

struct no * criarNoRead(char* v) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = NULL;
	no->tipo_no = READ_STMT;
	no->valor = (char *) malloc(sizeof(char));
	strcpy(no->valor, v);
	no->lista = NULL;

	return no;
}

struct no * criarNoWrite(struct no * esq) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = esq;
	no->tipo_no = WRITE_STMT;
	no->lista = NULL;

	return no;
}

struct no * criarNoOperacao(struct no *esq, tipoNO t, struct no *dir) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->esq = esq;
	no->dir = dir;
	no->tipo_no = t;
	no->lista = NULL;

	return no;
}

struct no * criarNoParenteses(struct no * esq) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = esq;
	no->tipo_no = PARENTESES;
	no->lista = NULL;

	return no;
}

struct no * criarNoAtribuicao(struct no * esq, struct no * dir) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->esq = esq;
	no->dir = dir;
	no->tipo_no = ASSIGN_STMT;
	no->lista = NULL;

	return no;
}

struct no * criarNoIf(struct no * esq, struct lista * lista) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->esq = esq;
	no->tipo_no = IF_STMT;
	no->lista = lista;
	return no;
}

struct no * criarNoWhile(struct no * esq, struct lista * lista) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->esq = esq;
	no->tipo_no = WHILE_STMT;
	no->lista = lista;
	return no;
}

struct lista* criarLista( struct no * no, struct lista * proximo) {
	struct lista * lista = (struct lista*) malloc(sizeof(struct lista));
	struct no * no_tmp = (struct no*) malloc(sizeof(struct no));
	no_tmp = no;
	lista->no = no_tmp;
	lista->proximo = proximo;
	return lista;
}

/*
*	função que percorre a árvore e printa os nós
* entrada: r = nó raiz da árvore
* saida: void
*/
void analisaAST (struct no *r) {
	if(r != NULL) {
		switch (r->tipo_no) {
			case TERMINAL:
				printf("%s", r->valor);
				break;
			case READ_STMT:
				tabular();
				printf("read %s", r->valor); //;\n
				break;
			case WRITE_STMT:
				tabular();
				printf("write ");
				analisaAST(r->esq);
				break;
			case MAIOR:
				analisaAST(r->esq);
				printf(" > ");
				analisaAST(r->dir);
				break;
			case MENOR:
				analisaAST(r->esq);
				printf(" < ");
				analisaAST(r->dir);
				break;
			case IGUAL:
				analisaAST(r->esq);
				printf(" = ");
				analisaAST(r->dir);
				break;
			case ADD:
				analisaAST(r->esq);
				printf(" + ");
				analisaAST(r->dir);
				break;
			case SUB:
				analisaAST(r->esq);
				printf(" - ");
				analisaAST(r->dir);
			case MULT:
				analisaAST(r->esq);
				printf(" * ");
				analisaAST(r->dir);
				break;
			case DIV:
				analisaAST(r->esq);
				break;
				printf(" / ");
				analisaAST(r->dir);
				break;
			case PARENTESES:
				printf("(");
				analisaAST(r->esq);
				printf(")");
				break;
			case ASSIGN_STMT:
				tabular();
				analisaAST(r->esq);
				printf(" := ");
				analisaAST(r->dir);
				break;
			case IF_STMT:
				tabular();
			 	printf("if ");
				analisaAST(r->esq);
				printf(" then\n");
				tabulacao++;
				imprimeLista(r->lista);
				tabulacao--;
				tabular();
				printf("endif");
				break;
			case WHILE_STMT:
				tabular();
				printf("while ");
				analisaAST(r->esq);
				printf(" do\n");
				tabulacao++;
				imprimeLista(r->lista);
				tabulacao--;
				tabular();
				printf("enddo");
				break;
		} //fim do swtich
	} //fim do if
}

/*
*	função que percorre a lista e chama o analisaAST com o nó da lista
* entrada: lista = header da lista
* saida: void
*/
void imprimeLista (struct lista * lista) {
	if (lista != NULL) {
		imprimeLista(lista->proximo);
		analisaAST(lista->no);
		printf(";\n");
	}
}

/*
*	função que imprime as tabulações no começo de cada linha
* saida: void
*/
void tabular () {
	for (int i = 0; i < tabulacao; i++) {
		printf("\t");
	}
}
