# this is my target
TARGET = main

# All .c files in this directory are my sources
SOURCES = main.cpp $(SRC_DIR)subscription_table.cpp $(SRC_DIR)mvp_agent_loader.cpp 
SOURCES += $(SRC_DIR)thread.cpp $(SRC_DIR)router.cpp $(SRC_DIR)agent_controller.cpp
SOURCES += $(SRC_DIR)condition_variable.cpp $(SRC_DIR)mutex.cpp $(SRC_DIR)event_distributor.cpp
SOURCES += $(SRC_DIR)event_distributor_mt.cpp $(SRC_DIR)thread_group.cpp
SOURCES += $(SRC_DIR)mvp_controller.cpp $(SRC_DIR)mvp_sensor.cpp

#SOURCES += $(SRC_DIR)thread_pool.cpp $(SRC_DIR)thread_group.cpp $(SRC_DIR)semaphore.cpp $(SRC_DIR)event_distributor_thread_pool.cpp

# Include directory
INC_DIR = ../../include/
SRC_DIR = ../../src/

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Werror -Wall -g3
CFLAGS += -g
CXXFLAGS = $(CFLAGS) -std=c++03
LDFLAGS = -g -pthread
CPPFLAGS = -I$(INC_DIR)


#  my objects are the .o of my sources
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY:all
all: $(TARGET)

# The default command, compile all the sources
#$(CC) $(LDFLAGS) $(^) -o $(@)

$(TARGET): $(OBJECTS)

#built-in c compiler rule is $(CC) $(CFLAGS) $(CPPFLAGS) -c  -o $(@) $(<)

#spacial targets
.PHONY:clean
clean:
	rm -f $(TARGET) *.o *.out *.log *.txt
	rm -f $(SRC_DIR)*.o

.PHONY:run
run: $(TARGET)
	./$(TARGET) -v

.PHONY:valgrind
valgrind:	$(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY:drd
drd:  $(TARGET)
	valgrind --tool=drd --log-file=drd.log ./$(TARGET)

.PHONY:helgrind
helgrind:  $(TARGET)
	valgrind --tool=helgrind --log-file=helgrind.log ./$(TARGET)
