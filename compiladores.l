%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
int linha = 1;
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
\n              {linha++;}
{ws}            {/*ignora espaço e tabulação*/}
{comentario}    {linha++;/*ignora os comentarios*/}
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
"true"          {return T_TRUE ;}
"false"         {return T_FALSE ;}
{id}            {yylval = *yytext - 'a'; return T_ID ;}
{numero}        {yylval = atoi(yytext); return T_NUM ;}
{numero}{letra} {printf("Erro léxico na linha %d, identificador malformado!\n", linha);exit(1);}
.               {printf("Erro léxico na linha %d, token não esperado!\n", linha);exit(1);}

%%

int main( int argc, char *argv[] ){
    printf("Linha\t| Token\t\t| Lexema\n");
    FILE *input = fopen(argv[1], "r");
    yyin = input;
    yylex();
    return 0;
}
