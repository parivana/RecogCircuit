.SUFFIXES : .cpp.o

CXX=g++
CXXFLAGS=-g -I/usr/local/include/
LDFLAGS=-L/usr/local/lib/ -lm -lopencv_core -lopencv_highgui

TARGET=RecogCircuit.out
OBJS=RecogCircuit.o Recognition.o Element.o Analysis.o DescWriter.o \
	 Wire.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

tag :
	ctags -R *

clean : 
	rm -f $(OBJS) $(TARGET) *.cir
