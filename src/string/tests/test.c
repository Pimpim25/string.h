#include "../my_string.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *test_str[] = {
    "Hello world\0", "Hello world\n\0", "a\n\0", " \n\0", " \0", "\n\0", "\0"};

START_TEST(test_my_strerror) {
  for (int errnum = 0; errnum < 133; errnum++) {
    ck_assert_str_eq(strerror(errnum), my_strerror(errnum));
  }
}
END_TEST

START_TEST(test_my_memcpy) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (my_size_t j = 0; j < sizeof(test_str) / sizeof(test_str[0]); j++) {
      my_size_t len1 = my_strlen(test_str[i]);
      size_t len2 = strlen(test_str[i]);

      char buff1[100] = {0};
      char buff2[100] = {0};

      strncpy(buff1, test_str[i], len1);
      my_strncpy(buff2, test_str[i], len2);
      ck_assert_mem_eq(memcpy(buff1, test_str[j], strlen(test_str[j])),
                       my_memcpy(buff2, test_str[j], my_strlen(test_str[j])),
                       len1);
    }
  }
}
END_TEST

START_TEST(test_my_memset) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    my_size_t len1 = my_strlen(test_str[i]);
    size_t len2 = strlen(test_str[i]);

    char buff1[100] = {0};
    char buff2[100] = {0};

    strncpy(buff1, test_str[i], len1);
    my_strncpy(buff2, test_str[i], len2);

    ck_assert_mem_eq(memset(buff1, 'c', len1), my_memset(buff2, 'c', len2),
                     len1);
  }
}
END_TEST

START_TEST(test_my_memchr) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    int c = 'H';
    my_size_t len = strlen(test_str[i]);
    ck_assert_ptr_eq(memchr(test_str[i], c, len),
                     my_memchr(test_str[i], c, len));
  }
}
END_TEST

START_TEST(test_my_strpbrk) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (my_size_t j = 0; j < sizeof(test_str) / sizeof(test_str[0]); j++) {
      ck_assert_ptr_eq(strpbrk(test_str[i], test_str[j]),
                       my_strpbrk(test_str[i], test_str[j]));
    }
  }
}
END_TEST

START_TEST(test_my_strrchr) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    int c = '\0';
    ck_assert_ptr_eq(strrchr(test_str[i], c), my_strrchr(test_str[i], c));
  }
}
END_TEST

START_TEST(test_my_strstr) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (my_size_t j = 0; j < sizeof(test_str) / sizeof(test_str[0]); j++) {
      ck_assert_ptr_eq(strstr(test_str[i], test_str[j]),
                       my_strstr(test_str[i], test_str[j]));
    }
  }
}
END_TEST

START_TEST(test_my_memcmp) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (my_size_t j = 0; j < sizeof(test_str) / sizeof(test_str[0]); j++) {
      my_size_t n = strlen(test_str[i]) < strlen(test_str[j])
                         ? strlen(test_str[i])
                         : strlen(test_str[j]);
      ck_assert_int_eq(memcmp(test_str[i], test_str[j], n),
                       my_memcmp(test_str[i], test_str[j], n));
    }
  }
}
END_TEST

START_TEST(test_my_strtok) {
  char str1[] = "test,string,example";
  char str2[] = "test,string,example";
  const char *delim = ",";

  char *token1 = strtok(str1, delim);
  char *token2 = my_strtok(str2, delim);

  while (token1 != NULL && token2 != NULL) {
    ck_assert_str_eq(token1, token2);
    token1 = strtok(NULL, delim);
    token2 = my_strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_my_strchr) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    int c = '\0';
    ck_assert_ptr_eq(strchr(test_str[i], c), my_strchr(test_str[i], c));
  }
}
END_TEST

START_TEST(test_my_strncat) {
  char dest1[100] = "start";
  char dest2[100] = "start";
  const char *src = "append";
  my_size_t n = strlen(src);

  strncat(dest1, src, n);
  my_strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_my_strncpy) {
  char dest1[100] = {0};
  char dest2[100] = {0};
  const char *src = "test string";
  my_size_t n = strlen(src) + 1;

  strncpy(dest1, src, n);
  my_strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_my_strncmp) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (my_size_t j = 0; j < sizeof(test_str) / sizeof(test_str[0]); j++) {
      my_size_t n = strlen(test_str[i]) < strlen(test_str[j])
                         ? strlen(test_str[i])
                         : strlen(test_str[j]);

      int remy = my_strncmp(test_str[i], test_str[j], n);
      int std_res = strncmp(test_str[i], test_str[j], n);
      ck_assert_int_eq(((remy > 0) - (remy < 0)),
                       ((std_res > 0) - (std_res < 0)));
    }
  }
}
END_TEST

START_TEST(test_my_strcspn) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    for (my_size_t j = 0; j < sizeof(test_str) / sizeof(test_str[0]); j++) {
      ck_assert_uint_eq(strcspn(test_str[i], test_str[j]),
                        my_strcspn(test_str[i], test_str[j]));
    }
  }
}
END_TEST

