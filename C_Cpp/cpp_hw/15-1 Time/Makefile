test.out: test.o time.o
	g++ -o test.out test.o time.o

test.o: test.cpp time.h

time.o: time.cpp time.h

.PHONY: clean
clean:
	rm test.out test.o time.o