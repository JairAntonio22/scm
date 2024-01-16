# command name
CMD := scm

# compilation files
SRC_FILES := $(shell find src -name "*.cpp")
OBJ_FILES := $(SRC_FILES:%.cpp=bin/objs/%.o)

# compiler config
CC       := clang++
INCLUDE  := -Isrc/
LDFLAGS  := -L/usr/lib -lstdc++ -lm
CPPFLAGS := -std=c++20 -Wall -Wextra -Wpedantic

# compilation steps
bin/cmd/$(CMD): $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

bin/objs/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

# make options
all: bin bin/cmd/$(CMD)

bin:
	-@mkdir -p bin/objs
	-@mkdir -p bin/cmd

run: bin/cmd/$(CMD)
	./$<

debug: CPPFLAGS += -g
debug: all

release: CPPFLAGS += -O2
release: all

clean:
	-@rm -rvf bin

.PHONY: all build clean debug release
