#include "my_string.h"

char *my_strstr(const char *haystack, const char *needle) {
  const char *result = MY_NULL;

  if (needle[0] == '\0') {
    result = haystack;

  } else {
    for (my_size_t i = 0; i < my_strlen(haystack) && !result; i++) {
      bool sub_str_is_found = true;
      for (my_size_t j = 0, k = i; j < my_strlen(needle) && sub_str_is_found;
           j++, k++) {
        if (needle[j] != haystack[k]) {
          sub_str_is_found = false;
        }
      }
      if (sub_str_is_found) {
        result = (char *)haystack + i;
      }
    }
  }
  return (char *)result;
}
