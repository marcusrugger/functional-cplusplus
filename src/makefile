
CC=g++
#CFLAGS=-c -O3 -DNODEBUG -pthread -std=c++11
#CFLAGS=-c -O2 -DNODEBUG -pthread -std=c++11
CFLAGS=-c -g3 -Og -pthread -std=c++11
LDFLAGS=-pthread -std=c++11 -Wl,--no-as-needed

#/usr/lib/x86_64-linux-gnu/libpthread.a

#-lncurses

SOURCE_FILES =


TEST_MAIN = test.main

TEST_MAIN_SOURCES =	$(TEST_MAIN).cpp														\
										test.foreach.foreach_executor.cpp						\
										test.foreach.foreach.cpp										\
										test.until.cpp															\
										test.fmap.fmap.cpp													\
										test.enumerator.forward_enumerator.cpp			\
										test.enumerator.backward_enumerator.cpp			\
										test.iterators.index_forward_iterator.cpp		\
										test.iterators.index_backward_iterator.cpp	\
										test.string.string.cpp											\
										test.vector.cpp

TEST_MAIN_OBJECTS = $(TEST_MAIN_SOURCES:.cpp=.o)


MAIN = main

MAIN_SOURCES =	$(MAIN).cpp

MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)


all:	$(TEST_MAIN)	\
			$(MAIN)				\
			unit_tests


clean:
	rm *.o
	rm $(TEST_MAIN)
	rm $(MAIN)


unit_tests:	$(TEST_MAIN)
	@echo "Running unit tests..."
	./$(TEST_MAIN) 2> log.err | tee log.out | grep "Success" | wc; cat log.err


$(TEST_MAIN):	$(TEST_MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_MAIN_OBJECTS) -o $@


$(MAIN):	$(MAIN_OBJECTS)
	$(CC) $(LDFLAGS) $(MAIN_OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
