#ifndef AST_H
#define AST_H
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

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
  void analisaAST(struct no *raiz);

#endif /*AST_H*/
