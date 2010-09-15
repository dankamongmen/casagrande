.DELTE_ON_ERROR:
.DEFAULT_GOAL:=test
.PHONY: all bin test clean

SRC:=src
TAGS:=.tags
PROJ:=casagrande

CINC:=$(wildcard $(SRC)/*.h)
CSRC:=$(wildcard $(SRC)/*.cpp)
COBJ:=$(SRC:%.cpp:%.o)
CBIN:=$(PROJ)

CFLAGS+=-I$(SRC) -fvisibility=hidden -O2 -Wall -W -Werror
LFLAGS+=-Wl,-O,--default-symver,--enable-new-dtags,--as-needed,--warn-common
CTAGS?=$(shell (which ctags || echo ctags) 2> /dev/null)

all: $(TAGS) bin

bin: $(CBIN)

$(PROJ): $(CSRC) $(CINC)
	$(CXX) $(CFLAGS) -o $@ $< $(LFLAGS)

test: all
	for test in $(BIN) ; do ./$$test ; done

$(TAGS): $(CSRC) $(CINC)
	$(CTAGS) -o $@ $^

clean:
	rm -rf $(TAGS) $(COBJ) $(CBIN)
