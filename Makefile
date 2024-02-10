VER 	= c++14
OBJS	= Card.o Game.o Main.o
SOURCE	= Card.cpp Game.cpp Main.cpp
HEADER	= Card.h Game.h
OUT	= game
CC	 = g++
FLAGS	 = -g -c -Wall -std=$(VER)
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Card.o: Card.cpp
	$(CC) $(FLAGS) Card.cpp

Game.o: Game.cpp
	$(CC) $(FLAGS) Game.cpp

Main.o: Main.cpp
	$(CC) $(FLAGS) Main.cpp


clean:
	rm -f $(OBJS) $(OUT)