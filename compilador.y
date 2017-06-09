
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
      fprintf(stderr, "Erro de sintaxe encontrado!\n");
      exit(1);
    }
%}

%union {
  char *sval;
  struct no *no;
  struct lista *lista;
}

%start program

%type <lista> program
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
%type <no> id

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

program:      stmt_seq T_PeV                      { raiz = $<lista>1; imprimeLista(raiz);}
              ;

stmt_seq:     stmt_seq T_PeV stmt                 { $<lista>$ = criarLista($<no>3, $<lista>1); }
              | stmt                              { $<lista>$ = criarLista($<no>1, NULL);}
              ;

stmt:         write_stmt                          { $<no>$ = $<no>1; }
              | while_stmt                        { $<no>$ = $<no>1; }
              | assign_stmt                       { $<no>$ = $<no>1; }
              | read_stmt                         { $<no>$ = $<no>1; }
              | if_stmt                           { $<no>$ = $<no>1; }
              ;

if_stmt:      T_IF exp T_THEN stmt_seq T_ENDIF    { $<no>$ = criarNoIf($<no>2, $<lista>4); }
              ;

while_stmt:   T_WHILE exp T_DO stmt_seq T_ENDDO   { $<no>$ = criarNoWhile($<no>2, $<lista>4); }
              ;

assign_stmt:  id T_ATRIB exp                    { $<no>$ = criarNoAtribuicao($<no>1, $<no>3);}
              ;

read_stmt:    T_READ T_ID                         { $<no>$ = criarNoRead($2); }
              ;

write_stmt:   T_WRITE exp                         { $<no>$ = criarNoWrite($<no>2); }
              ;

exp:          simple_exp T_MENOR simple_exp       { $<no>$ = criarNoOperacao($<no>1, MENOR, $<no>3); }
              | simple_exp T_MAIOR simple_exp     { $<no>$ = criarNoOperacao($<no>1, MAIOR, $<no>3); }
              | simple_exp T_IGUAL simple_exp     { $<no>$ = criarNoOperacao($<no>1, IGUAL, $<no>3); }
              | simple_exp                        { $<no>$ = $<no>1; }
              ;

simple_exp:   simple_exp T_ADD simple_exp         { $<no>$ = criarNoOperacao($<no>1, ADD, $<no>3); }
              | simple_exp T_SUB simple_exp       { $<no>$ = criarNoOperacao($<no>1, SUB, $<no>3); }
              | termo                             { $<no>$ = $<no>1; }
              ;

termo:        termo T_MULT fator                  { $<no>$ = criarNoOperacao($<no>1, MULT, $<no>3); }
              | termo T_DIV fator                 { $<no>$ = criarNoOperacao($<no>1, DIV, $<no>3); }
              | fator                             { $<no>$ = $<no>1; }
              ;

fator:        T_ABREP exp T_FECHAP                { $<no>$ = criarNoParenteses($<no>2); }
              | T_ID                              { $<no>$ = criaNoTerminal($<sval>1); }
              | T_NUM                             { $<no>$ = criaNoTerminal($<sval>1); }
              ;

id:           T_ID                                { $$ = criaNoTerminal($<sval>1);}
%%

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  yyin = input;
  yyparse();

  return 0;
}
