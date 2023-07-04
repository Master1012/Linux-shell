all:
	gcc -o ls ls.c
	gcc -o date date.c
	gcc -o mkdir mkdir.c
	gcc -o rm rm.c
	gcc -o cat cat.c
	gcc -pthread -o ./a.out a.c
	./a.out
