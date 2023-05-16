#!/usr/bin/make
.SUFFIXES:
.PHONY: all run pack clean

LEX = flex
TAR = urlscanner

CSRC = testurlscanner.c
LSRC = urlscanner.l
OBJ = $(LSRC:%.l=%.o) $(CSRC:%.c=%.o)
DEP = $(OBJ:%.o=%.d)
-include $(DEP)

CFLAGS = -std=c11 -Wall -pedantic -MMD -MP -DLEXDEBUG
LFLAGS = -t

%.c: %.l
	$(LEX) $(LFLAGS) $< > $@
%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TAR): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

all: $(TAR)

run: all
	./$(TAR) testeingabe.html

pack:
	@$(MAKE) -C .. pack

clean:
	$(RM) $(RMFILES) $(TAR) $(OBJ) $(DEP) $(LSRC:%.l=%.c)
