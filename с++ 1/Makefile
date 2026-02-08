CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = 

SOURCES = dbms.cpp array_operations.cpp stack_operations.cpp queue_operations.cpp \
          singlyLinkedList_operations.cpp doubleLinkedList_operations.cpp tree_operations.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = dbms

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

install-deps:
	sudo apt update
	sudo apt install nlohmann-json3-dev

.PHONY: clean install-deps
