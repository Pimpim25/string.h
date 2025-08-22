#include "my_string.h"

char *my_strpbrk(const char *str1, const char *str2) {
  my_size_t i = 0;
  while (str1[i] != '\0' && my_strchr(str2, str1[i]) == MY_NULL) {
    i++;
  }
  return i < my_strlen(str1) ? (char *)(str1 + i) : MY_NULL;
}