#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <isinetaddr.h>

int
isinetaddr(const char *str)
{
  char buf[4];
  const char *err;
  int i = 0, j = 0, k = 0;

  for(int l = 0; l < (int)strnlen(str, 16); l++) {
    if (str[l] == '.') {
      strtonum(buf, 0, 255, &err);
      if (err != NULL) {
        return 0;
      } else {
        k = 0;
        j++;
        bzero(buf, 3);
        buf[3] = '\0';
      }
    } else if (isdigit(str[l])) {
      buf[k++] = str[l];
      buf[k] = '\0';
      i++;
    } else {
      return 0;
    }
  }
  return j == 3 && i <= 12 ? 1 : 0;
}
