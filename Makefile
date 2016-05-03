TARGET=lib/librbtree.so
OBJECTS=rbtree.o
XX=g++
INCLUDE=./src/
CXXFLAGS=-std=c++11 -I ${INCLUDE} -fPIC

all:$(TARGET)
$(TARGET): $(OBJECTS)
	mkdir -p lib
	${XX} -o $(TARGET) -shared $(OBJECTS)
%.o: ${INCLUDE}%.cpp
	${XX} ${CXXFLAGS} -c "$<" -o "$@"
clean:
	rm -f *.o
