
ROOT_DIR = ../..
TEMPLATE_LIBRARY = $(ROOT_DIR)/src

CC=g++
#CFLAGS=-c -O3 -DNODEBUG -pthread -std=c++11 -I$(TEMPLATE_LIBRARY)
#CFLAGS=-c -O2 -DNODEBUG -pthread -std=c++11 -I$(TEMPLATE_LIBRARY)
CFLAGS=-c -g3 -Og -pthread -std=c++11 -I$(TEMPLATE_LIBRARY)
LDFLAGS=-pthread -std=c++11 -Wl,--no-as-needed

#/usr/lib/x86_64-linux-gnu/libpthread.a

#-lncurses

SOURCE_FILES =


MAIN = parse-stream

MAIN_SOURCES =	$(MAIN).cpp

MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)


all:	run


clean:
	rm *.o
	rm $(MAIN)


run:	$(MAIN)
	./$(MAIN) > stdout.txt; wc stdout.txt


$(MAIN):	$(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(MAIN_OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
