#include <isinetaddr.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

const char *valid[] = {
  /* valid IPv4 */
  "192.168.1.1", "0.0.0.0",
  "255.255.255.255", "123.45.67.89",
  "123.45.67.255",
};

const char *invalid[] = {
  /* invalid IPv4  */
  "123.45.67.891", "192.168.500.1",
  ".192.168.1.1", "192..168.1.1",
  "192.168.1.1.", "192.168.1.1..",
  "192.168.1.1a", "192.2.2.",
  /* edge cases */
  "555555555555555555555555555555555555",
  "", ".", ".......", "...4", "4...4",
  NULL
};

int
main(void) {
  size_t len;
  /* IPv4: valid */
  len = sizeof(valid) / sizeof(valid[0]);
  for (size_t i = 0; i < len; i++) {
    if (isinetaddr(valid[i]) != 1) {
      fprintf(stderr, "assertion failed: '%s' should be valid\n", valid[i]);
      abort();
    }
  }
  /* IPv4: invalid */
  len = sizeof(invalid) / sizeof(invalid[0]);
  for (size_t i = 0; i < len; i++) {
    if (isinetaddr(invalid[i]) != 0) {
      fprintf(stderr, "assertion failed: '%s' should NOT be valid\n", invalid[i]);
      abort();
    }
  }
  /* Done */
  printf("OK\n");
  return EXIT_SUCCESS;
}
