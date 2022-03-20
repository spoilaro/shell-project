wish: main.o prompt.o builtins.o
	gcc -Wall -std=c99 -o wish main.o prompt.o builtins.o

main.o: main.c prompt.h
	gcc -Wall -std=c99 -c main.c

builtins.o: builtins.c prompt.h
	gcc -Wall -std=c99 -c builtins.c

prompt.o: prompt.c prompt.h
	gcc -Wall -std=c99 -c prompt.c

clean:
	rm wish main.o prompt.o builtins.o
