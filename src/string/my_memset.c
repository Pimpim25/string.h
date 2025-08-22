#include "my_string.h"

void *my_memset(void *str, int c, my_size_t n) {
  unsigned char uc = (unsigned char)c;
  unsigned char *no_void_str = (unsigned char *)str;
  for (my_size_t i = 0; i < n; i++) {
    no_void_str[i] = uc;
  }

  return str;
}