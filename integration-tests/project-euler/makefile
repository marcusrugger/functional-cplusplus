
TEMPLATE_LIBRARY = ../../src

CC=g++
CFLAGS=-c -O3 -DNODEBUG -pthread -std=c++11 -I$(TEMPLATE_LIBRARY)
#CFLAGS=-c -g3 -fno-inline -O0 -pthread -std=c++11
LDFLAGS=-pthread -std=c++11 -Wl,--no-as-needed

#/usr/lib/x86_64-linux-gnu/libpthread.a

#-lncurses

SOURCE_FILES =


MAIN = project-euler

MAIN_SOURCES =	$(MAIN).cpp				\
								problem-001.cpp		\
								problem-002.cpp		\
								problem-003.cpp

MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)


all:	run


clean:
	rm *.o
	rm $(MAIN)


run:	$(MAIN)
	./project-euler


$(MAIN):	$(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(MAIN_OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
