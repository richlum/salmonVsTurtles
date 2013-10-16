# OS X
ifeq ("$(shell uname)", "Darwin")
  CXXFLAGS = -I/usr/include
  LIB = -framework OpenGL -framework GLUT

# Linux 
else
  CXXFLAGS = -I/usr/include 
  LIB = -lGL -lGLU -lglut
endif


BIN=a1
OBJ=$(BIN).o salmon.o turtle.o bubble.o

all: build

default: build
	
build: $(BIN)

test: build
	./$(BIN)

%.o: %.cpp
	g++ -c $(CXXFLAGS) -o $@ $<

$(BIN): $(OBJ)
	g++ -o $@ $(OBJ) $(LIB)

clean:
	- rm -f $(BIN) $(OBJ)
