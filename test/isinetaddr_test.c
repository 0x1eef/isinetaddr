#include <isinetaddr.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int
main(void) {
  /* Assertions */
  assert(isinetaddr("192.168.1.1") == 1);
  assert(isinetaddr("0.0.0.0") == 1);
  assert(isinetaddr("255.255.255.255") == 1);
  assert(isinetaddr("123.45.67.89") == 1);
  assert(isinetaddr("192.168.500.1") == 0);
  assert(isinetaddr(".192.168.1.1") == 0);
  assert(isinetaddr("192..168.1.1") == 0);
  assert(isinetaddr("192.168.1.1.") == 0);
  assert(isinetaddr("192.168.1.1..") == 0);
  assert(isinetaddr("192.168.1.1a") == 0);
  assert(isinetaddr("") == 0);
  /* Record success */
  printf("OK\n");
  return EXIT_SUCCESS;
}
