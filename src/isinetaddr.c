#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <isinetaddr.h>
#include <errno.h>

static int
inrange(char buf[4])
{
  char *err;
  long r;
  errno = 0;
  r = strtol(buf, &err, 10);
  return *err == '\0' && errno == 0 && (r >= 0 && r <= 255);
}

int
isinetaddr(const char *str)
{
  char buf[4];
  int i = 0, j = 0, k = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, 16));

  for (size_t l = 0; l < len; l++) {
    if (str[l] == '.') {
      if (j == 1 && i == 0) {
        return 0;
      } else if (k == 3 && !inrange(buf)) {
        return 0;
      } else {
        k = 0;
        j++;
        bzero(buf, 3);
        buf[3] = '\0';
      }
    } else if (isdigit(str[l])) {
      if (k == 3) {
        return 0;
      } else {
        buf[k++] = str[l];
        buf[k] = '\0';
        i++;
      }
    } else {
      return 0;
    }
  }
  if (j == 3 && k == 3) {
    if (!inrange(buf)) {
      return 0;
    }
  }
  return j == 3 && k > 0 && i <= 12;
}
