# Declaration of variables
CC = g++
#CC_FLAGS = -Wall -Werror -Wextra -std=c++17 -g
#CC_FLAGS = -Werror -Wextra -std=c++17 -O3
CC_FLAGS = -Werror -Wextra -std=c++17 -pg -no-pie -O3

# File names
EXEC = raytracer
SOURCES = $(filter-out $(wildcard *.t.cpp), $(wildcard *.cpp))
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
#	$(CC) $(OBJECTS) -o $(EXEC)
	$(CC) $(OBJECTS) -o $(EXEC) -pg -no-pie

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
