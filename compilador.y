
%{
#include <stdio.h>
#include "ast.c"
#define YYDEBUG 1
/* from lexer */
extern int yylineno;
extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(const char* msg) {
      fprintf(stderr, "%s\n", msg);
    }
%}

%union {
  char *sval;
  struct no *no;
}

%start program

%type <no> program
%type <lista> stmt_seq
%type <no> stmt
%type <no> if_stmt
%type <no> while_stmt
%type <no> assign_stmt
%type <no> read_stmt
%type <no> write_stmt
%type <no> exp
%type <no> simple_exp
%type <no> termo
%type <no> fator

%token T_IF
%token T_THEN
%token T_ENDIF
%token T_WHILE
%token T_DO
%token T_ENDDO
%token T_READ
%token <sval> T_WRITE
%token <sval> T_MENOR
%token <sval> T_MAIOR
%token <sval> T_IGUAL
%token <sval> T_ABREP
%token <sval> T_FECHAP
%token <sval> T_ADD
%token <sval> T_SUB
%token <sval> T_MULT
%token <sval> T_DIV
%token <sval> T_ATRIB
%token <sval> T_PeV
%token <sval> T_ID
%token <sval> T_NUM

%left T_ADD T_SUB T_MULT T_DIV
%%

program::=
              stmt_seq                     {raiz = $<no>1; printf("passei 1\n");}
              ;

stmt_seq:     stmt_seq T_PeV stmt                 { $<lista>$ = criarLista($<lista>1, $<no>3);printf("passei 2\n");}
              | stmt                              { raiz = $<no>1; printf("passei 3\n"); analisaAST(raiz);}
              ;

stmt:         write_stmt                          { $<no>$ = $<no>1; printf("passei 4\n");}
              | while_stmt                        { $<no>$ = $<no>1; printf("passei 5\n");}
              | assign_stmt                       { $<no>$ = $<no>1; printf("passei 6\n");}
              | read_stmt                         { $<no>$ = $<no>1; printf("passei 7\n");}
              | if_stmt                           { $<no>$ = $<no>1; printf("passei 8\n");}
              ;

if_stmt:      T_IF exp T_THEN stmt_seq T_ENDIF    { $<no>$ = criarNoIf($<no>2, $<lista>4); printf("passei 9\n");}
              ;

while_stmt:   T_WHILE exp T_DO stmt_seq T_ENDDO   { $<no>$ = criarNoWhile($<no>2, $<lista>4); printf("passei 10\n");}
              ;

assign_stmt:  T_ID T_ATRIB exp                    { $<no>$ = criarNoAtribuicao(criaNoTerminal($1), $<no>3); printf("passei 11\n");}
              ;

read_stmt:    T_READ T_ID                         { $<no>$ = criarNoRead($2); printf("passei 12\n");}
              ;

write_stmt:   T_WRITE exp                         { $<no>$ = criarNoWrite($<no>2); printf("passei 13\n");}
              ;

exp:          simple_exp T_MENOR simple_exp       { $<no>$ = criarNoOperacao($<no>1, MENOR, $<no>3); printf("passei 14\n");}
              | simple_exp T_MAIOR simple_exp     { $<no>$ = criarNoOperacao($<no>1, MAIOR, $<no>3); printf("passei 15\n");}
              | simple_exp T_IGUAL simple_exp     { $<no>$ = criarNoOperacao($<no>1, IGUAL, $<no>3); printf("passei 16\n");}
              | simple_exp                        { $<no>$ = $<no>1; printf("passei 17\n");}
              ;

simple_exp:   simple_exp T_ADD simple_exp         { $<no>$ = criarNoOperacao($<no>1, ADD, $<no>3); printf("passei 18\n");}
              | simple_exp T_SUB simple_exp       { $<no>$ = criarNoOperacao($<no>1, SUB, $<no>3); printf("passei 19\n");}
              | termo                             { $<no>$ = $<no>1; printf("passei 20\n");}
              ;

termo:        termo T_MULT fator                  { $<no>$ = criarNoOperacao($<no>1, MULT, $<no>3); printf("passei 21\n");}
              | termo T_DIV fator                 { $<no>$ = criarNoOperacao($<no>1, DIV, $<no>3); printf("passei 22\n");}
              | fator                             { $<no>$ = $<no>1; printf("passei 23\n");}
              ;

fator:        T_ABREP exp T_FECHAP                { $<no>$ = criarNoParenteses($<no>2); printf("passei 24\n");}
              | T_NUM                             { $<no>$ = criaNoTerminal($1);printf("passei 25\n");}
              | T_ID                              { $<no>$ = criaNoTerminal($1);printf("passei 26\n");}
              ;
%%

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  yyparse();

  return 0;
}
