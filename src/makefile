CC = g++
DEST = /usr/local/bin
INCLUDE = -I/usr/include/ncursesw/
CFLAGS = -std=c++11
LIBS = -lncursesw
OBJDIR = ./obj
OBJS = eim.o EimEngineClass.o BufferClass.o CommandLineClass.o

PROGRAM = ../bin/eim

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDE) $(OBJS) -o $(PROGRAM)

eim.o: eim.cpp
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDE) -c eim.cpp

EimEngineClass.o:EimEngineClass.cpp
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDE) -c EimEngineClass.cpp

BufferClass.o:BufferClass.cpp
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDE) -c BufferClass.cpp

CommandLineClass.o:CommandLineClass.cpp
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDE) -c CommandLineClass.cpp

clean:
	rm -f *.o $(PROGRAM)
