
%option noyywrap nodefault yylineno
%{
#include <stdio.h>
#include <ast.c>
extern int yylineno; /* from lexer */
void yyerror(char *s, ...);
%}

%token T_IF T_THEN T_ENDIF T_WHILE

%%

program:
              stmt_seq T_PeV //{$$ = makenode();}
              ;

stmt_seq:     stmt_seq T_PeV stmt //{ $$ = makenode();}
              | stmt //{ $$ = makenode();}
              ;

stmt:         if_stmt  //{ $$ = makenode();}
              | while_stmt //{ $$ = makenode();}
              | assign_stmt //{ $$ = makenode();}
              | read_stmt //{ $$ = makenode();}
              | write_stmt //{ $$ = makenode();}
              ;

if_stmt:      T_IF exp T_THEN stmt_seq T_ENDIF //{ $$ = makenode();}
              ;

while_stmt:   T_WHILE exp T_DO stmt_seq T_ENDDO //{ $$ = makenode();}
              ;

assign_stmt:  T_ID T_ATRIB exp //{ $$ = makenode();}
              ;

read_stmt:    T_READ T_ID T_PeV //{ $$ = makenode()}
              ;

write_stmt:   T_WRITE exp //{ $$ = makenode();}
              ;

exp:          simple_exp T_MENOR simple_exp //{ $$ = makenode();}
              | simple_exp T_MAIOR simple_exp //{ $$ = makenode();}
              | simple_exp T_IGUAL simple_exp //{ $$ = makenode();}
              | simple_exp //{ $$ = makenode();}
              ;

simple_exp:   simple_exp T_ADD simple_exp { printf("%d + %d", $1, $3);}
              | simple_exp T_SUB simple_exp //{ $$ = makenode();}
              | termo
              ;

termo:        termo T_MULT fator //{ $$ = makenode();}
              | termo T_DIV fator //{ $$ = makenode();}
              | fator //{ $$ = makenode();}
              ;

fator:        T_ABREP exp T_FECHAP //{ $$ = makenode();}
              | T_NUM //{ $$ = makenode();}
              | T_ID //{ $$ = makenode();}
              ;
