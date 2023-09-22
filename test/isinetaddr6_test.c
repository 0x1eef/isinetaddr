#include <isinetaddr.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

const char *valid[] = {
  /* valid IPv6 (single colon)*/
  "0000:0000:0000:0000:0000:0000:0000:0001",
  "2001:0db8:85a3:0000:0000:8a2e:0370:7334",
  "fe80:0000:0000:0000:0202:b3ff:fe1e:8329",
  "abcd:abcd:abcd:abcd:abcd:abcd:abcd:abcd",
  "1234:5678:9abc:def0:face:face:b00c:0ffe",
  "2001:19f0:5401:0000:0000:ffff:1e61:face",
  "dead:beef:cafe:babe:affe:8a2e:0370:7334",
  "2001:DB8:0:0:8:800:200C:417A",
  "0000:0000:0000:0000:0000:0000:0000:0",
  "FEDC:BA98:7654:3210:FEDC:BA98:7654:3210",

  /* valid IPv6 (double colon) */
  "fe80::c001:a0ff:fe12:3456",
  "2001:0db8::1",
  "2001:abcd:ef01:2345::",
  "1234::5678",
  "0000:00::1111",
  "000::1111:1111",
  "000::1111:1111:1111",
  "0000:00::1111",
  "0000:0000:0000:0000:0000:0000:0000:00::",
  "2001:0db8:85a3:0000:0000::8a2e:0370:7334",
  "2001::5",
  "::ffff:192.168.2.1",
  "::FFFF:192.168.2.1",
  "::",
  "::1",
};

const char *invalid[] = {
  /* invalid IPv6 (single colon) */
  "0000:0000:0000:0000:0000:0000:0000:000Z",
  "0000:0000:0000:0000:0000:0000:0000:",
  "2001:DB8:0:Z:8:800:200C:417A",

  /* invalid IPv6 (double colon) */
  ":::", "2001:::1", "2001:::1::",
  "2001::1::", "::1::",
  "2001:db8:85a3::8a2e:3700:7334",
  "::ffff", "::ffff:", "::ffff:00",

  /* edge cases */
  NULL
};

int
main(void) {
  size_t len;
  /* IPv6: valid */
  len = sizeof(valid) / sizeof(valid[0]);
  for (size_t i = 0; i < len; i++) {
    if (isinetaddr6(valid[i]) != 1) {
      fprintf(stderr, "assertion failed: '%s' should be valid\n", valid[i]);
      abort();
    }
  }
  /* IPv6: invalid */
  len = sizeof(invalid) / sizeof(invalid[0]);
  for (size_t i = 0; i < len; i++) {
    if (isinetaddr6(invalid[i]) != 0) {
      fprintf(stderr, "assertion failed: '%s' should NOT be valid\n", invalid[i]);
      abort();
    }
  }
  /* Done */
  printf("OK\n");
  return EXIT_SUCCESS;
}
