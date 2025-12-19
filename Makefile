CC             = cc
# Release options
CFLAGS         = -Wall -Wextra -pedantic -O2 
TARGET         = build/crbc
# Debug options
DEBUG_CFLAGS   = -Wall -Wextra -pedantic -O0 -fsanitize=address,undefined -g
DEBUG_TARGET   = debug/crbc
# Source
SRC            = src/rbc.c
# Install targets
PREFIX        ?= /usr/local
BINDIR         = $(PREFIX)/bin
INSTALL_TARGET = crbc
INSTALL_DEBUG_TARGET = $(INSTALL_TARGET)_debug

# Compile all
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	$(CC) $(DEBUG_CFLAGS) $(SRC) -o $(DEBUG_TARGET)

# Compile release (same as 'make')
release:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Compile debug
rebug:
	$(CC) $(DEBUG_CFLAGS) $(SRC) -o $(DEBUG_TARGET)

# Clean all (release + debug)
clean cleanall:
	rm -f $(TARGET)
	rm -f $(DEBUG_TARGET)

# Clean release
CleanRelease:
	rm -f $(TARGET)

# Clean debug
CleanDebug:
	rm -f $(DEBUG_TARGET)

# Install all (release + debug)
Install:
	install -Dm755 $(INSTALL_TARGET) $(BINDIR)/crbc
	install -Dm755 $(INSTALL_DEBUG_TARGET) $(BINDIR)/crbc

# Install release
InstallRelease:
	install -Dm755 $(INSTALL_TARGET) $(BINDIR)/crbc

# Install debug
InstallDebug:
	install -Dm755 $(INSTALL_DEBUG_TARGET) $(BINDIR)/crbc

# Uninstall all
Uninstall:
	rm -f $(BINDIR)/$(INSTALL_TARGET)
	rm -f $(BINDIR)/$(INSTALL_DEBUG_TARGET)
