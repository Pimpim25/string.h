#include "my_string.h"

void *my_memchr(const void *str, int c, my_size_t n) {
  const unsigned char *no_void_str = (const unsigned char *)str;
  unsigned char uc = (unsigned char)c;
  my_size_t uc_position = n;

  for (my_size_t i = 0; i < n && uc_position == n; i++) {
    if (no_void_str[i] == uc) {
      uc_position = i;
    }
  }

  return uc_position == n ? MY_NULL : (void *)(no_void_str + uc_position);
}
