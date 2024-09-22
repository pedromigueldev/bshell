CC=clang
CFLAGS=-g -Wall
BINS=libtest libbshell.so libbshell_s.a runtime_test static_test

all: $(BINS)

libtest: libtest.c libbshell.o
	$(CC) $(CFLAGS) -o $@ $^

runtime_test: libtest.c libbshell.so
	$(CC) $(CFLAGS) -o $@ $^ -L. -lbshell

static_test: libtest.c libbshell_s.a
	$(CC) $(CFLAGS) -o $@ $^ -L -libbshell_s

%.so: %.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< -lc
##  clang -g -Wall -fPIC -shared -o libbshell.so libbshell.c -lc

%_s.a: %.o
	ar rcs $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r main $(BINS) *.o *.so
