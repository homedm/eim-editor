CC = g++
DEST = /usr/local/bin
INCLUDE =
CFLAGS = -std=c++11
LIBS = -lncursesw
OBJDIR = ./obj
OBJS = eim.o EimEngineClass.o BufferClass.o CommandLineClass.o
PROGRAM = ../bin/eim

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $(PROGRAM)

eim.o: eim.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c eim.cpp

EimEngineClass.o:EimEngineClass.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c EimEngineClass.cpp

BufferClass.o:BufferClass.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c BufferClass.cpp

CommandLineClass.o:CommandLineClass.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c CommandLineClass.cpp

clean:
	rm -f *.o $(PROGRAM)
