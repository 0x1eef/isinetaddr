#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <isinetaddr.h>

static const int  MAX_DIGITLEN  = 4;
static const int  MAX_HEXTETS   = 8;
static const int  MAX_HEXDIGITS = 32;
static const int  MAX_STRLEN    = 40;
static const char SEP = ':';

static bool has_consecutive_chars(const char *str, char c, int n);
static char* expand(const char *str, size_t strlen, char *new_str, size_t headlen);
static size_t get_offset(char *tail);

bool
isinetaddr6(const char *str)
{
  int hextets = 1, digitlen = 0, hexdigits = 0;
  size_t len = (str == NULL ? 0 : strnlen(str, MAX_STRLEN));

  if (len == 0) {
    return false;
  } else if (strncasecmp(str, "::ffff", 6) == 0) {
    return isinetaddr4(&str[7]);
  }
  for (size_t i = 0; i < len; i++) {
    if (has_consecutive_chars(&str[i], SEP, 3)) {
      return false;
    } else if (has_consecutive_chars(&str[i], SEP, 2)) {
      if (i == 0 && isinetaddr4(&str[3])) {
        return true;
      } else {
        char new_str[MAX_STRLEN];
        return isinetaddr6(expand(str, len, new_str, i));
      }
    } else if (str[i] == SEP) {
      digitlen = 0;
    } else if (isxdigit(str[i])) {
      digitlen++;
      hexdigits++;
      if (digitlen > MAX_DIGITLEN) {
        return 0;
      } else if (str[i-1] == SEP) {
        hextets++;
      }
    } else {
      return false;
    }
  }
  return hextets == MAX_HEXTETS && hexdigits <= MAX_HEXDIGITS;
}

static bool
has_consecutive_chars(const char *str, char c, int n)
{
  for (int i = 0; i < n; i++) {
    if (*str++ != c) {
      return 0;
    }
  }
  return 1;
}

static char*
expand(const char *str, size_t strlen, char *new_str, size_t headlen)
{
  char *ptr = new_str;
  char *tail = (char*) &str[headlen + 2];
  size_t taillen = (strlen - headlen) - 2;
  size_t bodylen = MAX_STRLEN - taillen;
  size_t i = headlen + 2;
  size_t j = headlen;
  size_t offset = get_offset(tail);

  while (i++ < strlen) {
    if (has_consecutive_chars(&str[i], SEP, 2)) {
      return NULL;
    }
  }
  memcpy(ptr, &str[0], headlen);
  ptr += headlen;
  while (++j < bodylen-offset) {
    *ptr++ = j % 5 == 0 ? ':' : '0';
  }
  memcpy(ptr, tail, taillen);
  return new_str;
}

static size_t
get_offset(char *tail)
{
  size_t offset = 0;
  while (*tail++ != SEP) {
    offset++;
    if (*tail == '\0' || offset == 4) {
      offset = 0;
      break;
    }
  }
  return offset;
}
