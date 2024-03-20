#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *ipv6[] = {
  /* valid */
  "::", "::1", "0000:0000:0000:0000:0000:0000:0000:0000",
  /* invalid */
  "foobar", "00:::0"
};


int
main(void)
{
  for (int i = 0; i < 5; i++) {
    if (isinetaddr6(ipv6[i])) {
      printf("%s is a valid IPv4 address.\n", ipv6[i]);
    } else {
      printf("%s is an invalid IPv4 address.\n", ipv6[i]);
    }
  }
  return (EXIT_SUCCESS);
}
