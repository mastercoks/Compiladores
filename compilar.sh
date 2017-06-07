#!/bin/bash

if [ "$(bison -y -d compilador.y)" == "0" ]; then
  echo "falha no bison."
  exit 1
fi
if [ "$(flex compilador.l)" == "0" ]; then
  echo "falha no flex."
  exit 1
fi
if [ "$(gcc y.tab.c lex.yy.c)" == "0" ]; then
  echo "falha no gcc."
  exit 1
fi
echo "compilado com sucesso."
