OBJECTS = main.o tree.o

wordfreak: $(OBJECTS)
	gcc -o wordfreak $(OBJECTS)
main.o: main.c
	gcc -c main.c -o main.o
tree.o: tree.c tree.h
	gcc -c tree.c -o tree.o
clean:
	rm wordfreak $(OBJECTS)
