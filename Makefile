LIB_NAME=ehstr

AUX_INCLUDES=-I ../libecheck
AUX_A_FILES=../libecheck/libecheck.a
AUX_LDFLAGS=-L../libecheck -lecheck
AUX_LD_LIBRARY_PATHS=:../libecheck


UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
SHAREDFLAGS = -dynamiclib
SHAREDEXT = dylib
else
SHAREDFLAGS = -shared
SHAREDEXT = so
endif

ifeq ("$(PREFIX)", "")
PREFIX=/usr/local
endif

ifeq ("$(LIBDIR)", "")
LIBDIR=$(PREFIX)/lib
endif

ifeq ("$(INCDIR)", "")
INCDIR=$(PREFIX)/include
endif

LIB_SRC=$(LIB_NAME).c
LIB_HDR=$(LIB_NAME).h
LIB_OBJ=$(LIB_SRC:.c=.o)
SO_OBJS=$(LIB_NAME).o
SO_NAME=lib$(LIB_NAME).$(SHAREDEXT)
ifneq ($(UNAME), Darwin)
    SHAREDFLAGS += -Wl,-soname,$(SO_NAME)
endif

A_NAME=lib$(LIB_NAME).a

INCLUDES=-I.
TEST_SRC=test-$(LIB_NAME).c
TEST_OBJ=test-$(LIB_NAME).o
TEST_OUT=test-$(LIB_NAME)

CSTD_CFLAGS=-std=c89
#CSTD_CFLAGS=-std=c11
#DEBUG_CFLAGS=-ggdb -O0
DEBUG_CFLAGS=-Os
NOISY_CFLAGS=-Wall -Wextra -pedantic -Werror

CFLAGS += $(CSTD_CFLAGS) $(DEBUG_CFLAGS) $(NOISY_CFLAGS)
LDFLAGS += -L. -l$(LIB_NAME)
CC=gcc

ifeq ("$(LIBDIR)", "")
LIBDIR=/usr/local/lib
endif

ifeq ("$(INCDIR)", "")
INCDIR=/usr/local/include
endif

LD_LIBRARY_PATH=.$(AUX_LD_LIBRARY_PATHS)

# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

default: $(LIB_NAME)

.c.o:
	$(CC) -c -fPIC $(CFLAGS) $< -o $@

$(SO_NAME): $(LIB_OBJ)
	$(CC) $(SHAREDFLAGS) -o $(SO_NAME).1.0 $(SO_OBJS)
	ln -sf ./$(SO_NAME).1.0 ./$(SO_NAME).1
	ln -sf ./$(SO_NAME).1.0 ./$(SO_NAME)

$(A_NAME): $(LIB_OBJ)
	ar -r $(A_NAME) $(SO_OBJS)

$(LIB_NAME): $(SO_NAME) $(A_NAME)
	@echo $(UNAME) $(LIB_NAME) library files:
	@ls -1 $(SO_NAME)* *.a

tests: $(LIB_NAME)
	$(CC) -c $(INCLUDES) $(AUX_INCLUDES) $(CFLAGS) -o $(TEST_OBJ) \
		$(TEST_SRC)
	$(CC) $(TEST_OBJ) $(A_NAME) $(AUX_A_FILES) -o $(TEST_OUT)-static
	$(CC) $(TEST_OBJ) $(LDFLAGS) $(AUX_LDFLAGS) -o $(TEST_OUT)-dynamic

check: tests
	./$(TEST_OUT)-static
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) ./$(TEST_OUT)-dynamic

tidy:
	$(LINDENT) \
		-T FILE \
		-T size_t \
		*.h *.c

clean:
	rm -f *.o *.a *.$(SHAREDEXT) $(SO_NAME).* \
		$(TEST_OUT)-static $(TEST_OUT)-dynamic

install: $(LIB_NAME)
	@echo "Installing $(LIB_NAME) $(UNAME) libraries in $(LIBDIR)"
	@mkdir -pv $(LIBDIR)
	@cp -pv $(A_NAME) $(LIBDIR)/
	@cp -Rv $(SO_NAME)* $(LIBDIR)/
	@echo "Installing $(LIB_NAME) headers in $(INCDIR)"
	@mkdir -pv $(INCDIR)
	@cp -pv $(LIB_HDR) $(INCDIR)/