START_TEST(test_my_strlen) {
  for (my_size_t i = 0; i < sizeof(test_str) / sizeof(test_str[0]); i++) {
    ck_assert_uint_eq(strlen(test_str[i]), my_strlen(test_str[i]));
  }
}
END_TEST

START_TEST(test_my_sprintf_c) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(sprintf(buf1, "%c %5c %-5c", 'A', 'B', 'C'),
                   my_sprintf(buf2, "%c %5c %-5c", 'A', 'B', 'C'));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_d) {
  char buf1[100] = {0}, buf2[100] = {0};
  ck_assert_int_eq(sprintf(buf1, "%hd %d %+d % d %-5d %7.3d %07d %ld",
                           (short)123, 42, 42, 42, 42, 42, 42, 1234567L),
                   my_sprintf(buf2, "%hd %d %+d % d %-5d %7.3d %07d %ld",
                               (short)123, 42, 42, 42, 42, 42, 42, 1234567L));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_u) {
  char buf1[100] = {0}, buf2[100] = {0};
  ck_assert_int_eq(sprintf(buf1, "%u %-5u %7.3u %07u %hu %lu", 42u, 42, 42, 42,
                           (unsigned short)65535, 1234567890UL),
                   my_sprintf(buf2, "%u %-5u %7.3u %07u %hu %lu", 42u, 42, 42,
                               42, (unsigned short)65535, 1234567890UL));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_s) {
  char buf1[50] = {0}, buf2[50] = {0};

  ck_assert_int_eq(sprintf(buf1, "%s %10s %-10s %.3s %10.3s", "hello", "hi",
                           "hi", "abcdef", "abcdef"),
                   my_sprintf(buf2, "%s %10s %-10s %.3s %10.3s", "hello", "hi",
                               "hi", "abcdef", "abcdef"));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_proc) {
  char buf1[20] = {0}, buf2[20] = {0};

  ck_assert_int_eq(sprintf(buf1, "%% Rate: 100%%"),
                   my_sprintf(buf2, "%% Rate: 100%%"));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_f) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%f %10.2f %-10.2f %.0f %#.0f %f %+f %f", 3.141593,
              3.141593, 3.9, 3.9, 123.456, 123.456, 0.0, 12345678.9),
      my_sprintf(buf2, "%f %10.2f %-10.2f %.0f %#.0f %f %+f %f", 3.141593,
                  3.141593, 3.9, 3.9, 123.456, 123.456, 0.0, 12345678.9));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_e) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%e %e %+015.3e %.0e %#.0e %-#12.2e", 123.456, 0.0000123456,
              123.456, 123.456, 123.456, 123.456),
      my_sprintf(buf2, "%e %e %+015.3e %.0e %#.0e %-#12.2e", 123.456,
                  0.0000123456, 123.456, 123.456, 123.456, 123.456));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_E) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%E %E %+015.3E %.0E %#.0E %-#12.2E", 123.456, 0.0000123456,
              123.456, 123.456, 123.456, 123.456),
      my_sprintf(buf2, "%E %E %+015.3E %.0E %#.0E %-#12.2E", 123.456,
                  0.0000123456, 123.456, 123.456, 123.456, 123.456));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_g) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%g %g %+015.3g %.0g %#.0g %-#12.2g", 123.456, 0.0000123456,
              123.456, 123.456, 123.456, 123.456),
      my_sprintf(buf2, "%g %g %+015.3g %.0g %#.0g %-#12.2g", 123.456,
                  0.0000123456, 123.456, 123.456, 123.456, 123.456));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_G) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%G %G %+015.3G %.0G %#.0G %-#12.2G", 123.456, 0.0000123456,
              123.456, 123.456, 123.456, 123.456),
      my_sprintf(buf2, "%G %G %+015.3G %.0G %#.0G %-#12.2G", 123.456,
                  0.0000123456, 123.456, 123.456, 123.456, 123.456));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_dot) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%*c %*.*s %*.*d %*.*u %*.*f %*.*e %*.*E %*.*g %*.*G", 5,
              'A', 10, 4, "abcdefg", 8, 5, 123, 10, 3, 98765u, 10, 3, 3.1415926,
              12, 4, 1234.5678, 12, 4, 1234.5678, 12, 6, 1234.5678, 12, 6,
              1234.5678),
      my_sprintf(buf2, "%*c %*.*s %*.*d %*.*u %*.*f %*.*e %*.*E %*.*g %*.*G",
                  5, 'A', 10, 4, "abcdefg", 8, 5, 123, 10, 3, 98765u, 10, 3,
                  3.1415926, 12, 4, 1234.5678, 12, 4, 1234.5678, 12, 6,
                  1234.5678, 12, 6, 1234.5678));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_L) {
  char buf1[100] = {0}, buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%Lg %LG %Lg %LG %Lg %LG", 123.4567890123456789L,
              123.4567890123456789L, -0.0L, -0.0L, 1e-49L, 1e+49L),
      my_sprintf(buf2, "%Lg %LG %Lg %LG %Lg %LG", 123.4567890123456789L,
                  123.4567890123456789L, -0.0L, -0.0L, 1e-49L, 1e+49L));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_o) {
  char buf1[100] = {0};
  char buf2[100] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%o %#o %5o %-5o %05o %#05o", 83, 83, 83, 83, 83, 83),
      my_sprintf(buf2, "%o %#o %5o %-5o %05o %#05o", 83, 83, 83, 83, 83, 83));
  ck_assert_str_eq(buf1, buf2);
  memset(buf1, 0, sizeof(buf1));
  my_memset(buf2, 0, sizeof(buf2));

  ck_assert_int_eq(sprintf(buf1, "%o %#o", 0, 0),
                   my_sprintf(buf2, "%o %#o", 0, 0));
  ck_assert_str_eq(buf1, buf2);
  memset(buf1, 0, sizeof(buf1));
  my_memset(buf2, 0, sizeof(buf2));

  ck_assert_int_eq(sprintf(buf1, "%o %#o", 4294967295U, 4294967295U),
                   my_sprintf(buf2, "%o %#o", 4294967295U, 4294967295U));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_xX) {
  char buf1[200] = {0}, buf2[200] = {0};

  ck_assert_int_eq(
      sprintf(buf1, "%x %X %#x %#X %10x %-10X %.4x %hx %hX %lx %lX %x %X", 255,
              255, 255, 255, 255, 255, 10, (short)-1, (short)-1,
              (long)123456789, (long)123456789, 0, -1),
      my_sprintf(buf2, "%x %X %#x %#X %10x %-10X %.4x %hx %hX %lx %lX %x %X",
                  255, 255, 255, 255, 255, 255, 10, (short)-1, (short)-1,
                  (long)123456789, (long)123456789, 0, -1));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_p) {
  char buf1[100] = {0}, buf2[100] = {0};

  int a = 42;
  void *ptr1 = &a;
  void *ptr2 = NULL;

  ck_assert_int_eq(sprintf(buf1, "ptr: %p null: %p", ptr1, ptr2),
                   my_sprintf(buf2, "ptr: %p null: %p", ptr1, ptr2));
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_my_sprintf_n) {
  char buf1[100] = {0}, buf2[100] = {0};
  int n1_1 = 0, n1_2 = 0;
  int n2_1 = 0, n2_2 = 0;

  int ret1 = sprintf(buf1, "12345%n6789%n0", &n1_1, &n1_2);
  int ret2 = my_sprintf(buf2, "12345%n6789%n0", &n2_1, &n2_2);

  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(n1_1, n2_1);
  ck_assert_int_eq(n1_2, n2_2);
}
END_TEST

