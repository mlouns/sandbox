TARGET = mars
LIBS = -lmpfr -lgmp
CC = gcc
CXX = g++
#CFLAGS = -O3 -ggdb --std=c++11
CFLAGS = -g -O0 -ggdb --std=c++11 -W -Wall

default: $(TARGET)
all: default

HEADERS = $(wildcard *.h) Makefile

OBJECTS = $(TARGET).o basics.o robot.o

basics.o : $ basics.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c basics.cpp

robot.o : $ robot.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c robot.cpp

$(TARGET).o : $(TARGET).cpp $(HEADERS)
	$(CXX) $(CFLAGS) -c $(TARGET).cpp

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CFLAGS) $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -fr $(TARGET).dSYM
	-rm -f $(TARGET)

cleanest:
	-rm -f *.o
	-rm -f *~
	-rm -fr $(TARGET).dSYM
	-rm -f $(TARGET)
