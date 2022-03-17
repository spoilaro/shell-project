wish: main.o prompt.o
	gcc -Wall -std=c99 -o wish main.o prompt.o

main.o: main.c prompt.h
	gcc -Wall -std=c99 -c main.c

prompt.o: prompt.c prompt.h
	gcc -Wall -std=c99 -c prompt.c

clean:
	rm wish main.o prompt.o
