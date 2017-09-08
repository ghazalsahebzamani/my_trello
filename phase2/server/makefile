all: server
server: server_main.cpp myserver.o server_socket.o server.o tools.o funcs.o trello.o board.o list.o card.o comment.o
	g++ server_main.cpp myserver.o server_socket.o server.o tools.o funcs.o trello.o board.o list.o card.o comment.o -o server
myserver.o:myserver.cpp exp.h Myserver.h server.h tools.h funcs.h trello.h board.h list.h card.h exp.h comment.h member.h
	g++ -c myserver.cpp
server.o: server.cpp server.h funcs.h trello.h board.h list.h card.h exp.h comment.h member.h
	g++ -c server.cpp
	
server_socket.o: server_socket.cpp server_socket.h tools.h network_exception.h
	g++ -c server_socket.cpp
	
tools.o: tools.cpp tools.h
	g++ -c tools.cpp
funcs.o: funcs.cpp funcs.h trello.h board.h list.h card.h exp.h comment.h member.h
	g++ -c funcs.cpp
trello.o: trello.cpp trello.h board.h list.h card.h exp.h comment.h member.h
	g++ -c trello.cpp
board.o: board.cpp board.h list.h card.h exp.h comment.h member.h
	g++ -c board.cpp
list.o: list.cpp list.h card.h exp.h comment.h member.h
	g++ -c list.cpp
card.o: card.cpp card.h exp.h comment.h member.h
	g++ -c card.cpp
comment.o: comment.cpp comment.h member.h
		g++ -c comment.cpp
clean:
	rm *.o server *.txt
