#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <isinetaddr.h>

static const int  MAX_BUFLEN   = 3;
static const int  MAX_OCTETS   = 4;
static const int  MAX_DIGITLEN = 12;
static const int  MAX_STRLEN   = 16;
static const char SEP = '.';
static bool within_range(char buf[MAX_BUFLEN]);

bool
isinetaddr4(const char *str)
{
  char buf[MAX_BUFLEN + 1];
  int digits = 0, octets = 1, buflen = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, MAX_STRLEN));

  for (size_t i = 0; i < len; i++) {
    if (str[i] == SEP) {
      if (octets == MAX_OCTETS || buflen == 0) {
        return false;
      } else {
        buflen = 0;
      }
    } else if (isdigit(str[i])) {
      if (buflen == MAX_BUFLEN) {
        return false;
      } else {
        buf[buflen++] = str[i];
        buf[buflen] = '\0';
        digits++;
        if (!within_range(buf)) {
          return false;
        } else if (i > 0 && str[i-1] == SEP) {
          octets++;
        }
      }
    } else {
      return false;
    }
  }
  return octets == MAX_OCTETS && digits <= MAX_DIGITLEN;
}

static bool
within_range(char buf[MAX_BUFLEN])
{
  int n = atoi(buf);
  return n >= 0 && n <= 255;
}
