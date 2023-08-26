#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <isinetaddr.h>
#include <errno.h>

static int in_range(char buf[4], int buflen);
static void register_octet(int *octets, char *buf, int *buflen);
static void register_digit(char digit, int *digits, char *buf, int *buflen);

int
isinetaddr(const char *str)
{
  char buf[4];
  int digits = 0, octets = 1, buflen = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, 16));

  for (size_t l = 0; l < len; l++) {
    if (str[l] == '.') {
      if (buflen == 0) {
        return 0;
      } else if (!in_range(buf, buflen)) {
        return 0;
      } else {
        register_octet(&octets, buf, &buflen);
      }
    } else if (isdigit(str[l])) {
      if (buflen == 3) {
        return 0;
      } else {
        register_digit(str[l], &digits, buf, &buflen);
      }
    } else {
      return 0;
    }
  }
  if (octets == 4) {
    return digits <= 12 && in_range(buf, buflen) && buflen > 0;
  } else {
    return 0;
  }
}

static int
in_range(char buf[4], int buflen)
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

static void
register_octet(int *octets, char *buf, int *buflen)
{
  *buflen = 0;
  (*octets)++;
  bzero(buf, 3);
  buf[3] = '\0';
}

static void
register_digit(char digit, int *digits, char *buf, int *buflen)
{
  buf[(*buflen)++] = digit;
  buf[*buflen] = '\0';
  (*digits)++;
}
