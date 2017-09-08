all:client
client: client_main.cpp client_socket.o tools.o newfunc.o trello.o board.o list.o card.o comment.o
	g++ client_main.cpp client_socket.o tools.o  newfunc.o trello.o board.o list.o card.o comment.o -o client
	
client_socket.o: client_socket.cpp client_socket.h tools.h network_exception.h
	g++ -c client_socket.cpp
newfunc.o: newfunc.cpp newfuncs.h trello.h board.h list.h card.h exp.h comment.h client_socket.h 
	g++ -c newfunc.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp

	g++ -c funcs.cpp
trello.o: trello.cpp trello.h board.h list.h card.h exp.h comment.h 
	g++ -c trello.cpp
board.o: board.cpp board.h list.h card.h exp.h comment.h 
	g++ -c board.cpp
list.o: list.cpp list.h card.o
	g++ -c list.cpp
card.o: card.cpp card.h exp.h comment.h
	g++ -c card.cpp
comment.o: comment.cpp comment.h member.h
		g++ -c comment.cpp
clean:
	rm *.o client *.txt
