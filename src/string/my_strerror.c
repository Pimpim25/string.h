#include "my_string.h"

#ifdef __linux__
ERR_MSGS_LINUX
#define ERR_MSGS linux_error_msgs
#endif

#ifdef __APPLE__
ERR_MSGS_MAC
#define ERR_MSGS mac_error_msgs
#endif

char *my_strerror(int errnum) {
  static char cu[100] = {0};
  char first[20] = {0};
  my_size_t i = 0, j = 0;
  const char *c = NULL;
  if (errnum >= 0 && errnum < 134 && ERR_MSGS[errnum]) {
    c = ERR_MSGS[errnum];
  }
  if (c) {
    my_strncpy(cu, c, sizeof(cu) - 1);
    cu[sizeof(cu) - 1] = '\0';
  } else if (errnum == 0) {
    my_strncpy(cu, "Success", sizeof(cu) - 1);
    cu[sizeof(cu) - 1] = '\0';
  } else {
    const char *str = "Unknown error ";
    for (i = 0; i < my_strlen(str); i++) {
      cu[i] = str[i];
    }
    unsigned int unum;
    if (errnum < 0) {
      cu[i++] = '-';
      unum = (unsigned int)(-errnum);
    } else {
      unum = (unsigned int)errnum;
    }
    while (unum > 0 && j < sizeof(first)) {
      first[j++] = (unum % 10) + '0';
      unum /= 10;
    }
    while (j > 0 && i < sizeof(cu) - 1) {
      cu[i++] = first[--j];
    }
    cu[i] = '\0';
  }
  return cu;
}
