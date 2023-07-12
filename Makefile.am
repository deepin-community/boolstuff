# $Id: Makefile.am,v 1.15 2014/03/01 17:41:03 sarrazip Exp $

SUBDIRS = src examples

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(PACKAGE)-$(API).pc

man_MANS = doc/$(PACKAGE).3 doc/booldnf.1

docdir = $(datadir)/doc/$(PACKAGE)-$(VERSION)
doc_DATA = \
	AUTHORS \
	COPYING \
	NEWS \
	README \
	THANKS

RPMBUILD = rpmbuild

rpm: dist
	$(RPMBUILD) -ta $(distdir).tar.gz

EXTRA_DIST = \
	autogen.sh \
	bootstrap \
	$(PACKAGE)-$(API).spec \
	$(PACKAGE)-$(API).pc \
	ltmain.sh \
	$(man_MANS) \
	macros/ac_cxx_have_sstream.m4 \
	macros/ac_cxx_have_std.m4 \
	macros/ac_cxx_namespaces.m4 \
	macros/getopt_long.m4 \
	macros/ac_compile_warnings.m4 \
	macros/ac_prog_perl_modules.m4

ACLOCAL_AMFLAGS = -I macros

auxdir = @ac_aux_dir@
AUX_DIST = $(auxdir)/install-sh $(auxdir)/missing $(auxdir)/mkinstalldirs

MAINTAINERCLEANFILES = \
	Makefile.in \
	aclocal.m4 \
	configure \
	sic/config-h.in \
	sic/stamp-h.in \
	$(AUX_DIST) \
	compile \
	config.guess \
	config.sub \
	depcomp \
	install-sh \
	ltmain.sh \
	missing \
	mkinstalldirs

