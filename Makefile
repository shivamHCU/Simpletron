all: main.o shlToSml.o module8.o module7.o module6.o module5.o
	gcc	main.o shlToSml.o module8.o module7.o module6.o module5.o -o p1

main.o: main.c shlToSml.h
	gcc -I . -c main.c

shlToSml.o:	shlToSml.c shlToSml.h module5.h module6.h module7.h module8.h
	gcc -I . -c shlToSml.c

module5.o: module5.c module5.h module8.h module6.h
	gcc -I . -c module5.c

module6.o: module6.c module6.h module8.h
	gcc -I . -c module6.c

module7.o: module7.c module7.h module8.h
	gcc -I . -c module7.c

module8.o: module8.c module8.h
	gcc -I . -c module8.c

clean:
	rm -rf *.o
	rm p1
	rm error.txt
	rm sml.txt
output:
	cat sml.txt