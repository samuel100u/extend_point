CFLAGS = -std=c++11

LDFLAGS= -lxmlrpc_server_abyss++ -lxmlrpc_server++ \
				-lxmlrpc_util  -lxmlrpc++ \
				-pthread
ALL: example

extend.o: extend.cpp
	${CXX} extend.cpp -c $(CFLAGS) 

example.o: example.cpp
	${CXX} example.cpp -c $(CFLAGS) 

example: extend.o example.o
	${CXX} $(CFLAGS) example.o extend.o -o example $(LDFLAGS)
	
clean:
	rm *.o example
