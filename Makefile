.POSIX:
.SUFFIXES:

include config.mk

# flags for compiling
BLENDCPPFLAGS = -I. -DWLR_USE_UNSTABLE -DVERSION=\"$(VERSION)\"

# Wayland utils
WAYLAND_PROTOCOLS = `pkg-config --variable=pkgdatadir wayland-protocols`
WAYLAND_SCANNER   = `pkg-config --variable=wayland_scanner wayland-scanner`

# CFLAGS / LDFLAGS
PKGS      = wlroots wayland-server xkbcommon libinput lua5.4 $(XLIBS)
BLENDCFLAGS = `pkg-config --cflags $(PKGS)` $(BLENDCPPFLAGS) $(CFLAGS) $(XWAYLAND)
LDLIBS    = `pkg-config --libs $(PKGS)` $(LIBS)

# build rules

# wayland-scanner is a tool which generates C headers and rigging for Wayland
# protocols, which are specified in XML. wlroots requires you to rig these up
# to your build system yourself and provide them in the include path.
all: blend
blend: blend.o util.o
	$(CC) blend.o util.o $(LDLIBS) $(LDFLAGS) -o $@
blend.o: blend.c config.mk config.h client.h xdg-shell-protocol.h wlr-layer-shell-unstable-v1-protocol.h idle-protocol.h
util.o: util.c util.h

# wayland scanner rules to generate .h / .c files
xdg-shell-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@
wlr-layer-shell-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/wlr-layer-shell-unstable-v1.xml $@
idle-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/idle.xml $@

clean:
	rm -f blend *.o *-protocol.h

# distribution archive
dist: clean
	mkdir -p blend-$(VERSION)
	cp -R LICENSE* Makefile README.md generate-version.sh client.h\
		config.def.h config.mk protocols blend.c util.c util.h\
		blend-$(VERSION)
	echo "echo $(VERSION)" > blend-$(VERSION)/generate-version.sh
	tar -caf blend-$(VERSION).tar.gz blend-$(VERSION)
	rm -rf blend-$(VERSION)

# install rules

install: blend
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f blend $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/blend
	mkdir -p $(DESTDIR)$(MANDIR)/man1
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/blend

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CPPFLAGS) $(BLENDCFLAGS) -c $<
