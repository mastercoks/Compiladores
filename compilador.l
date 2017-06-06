%option noyywrap yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

/* definições regulares */
delim           [ \t]
ws              {delim}+
letra           [a-zA-Z]
digito          [0-9]
id              {letra}({letra}|{digito})*
numero          ({digito})+
comentario      "--"(.)*[\n]

%%
[\n]            {yylineno++;}
{ws}            {/*ignora espaço e tabulação*/}
{comentario}    {yylineno++;/*ignora os comentarios*/}
"if"            {return T_IF ;}
"then"          {return T_THEN ;}
"endif"         {return T_ENDIF ;}
"while"         {return T_WHILE ;}
"do"            {return T_DO ;}
"enddo"         {return T_ENDDO ;}
"read"          {return T_READ ;}
"write"         {return T_WRITE ;}
"<"             {return T_MENOR ;}
">"             {return T_MAIOR ;}
"="             {return T_IGUAL ;}
"("             {return T_ABREP ;}
")"             {return T_FECHAP ;}
"+"             {return T_ADD ;}
"-"             {return T_SUB ;}
"*"             {return T_MULT ;}
"/"             {return T_DIV ;}
":="            {return T_ATRIB ;}
";"             {return T_PeV ;}
{id}            {yylval.sval = yytext; return T_ID ;}
{numero}        {yylval.sval = yytext; return T_NUM ;}
{numero}{letra} {printf("Erro léxico na linha %d, identificador malformado!\n", yylineno);exit(1);}
.               {printf("Erro léxico na linha %d, token não esperado!\n", yylineno);exit(1);}

%%
//
// %%
//
// int main( int argc, char *argv[] ){
//     printf("Linha\t| Token\t\t| Lexema\n");
//     FILE *input = fopen(argv[1], "r");
//     yyin = input;
//     yylex();
//     return 0;
// }
