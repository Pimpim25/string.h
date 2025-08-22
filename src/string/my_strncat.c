#include "my_string.h"

char *my_strncat(char *dest, const char *src, my_size_t n) {
  char *ptr_dest = dest;
  while (*ptr_dest) {
    ptr_dest++;
  }

  for (my_size_t i = 0; i < n && src[i] != '\0'; i++) {
    *ptr_dest++ = src[i];
  }
  *ptr_dest = '\0';
  return dest;
}