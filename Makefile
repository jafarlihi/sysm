TARGET:=sysm

SOURCES:=./sources
INCLUDES:=./headers

ifeq ($(MAKECMDGOALS),build)
	BUILD:=./build
else ifeq ($(MAKECMDGOALS),debug)
	BUILD:=./build/debug
else
	BUILD:=./build
endif

CC:=g++
CFLAGS:=-std=c++20 -I$(INCLUDES) -lsfml-audio

CFILES:=$(shell find $(SOURCES) -printf '%P ' -name '*.cc')
OFILES:=$(patsubst %.cc,$(BUILD)/%.o,$(CFILES))

.PHONY: install build debug clean mkdir
.DEFAULT_GOAL:=build

install: build
	cp -R ./sysm ~/.config/.
	mkdir -p ~/.local/bin
	cp sysm.elf ~/.local/bin/sysm

build: mkdir $(OFILES)
	$(CC) $(OFILES) -o $(TARGET).elf $(CFLAGS)

debug: CFLAGS+=-O0 -ggdb -D DEBUG
debug: mkdir $(OFILES)
	$(CC) $(OFILES) -o $(TARGET).debug.elf $(CFLAGS)

mkdir:
	mkdir -p $(BUILD)

clean:
	-rm -rf $(BUILD)
	-rm -f $(TARGET).elf
	-rm -f $(TARGET).debug.elf

$(OFILES): $(BUILD)/%.o: $(SOURCES)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@
