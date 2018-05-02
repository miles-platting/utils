CC = g++                  
CFLAGS = -c -Wall -g
CXXFLAGS += -std=c++11
LDFLAGS += -L.
SOURCES = utils.cpp
TARGET_SRC = test-utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OUT = libutils.a
EXE = test-utils

test: $(OUT)
	$(CC) -o $(EXE) $(EXE).cpp $(LDFLAGS) $(OUT) $(CXXFLAGS)

$(OUT): $(OBJECTS)
	ar rcs $(OUT) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

strip:
	strip $(EXE)

show:
	@echo $(OUT)
	@echo $(EXE)
	@echo $(OBJECTS)
	
clean:
	@echo "Cleaning " $(OUT) " and " $(EXE)
	rm $(OUT)
	rm $(EXE)
	rm $(OBJECTS)

hello:
	@echo "hello"