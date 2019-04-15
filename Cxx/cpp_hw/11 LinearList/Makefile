test.out: test.o linearlist.o
	g++ -o test.out test.o linearlist.o

test.o: test.cpp linearlist.h

linearlist.o: linearlist.cpp linearlist.h

.PHONY: clean
clean:
	rm test.out test.o linearlist.o