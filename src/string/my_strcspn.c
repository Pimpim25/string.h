#include "my_string.h"

my_size_t my_strcspn(const char *str1, const char *str2) {
  my_size_t i = 0;
  while (my_strchr(str2, str1[i]) == MY_NULL) {
    i++;
  }
  return i;
}