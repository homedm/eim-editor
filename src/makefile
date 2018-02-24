CC = g++
DEST = /usr/local/bin
INCLUDE =
CFLAGS = -std=c++11 -g
LIBS = `pkg-config gtkmm-3.0 --cflags --libs gtk+-3.0`
OBJDIR = ./obj
OBJS = eim.o EimEditView.o EimEngine.o MainWindow.o
PROGRAM = ../bin/eim

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $(PROGRAM)

eim.o: eim.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c eim.cpp

EimEngine.o: EimEngine.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c EimEngine.cpp

EimEditView.o: EimEditView.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c EimEditView.cpp

MainWindow.o: MainWindow.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c MainWindow.cpp

clean:
	rm -f *.o $(PROGRAM)
