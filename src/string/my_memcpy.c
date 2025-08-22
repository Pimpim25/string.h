#include "my_string.h"

void *my_memcpy(void *dest, const void *src, my_size_t n) {
  const unsigned char *no_void_src = (const unsigned char *)src;
  unsigned char *char_dest = (unsigned char *)dest;

  for (my_size_t i = 0; i < n; i++) {
    char_dest[i] = no_void_src[i];
  }

  return (void *)char_dest;
}