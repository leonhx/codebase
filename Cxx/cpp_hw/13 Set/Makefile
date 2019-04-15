test.out: test.o set.o
	g++ -o test.out test.o set.o

test.o: test.cpp set.h

set.o: set.cpp set.h

.PHONY: clean
clean:
	rm test.out test.o set.o