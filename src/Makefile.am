AUTOMAKE_OPTIONS = gnu

plugin_LTLIBRARIES = libdlvhexplugin-sparql.la

AM_CPPFLAGS= -I$(top_srcdir)/include \
             $(DEBUG_FLAGS) \
             $(BOOST_CPPFLAGS) \
             $(DLVHEX_CFLAGS) \
			 $(SOPRANO_CFLAGS) \
			 $(QT_CFLAGS)

libdlvhexplugin_sparql_la_SOURCES = SparqlPlugin.cpp \
									SparqlAtom.cpp

libdlvhexplugin_sparql_la_LDFLAGS =-version-info="" -avoid-version -module $(SOPRANO_LIBS)

libdlvhexplugin-sparql-static.la: $(libdlvhexplugin_sparql_la_OBJECTS)
	$(CXXLINK) -avoid-version -module -rpath $(plugindir) $(libdlvhexplugin_sparql_la_OBJECTS)

install-static: libdlvhexplugin-sparql-static.la
	$(LIBTOOL) --mode=install $(INSTALL) -s libdlvhexplugin-sparql-static.la $(DESTDIR)$(plugindir)/libdlvhexplugin-sparql-static.la

uninstall-static:
	$(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(plugindir)/libdlvhexplugin-sparql-static.la
