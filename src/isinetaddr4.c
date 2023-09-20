#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <isinetaddr.h>
#include <errno.h>

static const int  MAX_BUFLEN   = 3;
static const int  MAX_OCTETS   = 4;
static const int  MAX_DIGITLEN = 12;
static const int  MAX_STRLEN   = 16;
static const char SEP = '.';
static int in_range(char buf[MAX_BUFLEN]);

int
isinetaddr4(const char *str)
{
  char buf[MAX_BUFLEN + 1];
  int digits = 0, octets = 1, buflen = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, MAX_STRLEN));

  buf[MAX_BUFLEN] = '\0';
  for (size_t l = 0; l < len; l++) {
    if (str[l] == SEP) {
      if (octets == MAX_OCTETS || buflen == 0) {
        return 0;
      } else {
        buflen = 0;
        bzero(buf, MAX_BUFLEN);
      }
    } else if (isdigit(str[l])) {
      if (buflen == MAX_BUFLEN) {
        return 0;
      } else {
        buf[buflen++] = str[l];
        digits++;
        if (!in_range(buf)) {
          return 0;
        }
      }
    } else {
      return 0;
    }
    if (str[l-1] == SEP) {
      octets++;
    }
  }
  return octets == MAX_OCTETS && digits <= MAX_DIGITLEN;
}

static int
in_range(char buf[MAX_BUFLEN])
{
  int n = atoi(buf);
  return n >= 0 && n <= 255;
}
