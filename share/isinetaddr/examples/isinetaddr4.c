#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *ipv4[] = {
    /* valid */
    "127.0.0.1", "1.1.1.1", "0.0.0.0",
    /* invalid */
    "0.0.0.0.0", "foobar"
};

int
main(void)
{
    for (int i = 0; i < 5; i++) {
        if (isinetaddr4(ipv4[i])) {
            printf("%s is a valid IPv4 address.\n", ipv4[i]);
        } else {
            printf("%s is an invalid IPv4 address.\n", ipv4[i]);
        }
    }
    return (EXIT_SUCCESS);
}
