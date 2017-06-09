# Identador da Linguagem T

Implementação de um compilador que recebe como entrada um código da linguagem T e tem como saída esse código identado.

## Exemplo de código da linguagem T que o compilador aceita como entrada
	read              x           ; -- le a variavel x
	if        (       x        =       0      ) then -- verifica se x eh igual a 0
	read        y; -- le a variavel y
	write               (       x     =     0   ); -- escreve x = 0 (retronara um boolean)
	while       (         y       =     x     )   do -- enquanto a x for igual a 0
	        read   z      ; -- le a variavel z
	z           :=        y * 2;  -- atribui a z o valor de y multiplicado por 2
	        write     (z +   y)  /   x -- escreve o valor da soma de z e y dividido por x
	enddo -- fim do while
	endif; -- fim do if

## Saída para a entrada acima
![alt tag](https://raw.githubusercontent.com/mastercoks/Compiladores/master/saida.png)

## Guia de como executar

### Compilar o trabalho:

	./compilar.sh
	./a.out exemplo.lt

### AnalizadorLexico.c

	gcc AnalizadorLexico.c
	./a.out exemplo.lt

### AFD.jff  

	Abrir no JFLAP.java versão 7

## Sobre
	Projeto realizado para a matéria de Compiladores,  UESB 2016.

## Autores
	Matheus Coqueiro Andrade, [@mastercoks]](https://github.com/mastercoks/);
	José Pedro Maioli Calvalcante Menezes[@mai0li]](https://github.com/mai0li/);
