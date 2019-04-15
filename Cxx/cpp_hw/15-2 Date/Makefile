test.out: test.o date.o
	g++ -o test.out test.o date.o

test.o: test.cpp date.h

date.o: date.cpp date.h

.PHONY: clean
clean:
	rm test.out test.o date.o