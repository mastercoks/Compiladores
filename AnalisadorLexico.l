%option noyywrap
    #include <stdio.h>
    #include <stdlib.h>
    int linha = 1;
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
"if"            {printf("%d\t| T_IF\t\t| if\n", linha);}
"then"          {printf("%d\t| T_THEN\t| then\n", linha);}
"endif"         {printf("%d\t| T_ENDIF\t| endif\n", linha);}
"while"         {printf("%d\t| T_WHILE\t| while\n", linha);}
"do"            {printf("%d\t| T_DO\t\t| do\n", linha);}
"enddo"         {printf("%d\t| T_ENDDO\t| enddo\n", linha);}
"read"          {printf("%d\t| T_READ\t| read\n", linha);}
"write"         {printf("%d\t| T_WRITE\t| write\n", linha);}
"<"             {printf("%d\t| T_MENOR\t| <\n", linha);}
">"             {printf("%d\t| T_MAIOR\t| >\n", linha);}
"="             {printf("%d\t| T_IGUAL\t| =\n", linha);}
"("             {printf("%d\t| T_ABREP\t| (\n", linha);}
")"             {printf("%d\t| T_FECHAP\t| )\n", linha);}
"+"             {printf("%d\t| T_ADD\t\t| +\n", linha);}
"-"             {printf("%d\t| T_SUB\t\t| -\n", linha);}
"*"             {printf("%d\t| T_MULT\t| *\n", linha);}
"/"             {printf("%d\t| T_DIV\t\t| /\n", linha);}
":="            {printf("%d\t| T_ATRIB\t| :=\n", linha);}
";"             {printf("%d\t| T_PeV\t\t| ;\n", linha);}
"true"          {printf("%d\t| T_TRUE\t| true\n", linha);}
"false"         {printf("%d\t| T_FALSE\t| false\n", linha);}
{id}            {printf("%d\t| T_ID\t\t| %s\n", linha, yytext);}
{numero}        {printf("%d\t| T_NUM\t\t| %s\n", linha, yytext);}
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
