#include "my_string.h"

int my_memcmp(const void *str1, const void *str2, my_size_t n) {
  const unsigned char *no_void_str1 = (const unsigned char *)str1;

  const unsigned char *no_void_str2 = (const unsigned char *)str2;

  bool dif_is_found = false;
  unsigned char ui_str1 = 0;
  unsigned char ui_str2 = 0;

  for (my_size_t i = 0; i < n && !dif_is_found; i++) {
    ui_str1 = no_void_str1[i];
    ui_str2 = no_void_str2[i];
    if (ui_str1 != ui_str2) {
      dif_is_found = true;
    }
  }

  return (int)(ui_str1 - ui_str2);
}