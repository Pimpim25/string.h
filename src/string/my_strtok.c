#include "my_string.h"

char *my_strtok(char *str, const char *delim) {
  static char *cu = MY_NULL;
  char *ret = MY_NULL;
  if (str != MY_NULL)
    cu = str;
  if (cu != MY_NULL) {
    while (*cu && my_strchr(delim, *cu) != MY_NULL)
      cu++;
    if (*cu == '\0')
      cu = MY_NULL;
    char *token = cu;
    while (*cu && my_strchr(delim, *cu) == MY_NULL)
      cu++;
    if (*cu != '\0') {
      *cu = '\0';
      cu++;
    } else {
      cu = MY_NULL;
    }
    ret = token;
  }
  return ret;
}