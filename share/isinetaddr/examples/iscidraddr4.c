#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *valid[] = { "127.0.0.1", "192.168.2.1/32", "192.168.2.1/0" };
const char *invalid[] = { "foobar", "0.0.0.0.0", "192.168.2.1/33" };

void
validate(const char *str)
{
  if (iscidraddr4(str)) {
    printf("%s is a valid IPv4 address.\n", str);
  } else {
    printf("%s is an invalid IPv4 address.\n", str);
  }
}

int
main(void)
{
  printf("// valid\n");
  for (int i = 0; i < 3; i++) {
    validate(valid[i]);
  }
  printf("// invalid\n");
  for (int i = 0; i < 3; i++) {
    validate(invalid[i]);
  }
  return EXIT_SUCCESS;
}
