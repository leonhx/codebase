test.out: test.o timewithdate.o
	g++ -o test.out test.o timewithdate.o

test.o: test.cpp timewithdate.h

timewithdate.o: timewithdate.cpp timewithdate.h

.PHONY: clean
clean:
	rm test.out test.o timewithdate.o