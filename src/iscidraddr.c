#include <isinetaddr.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

static int in_range(char buf[4], int min, int max);

int
iscidraddr(const char *str)
{
  size_t offset = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, 16));

  for(size_t i = 0; i < len; i++) {
    if(str[i] == '/') {
      offset = i;
      break;
    }
  }
  if (offset == 0) {
    return isinetaddr(str);
  } else {
    char addr[offset], cidr[3];
    char *c = (char*)&str[offset + 1];
    memcpy(addr, str, offset);
    memcpy(cidr, c, 3);
    addr[offset] = '\0';
    return isinetaddr(addr) && in_range(cidr, 0, 32);
  }
}

static int
in_range(char buf[4], int min, int max)
{
  char *err;
  long r;
  errno = 0;
  if (strnlen(buf, 1) == 0) {
    return 0;
  } else {
    r = strtol(buf, &err, 10);
    return *err == '\0' && errno == 0 && (r >= min && r <= max);
  }
}
