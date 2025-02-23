VERSION = 2.1.0
LIBNAME = scpi

# STM32 Kompilátor a Linker
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

# STM32 Specifické flagy
MCU = -mcpu=cortex-m3 -mthumb
CFLAGS = $(MCU) -Wextra -Wmissing-prototypes -Wimplicit -Iinc -Os -ffunction-sections -fdata-sections
CFLAGS_SHARED = $(CFLAGS) -fPIC
LDFLAGS = -Wl,--gc-sections

# Cesty
OBJDIR = obj
DISTDIR = dist

# Knihovny
STATICLIBFLAGS = rcs
STATICLIB = lib$(LIBNAME).a

# Seznam zdrojových souborů
SRCS = $(addprefix src/, \
    error.c fifo.c ieee488.c \
    minimal.c parser.c units.c utils.c \
    lexer.c expression.c \
    )

# Výstupní objektové soubory
OBJS_STATIC = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

# Hlavičkové soubory
HDRS = $(addprefix inc/scpi/, \
    scpi.h constants.h error.h \
    ieee488.h minimal.h parser.h types.h units.h \
    expression.h \
    ) \
    $(addprefix src/, \
    lexer_private.h utils_private.h fifo_private.h \
    parser_private.h \
    ) \

.PHONY: all clean static install

all: static

static: $(DISTDIR)/$(STATICLIB)

clean:
	$(RM) -r $(OBJDIR) $(DISTDIR)

install: $(DISTDIR)/$(STATICLIB)
	test -d $(PREFIX) || mkdir -p $(PREFIX)
	test -d $(LIBDIR) || mkdir -p $(LIBDIR)
	test -d $(INCDIR) || mkdir -p $(INCDIR)
	test -d $(INCDIR)/scpi || mkdir -p $(INCDIR)/scpi
	install -m 0644 $(DISTDIR)/$(STATICLIB) $(LIBDIR)
	install -m 0644 inc/scpi/*.h $(INCDIR)/scpi

$(OBJDIR):
	mkdir -p $@

$(DISTDIR):
	mkdir -p $@

$(OBJDIR)/%.o: src/%.c $(HDRS) | $(OBJDIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(DISTDIR)/$(STATICLIB): $(OBJS_STATIC) | $(DISTDIR)
	$(AR) $(STATICLIBFLAGS) $@ $(OBJS_STATIC)
