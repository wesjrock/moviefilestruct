all: program main operacoes_arquivo gerador_dados utilitarios

program: main.o operacoes_arquivo.o operacoes_arquivo.o gerador_dados.o utilitarios.o
	gcc -o program main.o operacoes_arquivo.o gerador_dados.o utilitarios.o -Wall -lm

main: main.o 
	gcc -g -c main.c
	
	
operacoes_arquivo: operacoes_arquivo.c operacoes_arquivo.h
	gcc -g -c operacoes_arquivo.c


gerador_dados: gerador_dados.c gerador_dados.h
	gcc -g -c gerador_dados.c
	
	
utilitarios: utilitarios.c utilitarios.h
	gcc -g -c utilitarios.c
	
clean:
	rm *.o
run:
	./program
