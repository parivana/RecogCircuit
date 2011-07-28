.SUFFIXES : .cpp.o

CXX=g++
CXXFLAGS=-g -I/usr/local/include/
LDFLAGS=-L/usr/local/lib/ -lopencv_core -lopencv_highgui

TARGET=RecogCircuit.out
OBJS=RecogCircuit.o Recognition.o DescWriter.o LinkedList.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean : 
	rm -f $(OBJS) $(TARGET)
