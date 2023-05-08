OBJS=coreutils.o
MAIN=main.c
INCLUDE=-I./ -I../glib_impl
LIB_INCLUDE=-L../glib_impl
LIB=-lgimpl

all: $(MAIN)

$(OBJS):%.o : %.c 
	$(CC) -c $^ ${INCLUDE} -o $@
$(MAIN): $(OBJS)
	${CC} $@ ${INCLUDE} ${LIB_INCLUDE} ${LIB} $^ -o $(patsubst %.c,%,$@)
clean:
	rm -rf *.o main
