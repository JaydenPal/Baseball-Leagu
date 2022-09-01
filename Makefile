output: project.o
	gcc project.o -o output

project.o: project.c
	gcc -c project.c

clean: 
	rm *.o output