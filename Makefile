SRCDIR   = src
SRCFILES = $(SRCDIR)/isinetaddr.c $(SRCDIR)/iscidraddr.c
INCDIR   = include
TESTDIR  = test
TESTBIN  = $(TESTDIR)/runner

CC = cc
CFLAGS = -fstack-protector-all -I$(INCDIR) -Wall -Wextra -pedantic

test:
	@$(CC) $(CFLAGS) $(SRCFILES) $(TESTDIR)/isinetaddr_test.c -o $(TESTDIR)/isinetaddr
	@echo -n test/isinetaddr: ''
	@$(TESTDIR)/isinetaddr
	@$(CC) $(CFLAGS) $(SRCFILES) $(TESTDIR)/iscidraddr_test.c -o $(TESTDIR)/iscidraddr
	@echo -n test/iscidraddr: ''
	@$(TESTDIR)/isinetaddr

.PHONY: test
