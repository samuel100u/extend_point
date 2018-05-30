CFLAGS = -std=c++11

ALL: example

extend.o: extend.cpp
	${CXX} extend.cpp -c $(CFLAGS) 

example.o: example.cpp
	${CXX} example.cpp -c $(CFLAGS) 

example: extend.o example.o
	${CXX} $(CFLAGS) example.o extend.o -o example

clean:
	rm *.o example
