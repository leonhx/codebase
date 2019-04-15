test.out: test.o int.o
	g++ -o test.out test.o int.o

test.o: test.cpp int.h

int.o: int.cpp int.h

.PHONY: clean
clean:
	rm test.out test.o int.o