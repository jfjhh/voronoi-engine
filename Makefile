#
# Perfect Ostrove Blosssom Makefile.
# Alex Striff.
#

PROJNAME   = pob
VERSION    = v0.0.1

MKDIR_P    = mkdir -p

SRCDIR     = src
BUILDDIR   = $(CURDIR)
MEDIA_PATH = $(CURDIR)/media/

EXENAME    = $(BUILDDIR)/$(PROJNAME)

CXX        = g++
CXXHEADERS = $(wildcard $(SRCDIR)/*.hpp) $(wildcard $(SRCDIR)/*.h)
CXXSOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.c)
CXXOBJECTS = $(patsubst %.cpp, %.o, $(CXXSOURCES))

# SDL Configuration.
SDLCONFIG  = sdl2-config
MACROS     = -DMEDIA_PATH=\"$(MEDIA_PATH)\" -DVERSION=\"$(VERSION)\"
CXXFLAGS   = -g -Wall -Werror -O2 -std=c++11 $(MACROS)
CPPFLAGS  := $(shell $(SDLCONFIG) --cflags)
EXTLIBS   := -lSDL2_image -lSDL2_ttf -lSDL2_gfx #-lSDL2_mixer
LIBS      := $(shell $(SDLCONFIG) --libs) $(EXTLIBS)

# pkg-config Configuration.
# PACKAGES   = sdl2
# PKGCONFIG  = pkg-config
# CPPFLAGS  := $(shell $(PKGCONFIG) --cflags $(PACKAGES))
# LIBS      := $(shell $(PKGCONFIG) --libs $(PACKAGES) -ldl)


all: directories $(EXENAME)


$(EXENAME): $(CXXOBJECTS)
	$(LINK.cc) -rdynamic $^ $(LIBS) -o $@

$(CXXOBJECTS): $(CXXHEADERS)

directories:
	@$(MKDIR_P) $(BUILDDIR)

print-% : ; $(info $* is $(flavor $*) variable set to [$($*)]) @true

clean:
	@$(RM) -rfv **/*.o **/*.so **/*~ $(EXENAME)

.PHONY: all directories clean print-%

