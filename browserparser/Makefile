# Компилятор.
ifeq ($(COMP), clang)
	CXX=clang++
else
	CXX=g++
endif

# Папка заголовочных файлов.
INCPATH=header

# Папка файлов исходного кода.
SRCPATH=src

# Флаги линкера.
LDFLAGS=

# Флаги компиляции.
CXXFLAGS=-I $(INCPATH) -std=c++17 -Wall -Wextra -Wshadow -Wunused -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy \
	-Wenum-compare -Wfloat-equal -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
	-Wsign-conversion -Wsign-promo -Wunreachable-code -Weffc++ 

SOURCES=$(wildcard  $(SRCPATH)/*.cpp)

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=browserparser

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -c -o $@ -MD -MP $(CXXFLAGS) $<

clean:
	rm -f $(OBJECTS) $(OBJECTS:.o=.d)
