#all:
#	gcc lib/*.c test.c -Iinclude/ -O3 -W -Wall -o test

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -Iinclude/
LDFLAGS = -shared
RM = rm -f
TARGET_LIB = librm_malloc.so

SRCS = lib/rm_attach.c \
	lib/rm_create_state.c \
	lib/rm_destroy_state.c \
	lib/rm_detach.c \
	lib/rm_hash.c \
	lib/rm_malloc.c \
	lib/rm_release.c \
	lib/rm_retain.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
