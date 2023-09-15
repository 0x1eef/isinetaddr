#include <isinetaddr.h>
#include <stdio.h>
#include <stdlib.h>

const char *valid[] = { "::", "::1", "0000:0000:0000:0000:0000:0000:0000:0000" };
const char *invalid[] = { "foobar", "00:::0", NULL };
void validate(const char *str);

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

void
validate(const char *str)
{
  if (isinetaddr6(str)) {
    printf("%s is a valid IPv6 address.\n", str);
  } else {
    printf("%s is an invalid IPv6 address.\n", str);
  }
}
