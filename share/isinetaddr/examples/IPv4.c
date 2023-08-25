#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *strings[] = {
  "127.0.0.1", "1.1.1.1", "0.0.0.0",
  "foobar", "0.0.0.0.0"
};

int
main(void)
{
    const char *str;
    const int i = sizeof(strings) / sizeof(strings[0]);
    for (int j = 0; j < i; j++) {
        str = strings[j];
        if(isinetaddr(str)) {
            printf("%s is a valid IPv4 address\n", str);
        } else {
            printf("%s is an invalid IPv4 address\n", str);
        }
    }
    return EXIT_SUCCESS;
}
