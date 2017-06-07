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

//*char ao inves de int?
void analisaAST (struct no *r) {

	if(r != NULL) {
		switch (r->tipo_no) {
			case TERMINAL:
        //char var[256];
				printf("%s", r->valor);
				break;
			case IF_STMT:
			 	printf("if ");
				analisaAST(r->esq);
				printf("then ");
				analisaAST(r->dir);
				printf("endif");
			case WRITE_STMT:
				printf("while ");
				analisaAST(r->esq);
				printf("do ");
				analisaAST(r->dir);
				printf("enddo");
			case FATOR:
				printf("(");
				analisaAST(r->esq);
				printf(")");
				break;
			default:
				analisaAST(r->esq);
				printf("%s", r->valor);
				analisaAST(r->dir);
		} //fim do swtich
	} //fim do if
}

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


	struct no * raiz =
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
