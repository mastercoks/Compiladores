#include "ast.h"

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


//construtor
struct no * criaNoTerminal(char v[]){
	struct no * no = (struct no*) malloc(sizeof(struct no));

	no->dir = NULL;
	no->esq = NULL;
	no->tipo_no = TERMINAL;
	strcpy(	no->valor, v);
	no->lista = NULL;

	return no;
}

//construtor
struct no * criaNoNaoTerminal(struct no * e, tipoNO n, char v[], struct no * d){
	struct no * no = (struct no*) malloc(sizeof(struct no));

	no->dir = d;
	no->esq = e;
	no->tipo_no = n;
	strcpy(	no->valor, v);
	no->lista = NULL;

	return no;
}

struct no * criarNoRead(char v[]) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = NULL;
	no->tipo_no = READ_STMT;
	strcpy(	no->valor, v);
	no->lista = NULL;

	return no;
}

struct no * criarNoWrite(struct no * n) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = n;
	no->tipo_no = WRITE_STMT;
	//no->valor = NULL;
	no->lista = NULL;

	return no;
}

struct no * criarNoOperacao(struct no *esq, tipoNO t, struct no *dir) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = dir;
	no->esq = esq;
	no->tipo_no = t;
	//no->valor = NULL;
	no->lista = NULL;

	return no;
}

struct no * criarNoParenteses(struct no * n) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = n;
	no->tipo_no = PARENTESES;
	//no->valor = NULL;
	no->lista = NULL;

	return no;
}

struct no * criarNoAtribuicao(struct no * esq, struct no * dir) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = dir;
	no->esq = esq;
	no->tipo_no = ASSIGN_STMT;
	//no->valor = NULL;
	no->lista = NULL;

	return no;
}

struct no * criarNoIf(struct no * esq, struct lista * lista) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = esq;
	no->tipo_no = IF_STMT;
	//no->valor = NULL;
	no->lista = lista;
	return no;
}

struct no * criarNoWhile(struct no * esq, struct lista * lista) {
	struct no * no = (struct no*) malloc(sizeof(struct no));
	no->dir = NULL;
	no->esq = esq;
	no->tipo_no = WHILE_STMT;
	//no->valor = NULL;
	no->lista = lista;
	return no;
}

struct lista* criarLista( struct no * no, struct lista * proximo) {
	struct lista * lista = (struct lista*) malloc(sizeof(struct lista));
	lista->no = no;
	lista->proximo = proximo;
	return lista;
}

//*char ao inves de int?
void analisaAST (struct no *r) {
	//char teste[] = (char[]) malloc(sizeof(char));
	//strcpy(	teste, r->teste);
	if(r != NULL) {
		switch (r->tipo_no) {
			case TERMINAL:
				printf("%s1", r->valor);
				break;
			case READ_STMT:
				printf("read %s;\n", r->valor);
				break;
			case WRITE_STMT:
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
				printf("1=1");
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
				break;
			case MULT:
				analisaAST(r->esq);
				printf(" * ");
				analisaAST(r->dir);
				break;
			case DIV:
				analisaAST(r->esq);
				printf(" / ");
				analisaAST(r->dir);
				break;
			case PARENTESES:
				printf("(");
				analisaAST(r->esq);
				printf(")");
				break;
			case ASSIGN_STMT:
				analisaAST(r->esq);
				printf(" := ");
				analisaAST(r->dir);
			case IF_STMT:
			 	printf("if ");
				analisaAST(r->esq);
				printf("then ");
				imprimeLista(r->lista);
				printf("endif");
				break;
			case WHILE_STMT:
				printf("while ");
				analisaAST(r->esq);
				printf("do ");
				imprimeLista(r->lista);
				printf("enddo");
				break;
			default:
				//analisaAST(r->esq);
				//printf("%s", r->valor);
				//analisaAST(r->dir);
				break;
		} //fim do swtich
	} //fim do if
}

void imprimeLista (struct lista * lista) {
	if (lista != NULL) {
		analisaAST(lista->no);
		imprimeLista(lista->proximo);
	}
}
/*
int main(){

	char coks[] = "coks";
	char read[] = "read ";
	char vazio[] = "";
	char pve[] = ";\n";
	char atrib[] = " := ";
	char num[] = "3";


	//struct no* raiz = criaNoNaoTerminal(criaNoNaoTerminal(criaNoTerminal(read), //READ_STMT, vazio, criaNoTerminal(coks)), PROGRAM, pve, NULL);
	//printf("%s\n", raiz->valor);
	//analisaAST(raiz);


	raiz =
											criaNoNaoTerminal(
												criaNoNaoTerminal(
													criaNoNaoTerminal(
														criaNoNaoTerminal(
															criaNoNaoTerminal(
																criaNoTerminal(read)
															, READ_STMT, vazio, criaNoTerminal(coks))
														, STMT, vazio, NULL)
													, STMT_SEQ, vazio, NULL)
												, STMT_SEQ, pve,
												criaNoNaoTerminal(
													criaNoNaoTerminal(
														criaNoTerminal(coks)
													, ASSIGN_STMT, atrib,
													criaNoNaoTerminal(
														criaNoNaoTerminal(
															criaNoNaoTerminal(
																criaNoTerminal(num)
															, TERMO, vazio, NULL)
														, SIMPLE_EXP, vazio, NULL)
													, EXP, vazio, NULL))
												, STMT, vazio, NULL))
											, PROGRAM, pve, NULL);
	//struct no * raiz =
	//	criaNoOperador(criaNoValor(2), ADD, criaNoOperador((criaNoValor(3)), MUL, criaNoValor(4)));

	analisaAST(raiz);
return 0;
}
*/
