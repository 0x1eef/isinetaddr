SRCDIR = src
INCDIR = include
TESTDIR = test
TESTBIN = $(TESTDIR)/runner

CC = cc
CFLAGS = -I$(INCDIR) -Wall -Wextra -pedantic

test:
	$(CC) $(CFLAGS) $(SRCDIR)/isinetaddr.c $(TESTDIR)/isinetaddr_test.c -o $(TESTBIN)
	$(TESTBIN)

.PHONY: test
