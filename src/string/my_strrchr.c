#include "my_string.h"

char *my_strrchr(const char *str, int c) {
  char *cu = MY_NULL;
  for (my_size_t i = my_strlen(str); i != (my_size_t)-1; i--) {
    if (str[i] == c && cu == MY_NULL) {
      cu = (char *)(str + i);
    }
  }
  return cu;
}