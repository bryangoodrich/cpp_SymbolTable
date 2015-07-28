CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp HashTable.cpp ../cpp_DLList/DLList.cpp ../cpp_BSTree/BSTree.cpp ../cpp_Record/Record.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	\rm *.o $(EXECUTABLE)

