#include <isinetaddr.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

const char *valid[] = {
  "192.168.1.1",
  "0.0.0.0",
  "255.255.255.255",
  "123.45.67.89",
  "123.45.67.255",
  "10.0.0.1/32"
};

const char *invalid[] = {
  "123.45.67.891",
  "192.168.500.1",
  ".192.168.1.1",
  "192..168.1.1",
  "192.168.1.1.",
  "192.168.1.1..",
  "192.168.1.1a",
  "555555555555555555555555555555555555",
  "",
  ".",
  ".......",
  "192.2.2.",
  "...4",
  "4...4",
  "10.0.0.1/33",
  "127.0.0.1/64",
  "127.0.0.1/",
  "127.0.0.1/a",
  "/",
  "/123.",
  "127/2",
  NULL
};

int
main(void) {
  size_t len;
  /* IPv4: valid */
  len = sizeof(valid) / sizeof(valid[0]);
  for (size_t i = 0; i < len; i++) {
    if (iscidraddr(valid[i]) != 1) {
      fprintf(stderr, "assertion failed: '%s' should be valid\n", valid[i]);
      abort();
    }
  }
  /* IPv4: invalid */
  len = sizeof(invalid) / sizeof(invalid[0]);
  for (size_t i = 0; i < len; i++) {
    if (iscidraddr(invalid[i]) != 0) {
      fprintf(stderr, "assertion failed: '%s' should NOT be valid\n", invalid[i]);
      abort();
    }
  }
  /* Done */
  printf("OK\n");
  return EXIT_SUCCESS;
}
