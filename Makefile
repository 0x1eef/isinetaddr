SRCDIR   = src
SRCFILES = $(SRCDIR)/isinetaddr4.c $(SRCDIR)/iscidraddr4.c $(SRCDIR)/isinetaddr6.c
INCDIR   = include
TESTDIR  = test

CC = cc
CFLAGS = -fstack-protector-all -I$(INCDIR) -Wall -Wextra -pedantic

test:
	@make test4
	@make test6

test4:
	@$(CC) $(CFLAGS) $(SRCFILES) $(TESTDIR)/isinetaddr4_test.c -o $(TESTDIR)/isinetaddr
	@echo -n test/isinetaddr: ''
	@$(TESTDIR)/isinetaddr
	@$(CC) $(CFLAGS) $(SRCFILES) $(TESTDIR)/iscidraddr4_test.c -o $(TESTDIR)/iscidraddr
	@echo -n test/iscidraddr: ''
	@$(TESTDIR)/iscidraddr

test6:
	@$(CC) $(CFLAGS) $(SRCFILES) $(TESTDIR)/isinetaddr6_test.c -o $(TESTDIR)/isinetaddr6
	@echo -n test/isinetaddr6: ''
	@$(TESTDIR)/isinetaddr6

.PHONY: test
