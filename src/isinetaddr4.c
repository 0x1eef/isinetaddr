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
static int within_range(char buf[MAX_BUFLEN]);

int
isinetaddr4(const char *str)
{
  char buf[MAX_BUFLEN + 1];
  int digits = 0, octets = 1, buflen = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, MAX_STRLEN));

  buf[MAX_BUFLEN] = '\0';
  for (size_t i = 0; i < len; i++) {
    if (str[i] == SEP) {
      if (octets == MAX_OCTETS || buflen == 0) {
        return 0;
      } else {
        buflen = 0;
        bzero(buf, MAX_BUFLEN);
      }
    } else if (isdigit(str[i])) {
      if (buflen == MAX_BUFLEN) {
        return 0;
      } else {
        buf[buflen++] = str[i];
        digits++;
        if (!within_range(buf)) {
          return 0;
        } else if (str[i-1] == SEP) {
          octets++;
        }
      }
    } else {
      return 0;
    }
  }
  return octets == MAX_OCTETS && digits <= MAX_DIGITLEN;
}

static int
within_range(char buf[MAX_BUFLEN])
{
  int n = atoi(buf);
  return n >= 0 && n <= 255;
}
