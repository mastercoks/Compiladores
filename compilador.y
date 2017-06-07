
%{
#include <stdio.h>
#include "ast.c"
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
%type <no> stmt_seq
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

program:
              stmt_seq T_PeV                      {$$ = criaNoNaoTerminal($<no>1, PROGRAM, ";\n", NULL); analisaAST($$);}
              ;

stmt_seq:     stmt_seq T_PeV stmt                 { $$ = criaNoNaoTerminal($<no>1, STMT_SEQ, ";\n", $<no>3);}
              | stmt                              { $$ = criaNoNaoTerminal($<no>1, STMT_SEQ, "", NULL);}
              ;

stmt:         write_stmt                          { $$ = criaNoNaoTerminal($<no>1, STMT, "", NULL);}
              | while_stmt                        { $$ = criaNoNaoTerminal($<no>1, STMT, "", NULL);}
              | assign_stmt                       { $$ = criaNoNaoTerminal($<no>1, STMT, "", NULL);}
              | read_stmt                         { $$ = criaNoNaoTerminal($<no>1, STMT, "", NULL);}
              | if_stmt                           { $$ = criaNoNaoTerminal($<no>1, STMT, "", NULL);}
              ;

if_stmt:      T_IF exp T_THEN stmt_seq T_ENDIF    { $$ = criaNoNaoTerminal($<no>1, IF_STMT, "", $<no>4);}
              ;

while_stmt:   T_WHILE exp T_DO stmt_seq T_ENDDO   { $$ = criaNoNaoTerminal($<no>1, WHILE_STMT, "", $<no>4);}
              ;

assign_stmt:  T_ID T_ATRIB exp                    { $$ = criaNoNaoTerminal($<no>1, ASSIGN_STMT, ":=", $<no>3);}
              ;

read_stmt:    T_READ T_ID                         { $$ = criaNoNaoTerminal($<no>1, READ_STMT, "", $<no>2);}
              ;

write_stmt:   T_WRITE exp                         { $$ = criaNoNaoTerminal($<no>1, WRITE_STMT, "", $<no>2);}
              ;

exp:          simple_exp T_MENOR simple_exp       { $$ = criaNoNaoTerminal($<no>1, EXP, "<", $<no>3);}
              | simple_exp T_MAIOR simple_exp     { $$ = criaNoNaoTerminal($<no>1, EXP, ">", $<no>3);}
              | simple_exp T_IGUAL simple_exp     { $$ = criaNoNaoTerminal($<no>1, EXP, "=", $<no>3);}
              | simple_exp                        { $$ = criaNoNaoTerminal($<no>1, EXP, "", NULL);}
              ;

simple_exp:   simple_exp T_ADD simple_exp         { $$ = criaNoNaoTerminal($<no>1, SIMPLE_EXP, "+", $<no>3);}
              | simple_exp T_SUB simple_exp       { $$ = criaNoNaoTerminal($<no>1, SIMPLE_EXP, "-", $<no>3);}
              | termo                             { $$ = criaNoNaoTerminal($<no>1, SIMPLE_EXP, "", NULL);}
              ;

termo:        termo T_MULT fator                  { $$ = criaNoNaoTerminal($<no>1, TERMO, "*", $<no>3);}
              | termo T_DIV fator                 { $$ = criaNoNaoTerminal($<no>1, TERMO, "/", $<no>3);}
              | fator                             { $$ = criaNoNaoTerminal($<no>1, TERMO, "", NULL);}
              ;

fator:        T_ABREP exp T_FECHAP                { $$ = criaNoNaoTerminal($<no>2, FATOR, "", NULL);}
              | T_NUM                             { $$ = criaNoTerminal($1);}
              | T_ID                              { $$ = criaNoTerminal($1);}
              ;
%%

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  yyparse();
  return 0;
}
