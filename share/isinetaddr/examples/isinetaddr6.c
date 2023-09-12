#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *strings[] = {
  /* valid */
  "::",
  "::1",
  "0000:0000:0000:0000:0000:0000:0000:0000",

  /* invalid */
  "foobar",
  NULL,
  "00:::0",
};

int
main(void)
{
    const char *str;
    const int i = sizeof(strings) / sizeof(strings[0]);
    for (int j = 0; j < i; j++) {
        str = strings[j];
        if (isinetaddr6(str)) {
            printf("%s is a valid IPv6 address\n", str);
        } else {
            printf("%s is an invalid IPv6 address\n", str);
        }
    }
    return EXIT_SUCCESS;
}
