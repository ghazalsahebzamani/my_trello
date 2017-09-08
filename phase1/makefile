all: a.out
a.out: main.cpp funcs.o
	g++ main.cpp  funcs.o trello.o board.o list.o card.o comment.o
funcs.o: funcs.cpp funcs.h trello.o
	g++ -c funcs.cpp
trello.o: trello.cpp trello.h board.o
	g++ -c trello.cpp
board.o: board.cpp board.h list.o
	g++ -c board.cpp
list.o: list.cpp list.h card.o
	g++ -c list.cpp
card.o: card.cpp card.h exp.h comment.o
	g++ -c card.cpp
comment.o: comment.cpp comment.h member.h
		g++ -c comment.cpp
clean:
	rm *.o a.out *.txt
