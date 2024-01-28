# command name
CMD := scm

# compilation files
SRC_FILES := $(shell find src -name "*.cpp")
OBJ_FILES := $(SRC_FILES:%.cpp=bin/objs/%.o)
DEP_FILES := $(SRC_FILES:%.cpp=bin/objs/%.d)

# compiler config
CC       := clang++
INCLUDE  := -Iinclude/
LDFLAGS  := -L/usr/lib -lstdc++ -lm
#  -Wl, -d
CPPFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -MMD -MP

# compilation steps
MAKEFLAGS += -j$(shell sysctl hw.ncpu | grep -o '[0-9]\+')

bin/cmd/$(CMD): $(OBJ_FILES)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

bin/objs/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

bin:
	-@mkdir -p bin/objs
	-@mkdir -p bin/cmd

-include $(DEP_FILES)

# make commands
.PHONY: all run debug release clean 

all: bin bin/cmd/$(CMD)

run: bin/cmd/$(CMD)
	clear
	./$< examples/main.scm

debug: CPPFLAGS += -g -DDEBUG
debug: all

release: CPPFLAGS += -O2
release: all

clean:
	-@rm -rvf bin
