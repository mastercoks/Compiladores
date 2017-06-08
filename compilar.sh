#!/bin/bash

bison -y -d compilador.y
flex compilador.l
gcc y.tab.c lex.yy.c
clear
echo "compilado com sucesso."
