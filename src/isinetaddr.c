#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <isinetaddr.h>
#include <errno.h>
static int inrange(char buf[4], int buflen);

int
isinetaddr(const char *str)
{
  char buf[4];
  int digits = 0, octets = 0, buflen = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, 16));

  for (size_t l = 0; l < len; l++) {
    if (str[l] == '.') {
      if (octets == 1 && digits == 0) {
        return 0;
      } else if (!inrange(buf, buflen)) {
        return 0;
      } else {
        buflen = 0;
        octets++;
        bzero(buf, 3);
        buf[3] = '\0';
      }
    } else if (isdigit(str[l])) {
      if (buflen == 3) {
        return 0;
      } else {
        buf[buflen++] = str[l];
        buf[buflen] = '\0';
        digits++;
      }
    } else {
      return 0;
    }
  }
  if (octets == 3) {
    if (!inrange(buf, buflen)) {
      return 0;
    }
  }
  return octets == 3 && digits <= 12 && buflen > 0;
}

static int
inrange(char buf[4], int buflen)
{
  char *err;
  long r;
  if (buflen < 3) {
    return 1;
  } else {
    errno = 0;
    r = strtol(buf, &err, 10);
    return *err == '\0' && errno == 0 && (r >= 0 && r <= 255);
  }
}
