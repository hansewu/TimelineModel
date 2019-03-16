include ../mlt/config.mak

CXXFLAGS+=-std=c++11
CXXFLAGS += -I"$(DESTDIR)$(prefix)/include/mlt++"
CXXFLAGS += -I"$(DESTDIR)$(prefix)/include/mlt"
CXXFLAGS += -Imltext/include
CXXFLAGS += -Iundo
LDFLAGS += -L../mlt/src/framework -lmlt -lm -L../mlt/src/mlt++ -lmlt++

TARGET = libtimelinemodel$(LIBSUF)
CXXFLAGS += -DMLTPP_EXPORTS
LIBFLAGS += -Wl,--output-def,libtimelinemodel.def

OBJS =  mltext/src/mltext_consumer.o \
        mltext/src/mltext_frame.o \
		undo/undo_history.o

SRCS := $(OBJS:.o=.cpp)

all: 	$(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(SHFLAGS) -o $@ $(OBJS) $(LDFLAGS)

depend:	$(SRCS)
		$(CXX) -MM $(CXXFLAGS) $^ 1>.depend

distclean:	clean
		rm -f .depend

clean:	
		rm -f $(OBJS) $(TARGET)

install:
	install -d $(DESTDIR)$(libdir)
	if [ "$(targetos)" = "MinGW" ]; then \
		install -m 755 $(TARGET) $(DESTDIR)$(prefix) ; \
		install -m 755 $(TARGET) $(DESTDIR)$(libdir)/libtimelinemodel.dll ; \
		install -m 644 libtimelinemodel.def $(DESTDIR)$(libdir) ; \
	else \
		install -m 755 $(TARGET) $(DESTDIR)$(libdir) ; \
		ln -sf $(TARGET) $(DESTDIR)$(libdir)/$(SONAME) ; \
		ln -sf $(TARGET) $(DESTDIR)$(libdir)/$(NAME) ; \
	fi
	install -d "$(DESTDIR)$(prefix)/include"
	install -m 644 $(INCS) "$(DESTDIR)$(prefix)/include"

uninstall:
	rm -f "$(DESTDIR)$(libdir)/$(TARGET)"
	if [ "$(targetos)" != "MinGW" ]; then \
		rm -f "$(DESTDIR)$(libdir)/$(SONAME)" ; \
		rm -f "$(DESTDIR)$(libdir)/$(NAME)" ; \
	fi
ifneq ($(wildcard .depend),)
include .depend
endif
