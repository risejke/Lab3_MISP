.PHONY: all clean test format

CXX = g++
OFLAGS = -O2 -Wall -DNDEBUG
LDFLAGS = -lUnitTest++

SOURCES=modifedTableCipher.cpp main.cpp
HEADERS=headers/modifedTableCipher.h
EXECUTABLE=result

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(SOURCES) -o $(EXECUTABLE) $(OFLAGS) $(LDFLAGS)
	
test: $(EXECUTABLE)
	./$(EXECUTABLE)
	

format:
	astyle $(SOURCES) $(HEADERS)

clean:
	rm -f $(EXECUTABLE) *.orig