START_TEST(test_my_sprintf_nwf) {
  char buf1[100] = {0}, buf2[100] = {0};
  int n1 = 0, n2 = 0;
  int val = 42;

  int ret1 = sprintf(buf1, "Value: %d%n!", val, &n1);
  int ret2 = my_sprintf(buf2, "Value: %d%n!", val, &n2);

  ck_assert_int_eq(ret1, ret2);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(n1, n2);
}
END_TEST


Suite *string_suite(void) {
  Suite *s = suite_create("String");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_my_sprintf_p);
  tcase_add_test(tc_core, test_my_sprintf_xX);
  tcase_add_test(tc_core, test_my_sprintf_o);
  tcase_add_test(tc_core, test_my_sprintf_L);
  tcase_add_test(tc_core, test_my_sprintf_dot);
  tcase_add_test(tc_core, test_my_sprintf_proc);
  tcase_add_test(tc_core, test_my_sprintf_G);
  tcase_add_test(tc_core, test_my_sprintf_g);
  tcase_add_test(tc_core, test_my_sprintf_E);
  tcase_add_test(tc_core, test_my_sprintf_e);
  tcase_add_test(tc_core, test_my_sprintf_f);
  tcase_add_test(tc_core, test_my_sprintf_s);
  tcase_add_test(tc_core, test_my_sprintf_u);
  tcase_add_test(tc_core, test_my_sprintf_d);
  tcase_add_test(tc_core, test_my_sprintf_c);
  tcase_add_test(tc_core, test_my_sprintf_n);
  tcase_add_test(tc_core, test_my_sprintf_nwf);
  tcase_add_test(tc_core, test_my_memset);
  tcase_add_test(tc_core, test_my_memcpy);
  tcase_add_test(tc_core, test_my_strerror);
  tcase_add_test(tc_core, test_my_memchr);
  tcase_add_test(tc_core, test_my_strpbrk);
  tcase_add_test(tc_core, test_my_strrchr);
  tcase_add_test(tc_core, test_my_strstr);
  tcase_add_test(tc_core, test_my_memcmp);
  tcase_add_test(tc_core, test_my_strtok);
  tcase_add_test(tc_core, test_my_strchr);
  tcase_add_test(tc_core, test_my_strncat);
  tcase_add_test(tc_core, test_my_strncpy);
  tcase_add_test(tc_core, test_my_strncmp);
  tcase_add_test(tc_core, test_my_strcspn);
  tcase_add_test(tc_core, test_my_strlen);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite *s = string_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}