SRCDIR = src
INCDIR = include
TESTDIR = test
TESTBIN = $(TESTDIR)/runner

CC = cc
CFLAGS = -fstack-protector-all -I$(INCDIR) -Wall -Wextra -pedantic

test:
	@$(CC) $(CFLAGS) $(SRCDIR)/isinetaddr.c $(TESTDIR)/isinetaddr_test.c -o $(TESTDIR)/isinetaddr
	@echo -n test/isinetaddr: ''
	@$(TESTDIR)/isinetaddr
	@$(CC) $(CFLAGS) $(SRCDIR)/isinetaddr.c $(TESTDIR)/iscidraddr_test.c -o $(TESTDIR)/iscidraddr
	@echo -n test/iscidraddr: ''
	@$(TESTDIR)/isinetaddr

.PHONY: test
