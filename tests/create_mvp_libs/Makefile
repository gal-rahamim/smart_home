# All .c files in this directory are my sources
SOURCES = $(SRC_DIR)mvp_controller.cpp $(SRC_DIR)mvp_sensor.cpp $(SRC_DIR)thread.cpp $(SRC_DIR)mutex.cpp

# Include directory
INC_DIR = ../../include/
SRC_DIR = ../../src/

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Werror -Wall -g3
CFLAGS += -g -shared -fPIC
CXXFLAGS = $(CFLAGS) -std=c++03
LDFLAGS = -g -pthread
CPPFLAGS = -I$(INC_DIR)


#  my objects are the .o of my sources
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY:all
all: $(OBJECTS) mvp_sensor mvp_controller

# The default command, compile all the sources
#$(CC) $(LDFLAGS) $(^) -o $(@)

#main: LDLIBS += -ldl

#built-in c compiler rule is $(CC) $(CFLAGS) $(CPPFLAGS) -c  -o $(@) $(<)

#.c.o:
#	$(CC) $(CFLAGS) -c $< -o $@

mvp_sensor.o: CFLAGS += -shared -fPIC
mvp_sensor: $(SRC_DIR)mvp_sensor.o $(SRC_DIR)thread.o
	$(CC) -shared -Wl,-soname,libmvp_sensor.so $^ -o libmvp_sensor.so
	$(RM) ../mvp1_libs/libmvp_sensor.so	
	ln libmvp_sensor.so ../mvp1_libs

mvp_controller.o: CFLAGS += -shared -fPIC
mvp_controller: $(SRC_DIR)mvp_controller.o $(SRC_DIR)mutex.o
	$(CC) -shared -Wl,-soname,libmvp_controller.so $^ -o libmvp_controller.so
	$(RM) ../mvp1_libs/libmvp_controller.so
	ln libmvp_controller.so ../mvp1_libs

#spacial targets
.PHONY:clean
clean:
	rm -f *.o *.out *.log *.txt core
	rm -f $(SRC_DIR)*.o
