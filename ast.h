#ifndef AST_H
#define AST_H
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  //define os tipos de nó (agrupando terminais)
  //se mudanças se confirmarem: adicionar tokens das rotinas auxiliares
  typedef enum NO { TERMINAL, IF_STMT, WHILE_STMT, ASSIGN_STMT, READ_STMT, WRITE_STMT, ADD, SUB, MULT, DIV, MAIOR, MENOR, IGUAL, PARENTESES }
  	tipoNO;

	struct lista * raiz;
  int tabulacao = 0;

  /*
  * define o tipo nó
  * esq: filho esquerdo
  * dir: filho direito
  * tipo_no = define regras de produção (nós)
  * valor = valor do nó (a ser impresso quando estourado)
  * lista = lista que aponta para o próximo STMT
  */
  struct no {
  	struct no * esq;
  	struct no * dir;
  	tipoNO tipo_no;
  	char* valor  ;
    struct lista * lista;
  };

  /*
  * define o tipo nó
  * no = nó que pertence a lista
  * proximo = lista que aponta para o próximo STMT
  */
  struct lista {
    struct no * no;
    struct lista * proximo;
  };

  //inicializando funções
  struct no * criaNoTerminal(char* v);
  struct no * criarNoRead(char* v);
  struct no * criarNoWrite(struct no * n);
  struct no * criarNoOperacao(struct no *esq, tipoNO t, struct no *dir);
  struct no * criarNoParenteses(struct no * esq);
  struct no * criarNoAtribuicao(struct no * esq, struct no * dir);
  struct no * criarNoIf(struct no * esq, struct lista * lista);
  struct no * criarNoWhile(struct no * esq, struct lista * lista);
  struct lista* criarLista( struct no * no, struct lista * proximo);
  void analisaAST(struct no *raiz);
  void imprimeLista(struct lista *lista);
  void tabular();

#endif /*AST_H*/
