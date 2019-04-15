test.out: test.o complex.o
	g++ -o test.out test.o complex.o

test.o: test.cpp complex.h

complex.o: complex.cpp complex.h

.PHONY: clean
clean:
	rm test.out test.o complex.o