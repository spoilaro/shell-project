wish: main.o prompt.o utility.o builtins.o
	gcc -Wall -std=c99 -o wish main.o prompt.o utility.o builtins.o

main.o: main.c utility.h
	gcc -Wall -std=c99 -c main.c

prompt.o: prompt.c utility.c utility.h
	gcc -Wall -std=c99 -c prompt.c utility.c

builtins.o: builtins.c utility.h
	gcc -Wall -std=c99 -c builtins.c

utility.o: utility.c utility.h
	gcc -Wall -std=c99 -c utility.c

clean:
	rm wish main.o prompt.o utility.o builtins.o