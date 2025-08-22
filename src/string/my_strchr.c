#include "my_string.h"

char *my_strchr(const char *str, int c) {
  unsigned char uc = (unsigned char)c;
  const unsigned char *no_void_str = (const unsigned char *)str;

  while (*no_void_str && *no_void_str != uc) {
    no_void_str++;
  }

  return *no_void_str == uc ? (char *)no_void_str : MY_NULL;
}