# -*- MakeFile -*-

main: main.c
	gcc main.c llfifo.c cbfifo.c test_cbfifo.c test_llfifo.c  -o main
