
PROG = test

SRCS = main.c ../common/scpi-def.c ../common/scpi-proto.c ../common/DMM.c ../common/HW_control.c
CFLAGS += -Wextra -Wmissing-prototypes -Wimplicit -I ../../libscpi/inc/ -I ../common 
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
