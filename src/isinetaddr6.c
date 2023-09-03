#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <isinetaddr.h>

static const int  MAX_DIGITLEN  = 4;
static const int  MAX_HEXTETS   = 8;
static const int  MAX_HEXDIGITS = 32;
static const int  MAX_STRLEN    = 40;
static const char SEP = ':';

static int has_consecutive_chars(const char *str, char c, int n);
static char* expand(const char *str, size_t strlen, char *new_str, size_t headlen);

int
isinetaddr6(const char *str)
{
  int hextets = 1, digitlen = 0, hexdigits = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, MAX_STRLEN));

  if (len == 0) {
    return 0;
  } else if (strncasecmp(str, "::ffff", 6) == 0) {
    return isinetaddr(&str[7]);
  }
  for (size_t i = 0; i < len; i++) {
    if (has_consecutive_chars(&str[i], SEP, 3)) {
      return 0;
    } else if (has_consecutive_chars(&str[i], SEP, 2)) {
      char new_str[MAX_STRLEN];
      return isinetaddr6(expand(str, len, new_str, i));
    } else if (str[i] == SEP) {
      if (digitlen < MAX_DIGITLEN) {
        return 0;
      } else {
        digitlen = 0;
        hextets++;
      }
    } else if (isxdigit(str[i])) {
      if (digitlen == MAX_DIGITLEN) {
        return 0;
      } else {
        digitlen++;
        hexdigits++;
      }
    } else {
      return 0;
    }
  }
  if (hextets == MAX_HEXTETS) {
    return hexdigits <= MAX_HEXDIGITS && digitlen == MAX_DIGITLEN;
  } else {
    return 0;
  }
}

static int
has_consecutive_chars(const char *str, char c, int n)
{
  for (int i = 0; i < n; i++) {
    if (*str != c) {
      return 0;
    }
    str++;
  }
  return 1;
}

static char*
expand(const char *str, size_t strlen, char *new_str, size_t headlen)
{
  char *ptr = new_str;
  size_t taillen = (strlen - headlen) - 2;
  size_t bodylen = MAX_STRLEN - taillen;
  size_t i = headlen + 2;
  size_t j = headlen;

  while (i++ < strlen) {
    if (has_consecutive_chars(&str[i], SEP, 2)) {
      return NULL;
    }
  }
  memcpy(ptr, &str[0], headlen);
  ptr += headlen;
  while (++j < bodylen) {
    *ptr++ = j % 5 == 0 ? ':' : '0';
  }
  memcpy(ptr, &str[headlen + 2], taillen);
  return new_str;
}
