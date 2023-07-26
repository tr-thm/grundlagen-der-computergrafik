bin/engine: obj/main.o | bin
	gcc -g obj/*.o -o bin/engine

obj/main.o: main.c | obj
	gcc -g -c main.c -o obj/main.o

bin:
	mkdir -p bin

obj: 
	mkdir -p obj

run: bin/engine
	bin/engine

clean:
	rm -rf obj
	rm -rf bin