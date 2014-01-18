
CC=g++
#CFLAGS=-c -O3 -DNODEBUG -pthread -std=c++11
CFLAGS=-c -g3 -fno-inline -O0 -pthread -std=c++11
LDFLAGS=-pthread -std=c++11 -Wl,--no-as-needed

#/usr/lib/x86_64-linux-gnu/libpthread.a

#-lncurses

SOURCE_FILES =


TEST_MAIN = test.main

TEST_MAIN_SOURCES =	$(TEST_MAIN).cpp						\
										test.iterators.executor.cpp	\
										test.iterators.foreach.cpp

TEST_MAIN_OBJECTS = $(TEST_MAIN_SOURCES:.cpp=.o)


MAIN = main

MAIN_SOURCES =	$(MAIN).cpp

MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)


all:	$(TEST_MAIN)	\
			$(MAIN)


clean:
	rm *.o
	rm $(TEST_MAIN)
	rm $(MAIN)


$(TEST_MAIN):	$(TEST_MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_MAIN_OBJECTS) -o $@


$(MAIN):	$(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(MAIN_OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
