#include "my_string.h"

char *my_strncpy(char *dest, const char *src, my_size_t n) {
  char *ptr_dest = dest;
  const char *ptr_src = src;

  for (my_size_t i = 0; i < n && *ptr_src != '\0'; i++) {
    *ptr_dest++ = *ptr_src++;
  }
  while (ptr_dest < dest + n) {
    *ptr_dest++ = '\0';
  }

  return dest;
}