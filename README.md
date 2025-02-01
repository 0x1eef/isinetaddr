## About

isinetaddr is a clang library that provides a set of functions for
IP address validation.

## Examples

### isinetaddr4

The `isinetaddr4` function returns `true` when given a valid IPv4 address:

```C
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
```

### iscidraddr4

The `iscidraddr4` function supports the same features as `isinetaddr4` plus
[CIDR notation](https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing#CIDR_notation).
The following example builds on the previous example:

```C
#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *ipv4[] = {
    /* valid */
    "127.0.0.1", "192.168.2.1/32", "192.168.2.1/0",
    /* invalid */
    "192.168.2.1/33", "foobar"
};

int
main(void)
{
    for (int i = 0; i < 5; i++) {
        if (iscidraddr4(ipv4[i])) {
            printf("%s is a valid IPv4 address.\n", ipv4[i]);
        } else {
            printf("%s is an invalid IPv4 address.\n", ipv4[i]);
        }
    }
    return (EXIT_SUCCESS);
}
```

### isinetaddr6

The `isinetaddr6` function returns `true` when given a valid IPv6 address:

```C
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
```

## Sources

* [github.com/@0x1eef](https://github.com/0x1eef/isinetaddr#readme)
* [gitlab.com/@0x1eef](https://gitlab.com/0x1eef/isinetaddr#about)
* [brew.bsd.cafe/@0x1eef](https://brew.bsd.cafe/0x1eef/isinetaddr#about)

## <a id="license"> License </a>

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/)
<br>
See [LICENSE](./LICENSE)
