OBJS=coreutils.o
MAIN=main.c
INCLUDE=-I./ -I../glib_impl
LIB_INCLUDE=-L../glib_impl
LIB=-lgimpl
include config.mk
FLAGS=-D_TARGET="${TARGET}" -Wall -O3

all: $(TARGET)

$(OBJS):%.o : %.c 
	$(CC) -c $^ ${INCLUDE} ${FLAGS} -o $@
$(TARGET): $(MAIN) $(OBJS)
	${CC} $^ ${INCLUDE} ${LIB_INCLUDE} ${LIB} ${FLAGS} -o $@
clean:
	rm -rf *.o ${TARGET}
