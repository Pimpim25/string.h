#include "my_string.h"

my_size_t my_strlen(const char *str) {
  my_size_t len = 0;
  for (; str[len]; len++);
  return len;
}
