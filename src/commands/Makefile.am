# $Id: Makefile.am,v 1.14 2014/03/01 16:00:06 sarrazip Exp $

bin_PROGRAMS = booldnf

booldnf_SOURCES = booldnf.cpp

booldnf_CXXFLAGS = \
	-I$(top_srcdir)/src \
	-DCOMMAND_NAME=\"booldnf\"

booldnf_LDADD = ../boolstuff/libboolstuff-$(API).la

check: all
if HAVE_GETOPT_LONG
	test "`./booldnf --version`" = "booldnf $(VERSION)"
	@echo "Testing exit status when requesting help page:"
	./booldnf --help >/dev/null
	@echo "Testing exit status when passing unknown option:"
	./booldnf --unknown >/dev/null; test "$$?" = 1
endif
	test "_`./booldnf </dev/null`" = _
	$(PERL) -cw $(srcdir)/test-regressions.pl
	$(PERL) $(srcdir)/test-regressions.pl $(srcdir)/regressions.txt ./booldnf

EXTRA_DIST = test-regressions.pl regressions.txt

MAINTAINERCLEANFILES = Makefile.in
