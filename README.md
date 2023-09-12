## About

isinetaddr is a simple C library that provides an interface that can
be used to validate an IPv(<b>4</b>|<b>6</b>) address (with optional
support for CIDR notation as well). The library is guided by easy to
extend [testcases](test/) that help verify safety and correctness.

## Examples

### IPv4

The following example demonstrates the `isinetaddr4` function with
both valid and invalid inputs. The `isinetaddr4` function returns 1
when the input given is a valid IPv4 address, and otherwise returns 0.

```C
#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *strings[] = {
  /* valid */
  "127.0.0.1",
  "1.1.1.1",
  "0.0.0.0",

  /* invalid */
  "foobar",
  "0.0.0.0.0"
};

int
main(void)
{
    const char *str;
    const int i = sizeof(strings) / sizeof(strings[0]);
    for (int j = 0; j < i; j++) {
        str = strings[j];
        if (isinetaddr4(str)) {
            printf("%s is a valid IPv4 address\n", str);
        } else {
            printf("%s is an invalid IPv4 address\n", str);
        }
    }
    return EXIT_SUCCESS;
}
```

When the above source code is compiled and run the output is
expected to be as follows:

```
$ cc -Iinclude src/*.c share/isinetaddr/examples/isinetaddr4.c -o example
$ ./example
127.0.0.1 is a valid IPv4 address
1.1.1.1 is a valid IPv4 address
0.0.0.0 is a valid IPv4 address
foobar is an invalid IPv4 address
0.0.0.0.0 is an invalid IPv4 address
```

### CIDR notation (IPv4)

The `iscidraddr4` function supports the same feature set as `isinetaddr4`, and
in addition supports
[CIDR notation](https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing#CIDR_notation).
The following example builds on the previous example:

```C
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
  "127.0.0.1/64"
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
```

When the above source code is compiled and run the output is
expected to be as follows:

```
$ cc -Iinclude src/*.c share/isinetaddr/examples/iscidraddr4.c -o example
$ ./example
127.0.0.1 is a valid IPv4 address
1.1.1.1 is a valid IPv4 address
0.0.0.0 is a valid IPv4 address
127.0.0.1/8 is a valid IPv4 address
127.0.0.1/16 is a valid IPv4 address
127.0.0.1/32 is a valid IPv4 address
foobar is an invalid IPv4 address
0.0.0.0.0 is an invalid IPv4 address
127.0.0.1/33 is an invalid IPv4 address
127.0.0.1/64 is an invalid IPv4 address
```

### IPv6

The following example demonstrates the `isinetaddr6` function with
both valid and invalid inputs. The `isinetaddr6` function returns 1
when the input given is a valid IPv6 address, and otherwise returns 0.

```C
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
```

When the above source code is compiled and run the output is
expected to be as follows:

```
$ cc -Iinclude src/*.c share/isinetaddr/examples/isinetaddr6.c -o example
$ ./example
0x1eef [isinetaddr] % ./example
:: is a valid IPv6 address
::1 is a valid IPv6 address
0000:0000:0000:0000:0000:0000:0000:0000 is a valid IPv6 address
foobar is an invalid IPv6 address
(null) is an invalid IPv6 address
00:::0 is an invalid IPv6 address
```

## Sources

* [Source code (GitHub)](https://github.com/0x1eef/isinetaddr#readme)
* [Source code (GitLab)](https://gitlab.com/0x1eef/isinetaddr#about)

## <a id="license"> License </a>

[BSD Zero Clause](https://choosealicense.com/licenses/0bsd/).
<br>
See [LICENSE](./LICENSE).
