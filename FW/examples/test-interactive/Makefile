
PROG = test

SRCS = main.c ../common/scpi-def.c ../common/scpi-proto.c ../common/dev/DMM.c ../common/dev/HW_control.c
CFLAGS += -Wextra -Wmissing-prototypes -Wimplicit -I ../../libscpi/inc/ -I ../common -I ../common/dev
LDFLAGS += -lm ../../libscpi/dist/libscpi.a -Wl,--as-needed

.PHONY: clean all

all: $(PROG)

OBJS = $(SRCS:.c=.o)


.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(PROG) $(OBJS)
