OBJS=coreutils.o
MAIN=main.c
INCLUDE=-I./ -I../glib_impl
LIB_INCLUDE=-L../glib_impl
LIB=-lgimpl
include config.mk
FLAGS=-D_TARGET="${TARGET}"

all: $(MAIN)

$(OBJS):%.o : %.c 
	$(CC) -c $^ ${INCLUDE} -o $@
$(MAIN): $(OBJS)
	${CC} $@ ${INCLUDE} ${LIB_INCLUDE} ${LIB} ${FLAGS} $^ -o ${TARGET}
clean:
	rm -rf *.o ${TARGET}
