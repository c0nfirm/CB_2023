#!/usr/bin/make
.SUFFIXES:
.PHONY: all run pack clean

PCK = lab-2.zip

all:
	@$(MAKE) -C c1-scanner all
	@$(MAKE) -C urlscanner all

run:
	@$(MAKE) -C c1-scanner run
	@$(MAKE) -C urlscanner run

pack:
	zip -vj $(PCK) c1-scanner/minako-lexic.l urlscanner/urlscanner.l -x "*/.*"

clean:
	@$(MAKE) -C c1-scanner clean
	@$(MAKE) -C urlscanner clean
	$(RM) $(RMFLAGS) $(PCK)
