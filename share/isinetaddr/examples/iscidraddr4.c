#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *strings[] = {
  /* valid */
  "127.0.0.1",
  "1.1.1.1",
  "0.0.0.0",
  "127.0.0.1/8",
  "127.0.0.1/16",
  "127.0.0.1/32",

  /* invalid */
  "foobar",
  "0.0.0.0.0",
  "127.0.0.1/33",
};

int
main(void)
{
    const char *str;
    const int i = sizeof(strings) / sizeof(strings[0]);
    for (int j = 0; j < i; j++) {
        str = strings[j];
        if (iscidraddr4(str)) {
            printf("%s is a valid IPv4 address\n", str);
        } else {
            printf("%s is an invalid IPv4 address\n", str);
        }
    }
    return EXIT_SUCCESS;
}
