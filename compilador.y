
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
//%type <no> if_stmt
//%type <no> while_stmt
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
%token <sval> T_WHILE
%token <sval> T_DO
%token <sval> T_ENDDO
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

%%

program:
              stmt_seq T_PeV {$$ = criaNoNaoTerminal($<no>1, PROGRAM, ";\n", NULL);}
              ;

stmt_seq:     stmt_seq T_PeV stmt { $$ = criaNoNaoTerminal($<no>1, STMT_SEQ, ";\n", $<no>3);}
              | stmt { $$ = criaNoNaoTerminal($1, STMT_SEQ, "", NULL);}
              ;

stmt:         write_stmt { $$ = criaNoNaoTerminal($1, STMT, "", NULL);}
//              | while_stmt { $$ = criaNoNaoTerminal($1, STMT, "", NULL);}
              | assign_stmt { $$ = criaNoNaoTerminal($1, STMT, "", NULL);}
              | read_stmt { $$ = criaNoNaoTerminal($1, STMT, "", NULL);}
//              | if_stmt  { $$ = criaNoNaoTerminal($1, STMT, "", NULL);}
              ;


//modificar gramatica para manter arvore binaria

//if_stmt:    T_IF if_stmt2 { $$ = criaNoNaoTerminal($1 IF_STMT "" $2);}
//            ;

//if_stmt2:   exp if_stmt3 { $$ = criaNoNaoTerminal($1 IF_STMT2 "" $2);}
//            ;

//if_stmt3:   T_THEN if_stmt3 { $$ = criaNoNaoTerminal($1 IF_STMT3 "" $2);}
//            ;

//if_stmt4:   stmt_seq T_ENDIF { $$ = criaNoNaoTerminal($1 IF_STMT4 "" $2);}
//            ;

//if_stmt:      T_IF exp T_THEN stmt_seq T_ENDIF { $$ = criaNoNaoTerminal($1, STMT, "", NULL);}
//              ;

//modificar gramatica para manter arvore binaria

//while_stmt:   T_WHILE while_stmt2 { $$ = criaNoNaoTerminal($1 WHILE_STMT "" $2);}
//              ;

//while_stmt2:  exp while_stmt3 { $$ = criaNoNaoTerminal($1 WHILE_STMT2 "" $2);}
//              ;

//while_stmt3:  T_DO while_stmt4 { $$ = criaNoNaoTerminal($1 WHILE_STMT3 "" $2);}
//              ;

//while_stmt4:  stmt_seq T_ENDDO { $$ = criaNoNaoTerminal($1 WHILE_STMT4 "" $2);}
//              ;

//while_stmt:   T_WHILE exp T_DO stmt_seq T_ENDDO { $$ = criaNoNaoTerminal($1, WHILE_STMT, "", NULL);}
//              ;

assign_stmt:  T_ID T_ATRIB exp { $$ = criaNoNaoTerminal($<no>1, ASSIGN_STMT, ":=", $3);}
              ;

read_stmt:    T_READ T_ID { $$ = criaNoNaoTerminal($<no>1, READ_STMT, "", $<no>2);}
              ;

write_stmt:   T_WRITE exp { $$ = criaNoNaoTerminal($<no>1, WRITE_STMT, "", $<no>2);}
              ;

exp:          simple_exp T_MENOR simple_exp { $$ = criaNoNaoTerminal($1, EXP, "<", $3);}
              | simple_exp T_MAIOR simple_exp { $$ = criaNoNaoTerminal($1, EXP, ">", $3);}
              | simple_exp T_IGUAL simple_exp { $$ = criaNoNaoTerminal($1, EXP, "=", $3);}
              | simple_exp { $$ = criaNoNaoTerminal($1, EXP, "", NULL);}
              ;

simple_exp:   simple_exp T_ADD simple_exp { $$ = criaNoNaoTerminal($1, SIMPLE_EXP, "+", $3);}
              | simple_exp T_SUB simple_exp { $$ = criaNoNaoTerminal($1, SIMPLE_EXP, "-", $3);}
              | termo { $$ = criaNoNaoTerminal($1, SIMPLE_EXP, "", NULL);}
              ;

termo:        termo T_MULT fator { $$ = criaNoNaoTerminal($1, TERMO, "*", $3);}
              | termo T_DIV fator { $$ = criaNoNaoTerminal($1, TERMO, "/", $3);}
              | fator { $$ = criaNoNaoTerminal($1, TERMO, "", NULL);}
              ;

//modificar gramatica para manter arvore binaria
//fixar parenteses!

//fator:      T_ABREP fator2 { $$ = criaNoNaoTerminal($1 FATOR "" $2);}
//            | T_NUM { $$ = criaNoTerminal(T_NUM.lval T_NUM);}
//            | T_ID { $$ = criaNoTerminal(T_ID.lval T_ID);}
//            ;

//fator2:     exp T_FECHAP { $$ = criaNoNaoTerminal($1 FATOR2 "" $2);}
//            ;


//por hora desconsiderando parenteses T_ABREP exp T_FECHAP{ $$ = criaNoNaoTerminal($1 FATOR "<" $3);}
fator:        T_NUM { $<no>$ = criaNoTerminal(yylval.sval);}
              | T_ID { $<no>$ = criaNoTerminal(yylval.sval);}
              ;
%%

int main(int argc, char *argv[]) {
  FILE *input = fopen(argv[1], "r");
  yyparse();
  return 0;
}
