# $Id: Makefile.am,v 1.7 2015/01/21 03:00:42 sarrazip Exp $

check_PROGRAMS = example c-example non-string-nodes

example_SOURCES = example.cpp
example_CXXFLAGS = -I$(top_srcdir)/src
example_LDADD = -L../src/boolstuff -lboolstuff-$(API)

c_example_SOURCES = c-example.c
c_example_CFLAGS = -I$(top_srcdir)/src
c_example_LDADD = -L../src/boolstuff -lboolstuff-$(API)

non_string_nodes_SOURCES = non-string-nodes.cpp
non_string_nodes_CXXFLAGS = -I$(top_srcdir)/src
non_string_nodes_LDADD = -L../src/boolstuff -lboolstuff-$(API)

EXTRA_DIST = \
	test-booldnf.pl

check:
	test "`echo '!(a|b)' | ./example | grep ^Disj`" = \
				"Disjunctive normal form : !a&!b"
	test "`echo '!(a|b)' | ./c-example | grep ^Disj`" = \
				"Disjunctive normal form : !a&!b"
	$(PERL) -cw $(srcdir)/test-booldnf.pl
	test "`echo a | $(PERL) $(srcdir)/test-booldnf.pl ../src/commands/booldnf`" = "Response: a"

MAINTAINERCLEANFILES = Makefile.in
