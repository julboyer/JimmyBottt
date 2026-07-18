CXXFLAGS = -std=c++17 -Wall -Wextra
DPP_FLAGS = $(shell pkg-config --cflags dpp)
DPP_LIBS = $(shell pkg-config --libs dpp)

NAME=jimmybottt
SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(patsubst src/%.cpp,build/%.o,$(SOURCES))

all: ${NAME}

prepare:
	mkdir -p build

clean:
	rm -r build

fclean: clean
	rm -r target

build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ -I ./src -c $< -o $@ $(CXXFLAGS) $(DPP_FLAGS)

re: fclean all

build: ${NAME}

${NAME}: $(OBJECTS)
	mkdir -p target
	g++ $(OBJECTS) -o target/${NAME} `pkg-config --libs dpp`

.PHONY: clean build prepare all fclean re