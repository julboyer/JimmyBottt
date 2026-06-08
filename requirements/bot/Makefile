CXXFLAGS = -std=c++17 -Wall -Wextra
DPP_FLAGS = $(shell pkg-config --cflags dpp)
DPP_LIBS = $(shell pkg-config --libs dpp)

SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(patsubst src/%.cpp,build/%.o,$(SOURCES))

prepare:
	mkdir -p target
	mkdir -p build

clean:
	rm -r target

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ -c $< -o $@ $(CXXFLAGS) $(DPP_FLAGS)

build: $(OBJECTS)
	g++ $(OBJECTS) -o target/jimmybott `pkg-config --libs dpp`

.PHONY: clean build prepare