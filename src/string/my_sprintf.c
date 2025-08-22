#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "my_string.h"

int my_sprintf(char *str, const char *format, ...);
void parser_args(const char **cu, char *str, my_size_t *i, va_list func);
int char_to_int(const char **cu);
void uce_spec(int flags[5], int num_flags[3], const char **cu, char *str,
              my_size_t *i, va_list func, int wide, int accuracy);
void process_string(char *s, int flags[5], char *str, my_size_t *i,
                    my_size_t accuracy, int wide, char type);
void process_num(long double num, int flags[5], char *str, my_size_t *i,
                 int wide, int accuracy, char type, uintptr_t up);
void int_to_char(long long num, my_size_t t, char *str, int if_null, char type,
                 int len, int flags[5]);
void process_x(long double num, char *str, char type);
void float_to_char(long double num, char *str, int acc, char type,
                   int flags[5]);
void add_chars(int end, char *str, my_size_t *i, char c);
int choose_the_spec(int len, int acc, char *type);
void use_spec_e(int *len, long double *num);
void add_exp(my_size_t *i, char *str, char type, int len);
void wide_and_accuracy(const char **cu, va_list func, int *wide,
                       my_size_t *accuracy, int flags[5]);
void s_case(char *s, va_list func, int flags[5], char *str, my_size_t *i,
            int wide, int accuracy);
void c_case(char c[1], va_list func, int flags[5], char *str, my_size_t *i,
            int wide, int accuracy);
void d_case(long double num, int flags[5], int num_flags[3], char *str,
            my_size_t *i, va_list func, int wide, int accuracy, char type);
void u_case(long double num, int flags[5], int num_flags[3], char *str,
            my_size_t *i, va_list func, int wide, int accuracy, char type);
void f_case(long double num, int flags[5], int num_flags[3], char *str,
            my_size_t *i, va_list func, int wide, int accuracy);
void double_case(long double num, int flags[5], int num_flags[3], char *str,
                 my_size_t *i, va_list func, int wide, int accuracy,
                 char type);
void sort(char str[10], int idx);
void o_to_int(long long num, int flags[5], char *str, my_size_t *i);
void p_case(uintptr_t up, char *str, my_size_t *i, va_list func, int flags[5],
            int wide, int accuracy, char type);
void process_p(uintptr_t up, char *str);
int count_num_len(int accuracy, int num, char type, char num_str[100]);
void make_str(int wide, int total, int flags[5], int sign, char *str,
              my_size_t *i, char ch, long double num, char type, int zeros,
              int num_len, char num_str[100]);
void n_case(void *n_c, my_size_t *i, va_list func, int num_flags[3]);

int my_sprintf(char *str, const char *format, ...) {
  my_size_t i = 0;
  va_list func;
  va_start(func, format);
  const char *cu = format;
  for (; *cu; cu++) {
    if (*cu != '%') {
      str[i++] = *cu;
    } else {
      parser_args(&cu, str, &i, func);
    }
  }

  va_end(func);
  return i;
}

void parser_args(const char **cu, char *str, my_size_t *i, va_list func) {
  int flags[5] = {0};  // flags[0] для -, flags[1] для +, flags[2] для ' ',
                       // flags[3] для #, flags[4] для 0
  int wide = 0;
  my_size_t accuracy = (my_size_t)-1;
  int num_flags[3] = {
      0};  // num_flags[0] для h, num_flags[1] для l, num_flags[2] для L

  (*cu)++;
  if (**cu == '%')
    str[(*i)++] = **cu;
  else {
    while (**cu == '-' || **cu == '+' || **cu == ' ' || **cu == '#') {
      if (**cu == '-') flags[0]++;
      if (**cu == '+') flags[1]++;
      if (**cu == ' ') flags[2]++;
      if (**cu == '#') flags[3]++;
      (*cu)++;
    }

    if (**cu == '.' || (**cu > 47 && **cu < 58) || **cu == '*')
      wide_and_accuracy(cu, func, &wide, &accuracy, flags);

    if (**cu == 'l' || **cu == 'h' || **cu == 'L') {
      if (**cu == 'h') num_flags[0]++;
      if (**cu == 'l') num_flags[1]++;
      if (**cu == 'L') num_flags[2]++;
      (*cu)++;
    }
    uce_spec(flags, num_flags, cu, str, i, func, wide, accuracy);
  }
}

int char_to_int(const char **cu) {
  int sum = 0;
  while (**cu >= 47 && **cu <= 58) {
    sum = sum * 10 + (**cu - 48);
    *cu += 1;
  }
  return sum;
}

void uce_spec(int flags[5], int num_flags[3], const char **cu, char *str,
              my_size_t *i, va_list func, int wide, int accuracy) {
  long double num = 0;
  char *s = MY_NULL;
  char c[1];
  uintptr_t up = 0;
  long long w_c = 0;
  void *n_c = &w_c;

  if (**cu == 's')
    s_case(s, func, flags, str, i, wide, accuracy);
  else if (**cu == 'c')
    c_case(c, func, flags, str, i, wide, accuracy);
  else if (**cu == 'i' || **cu == 'd')
    d_case(num, flags, num_flags, str, i, func, wide, accuracy, **cu);
  else if (**cu == 'u' || **cu == 'o' || **cu == 'x' || **cu == 'X')
    u_case(num, flags, num_flags, str, i, func, wide, accuracy, **cu);
  else if (**cu == 'f' || **cu == 'e' || **cu == 'E' || **cu == 'g' ||
           **cu == 'G')
    double_case(num, flags, num_flags, str, i, func, wide, accuracy, **cu);
  else if (**cu == 'p')
    p_case(up, str, i, func, flags, wide, accuracy, **cu);
  else if (**cu == 'n') {
    n_case(n_c, i, func, num_flags);
  }
}

void n_case(void *n_c, my_size_t *i, va_list func, int num_flags[3]) {
  n_c = va_arg(func, void *);
  if (!n_c || !i) return;

  if (num_flags[0]) {
    *((short *)n_c) = (short)(*i);
  } else if (num_flags[1]) {
    *((long *)n_c) = (long)(*i);
  } else {
    *((int *)n_c) = (int)(*i);
  }
  //(*i)++;
}

void process_string(char *s, int flags[5], char *str, my_size_t *i,
                    my_size_t accuracy, int wide, char type) {
  int str_len;

  if (type == 's') {
    str_len = accuracy < my_strlen(s) ? accuracy : my_strlen(s);
  } else if (type == 'c') {
    str_len = 1;
  }

  if (!flags[0]) add_chars(wide - str_len, str, i, ' ');
  for (int j = 0; j < str_len; j++) str[(*i)++] = s[j];
  if (flags[0]) add_chars(wide - str_len, str, i, ' ');
}

void process_num(long double num, int flags[5], char *str, my_size_t *i,
                 int wide, int accuracy, char type, uintptr_t up) {
  char num_str[256] = {0};
  char sign = 0;
  char ch = flags[4] ? '0' : ' ';

  if (type == 'd' || type == 'u' || type == 'i' || type == 'o') {
    int_to_char((long long)num, 0, num_str, 1, type, 0, flags);
  } else if (type == 'p') {
    process_p(up, num_str);
  } else if (type == 'x' || type == 'X') {
    process_x(num, num_str, type);
  } else {
    float_to_char(num, num_str, (int)accuracy, type, flags);
  }
  if (type != 'u' && type != 's' && type != 'o' && type != 'x' && type != 'X') {
    if (signbit(num)) sign = '-';
    if (flags[1] && num >= 0) sign = '+';
    if (flags[2] && num >= 0) sign = ' ';
  }

  int num_len = count_num_len(accuracy, num, type, num_str);

  int zeros = 0;
  if (type != 'g' && type != 'G')
    zeros = accuracy > num_len ? accuracy - num_len : 0;
  int total = num_len + zeros + (sign != 0 ? 1 : 0) +
              ((type == 'x' || type == 'X') && flags[3] && num != 0 ? 2 : 0);

  make_str(wide, total, flags, sign, str, i, ch, num, type, zeros, num_len,
           num_str);
}

void make_str(int wide, int total, int flags[5], int sign, char *str,
              my_size_t *i, char ch, long double num, char type, int zeros,
              int num_len, char num_str[100]) {
  int add_sign = 0;

  if (wide > total && !flags[0]) {
    if (flags[4] && sign) {
      str[(*i)++] = sign;
      add_sign++;
    }
    add_chars(wide - total, str, i, ch);
  }
  if (sign != 0 && !add_sign) str[(*i)++] = sign;
  if ((type == 'x' || type == 'X') && flags[3] && num != 0) {
    if (*i < 100) str[(*i)++] = '0';
    if (*i < 100) str[(*i)++] = type;
  }
  add_chars(zeros, str, i, '0');
  for (int j = 0; j < num_len; j++) {
    if (*i < 100) str[(*i)++] = num_str[j];
  }
  if (flags[0] && wide > total) {
    add_chars(wide - total, str, i, ch);
  }
}

int count_num_len(int accuracy, int num, char type, char num_str[100]) {
  return accuracy == 0 && num == 0 &&
                 (type == 'u' || type == 's' || type == 'd' || type == 'i' ||
                  type == 'o')
             ? 0
             : my_strlen(num_str);
}
void process_x(long double num, char *str, char type) {
  long int x = (long int)num;
  my_size_t i = 0;
  int minus = 0;
  int x_num = 0;

  if (x < 0) {
    minus = 1;
    x = -x;
  }

  while (x > 0) {
    int ost = x % 16;
    int osn = i == 0 ? 16 : 15;
    ost = minus ? osn - ost : ost;
    if (ost > 9) {
      int w = type == 'x' ? 0 : 32;
      x_num = ost - 10 + 97 - w;
    } else {
      x_num = ost + 48;
    }
    if (i < 100) str[i++] = x_num;
    x /= 16;
  }

  if (num == 0 && i < 100) str[i] = '0';

  while (minus && i < 8) {
    if (i < 100) str[i++] = type == 'x' ? 102 : 70;
  }

  sort(str, i);
}

void add_chars(int end, char *str, my_size_t *i, char c) {
  for (int j = 0; j < end; j++) str[(*i)++] = c;
}

void int_to_char(long long num, my_size_t t, char *str, int if_null, char type,
                 int len, int flags[5]) {
  my_size_t i = 0;
  my_size_t count = 0;

  if (type != 'o') {
    if (num == 0) {
      if (i < 100) str[i++] = '0';
      if_null = 1;
    } else if (num < 0) {
      num = -num;
    }

    while ((num > 0 || count < t) && i < 99) {
      if (i < 100) str[i++] = (num % 10) + 48;
      num /= 10;
      if ((t > 0 && t == i) && (i < 100)) str[i++] = '.';
      count++;
    }

    if (if_null == 0 && type != 'e' && type != 'E') {
      if (i < 100) str[i++] = '0';
    }

  } else if (type == 'o') {
    o_to_int(num, flags, str, &i);
  }
  sort(str, i);

  if (t == 0 && flags[3] && type != 'o')
    if (i < 100) str[i++] = '.';  // обработка # для E e G g

  if (type == 'e' || type == 'E')
    add_exp(&i, str, type, len);  // добавляю экспоненту в запись

  str[i] = '\0';
}

void o_to_int(long long num, int flags[5], char *str, my_size_t *i) {
  while (num / 8 != 0) {
    if (*i < 100) str[(*i)++] = num % 8 + 48;
    num /= 8;
  }
  if (*i < 100) str[(*i)++] = num + 48;
  if (flags[3] && num != 0 && *i < 100) str[(*i)++] = '0';
}

void float_to_char(long double num, char *str, int acc, char type,
                   int flags[5]) {
  int g_flag = 0;
  int len = 0;
  int if_null = 1;
  if ((int)num == 0) if_null = 0;
  if (acc == -1) acc = 6;
  int is_negative = num < 0;
  if (is_negative) num = -num;
  long double second_num = num;

  if (type == 'g' || type == 'G') {
    long double tmp = num;
    use_spec_e(&len, &tmp);

    if (acc == 0) {
      acc = len < 0 ? -len : len;
      if (len < 0)
        type = 'f';
      else {
        type = type == 'g' ? 'e' : 'E';
        acc = 0;
      }
    } else
      acc = choose_the_spec(len, acc, &type);
    g_flag = 1;
    if (type == 'e' || type == 'E') {
      use_spec_e(&len, &num);
    }
  } else if (type == 'e' || type == 'E')
    use_spec_e(&len, &num);
  if (type == 'e' || type == 'E') second_num = num;

  for (int i = 0; i < acc; i++) {
    second_num *= 10.0;
  }
  second_num = roundl(second_num);

  if (g_flag) {  // Обрезаем хвост нулей для g
    if (second_num == 0.0L)
      acc = 0;
    else {
      while (acc > 0 && ((long long)second_num % 10 == 0)) {
        second_num /= 10.0;
        acc--;
      }
    }
  }
  int_to_char((long long)second_num, acc, str, if_null, type, len, flags);
}

int choose_the_spec(int len, int acc, char *type) {
  if (len >= -4 && len < acc) {
    *type = 'f';
    if (acc > 0) acc -= (len + 1);
  } else {
    *type = *type == 'g' ? 'e' : 'E';
    acc = acc > 0 ? acc - 1 : 0;
  }

  return acc;
}

void use_spec_e(int *len, long double *num) {
  *len = 0;
  if (*num == 0.0L) return;

  while (*num >= 10.0L) {
    *num /= 10.0L;
    (*len)++;
  }

  while (*num > 0.0L && *num < 1.0L) {
    *num *= 10.0L;
    (*len)--;
  }
}

void add_exp(my_size_t *i, char *str, char type, int len) {
  if (*i < 100) str[(*i)++] = type;
  if (*i < 100) str[(*i)++] = len >= 0 ? '+' : '-';

  if (len < 0) len = -len;

  if (len < 10)
    if (*i < 100) str[(*i)++] = '0';

  char exp[10] = {0};

  int temp = len;
  int idx = 0;
  if (temp == 0) {
    exp[idx++] = '0';
  } else {
    while (temp > 0) {
      exp[idx++] = (temp % 10) + '0';
      temp /= 10;
    }
    sort(exp, idx);
  }
  exp[idx] = '\0';

  for (my_size_t j = 0; exp[j] != '\0'; j++)
    if (*i < 100) str[(*i)++] = exp[j];
}

void wide_and_accuracy(const char **cu, va_list func, int *wide,
                       my_size_t *accuracy, int flags[5]) {
  if (**cu != '.') {
    if (**cu == '0') {
      flags[4]++;
      (*cu)++;
    }
    if (**cu != '*')
      *wide = char_to_int(cu);
    else {
      *wide = va_arg(func, int);
      (*cu)++;
    }
  }
  if (**cu == '.') {
    (*cu)++;
    if (**cu != '*')
      *accuracy = char_to_int(cu);
    else {
      *accuracy = va_arg(func, my_size_t);
      (*cu)++;
    }
  }
  if (*wide == 0 && flags[4]) flags[4] = 0;
}

void s_case(char *s, va_list func, int flags[5], char *str, my_size_t *i,
            int wide, int accuracy) {
  s = va_arg(func, char *);
  process_string(s, flags, str, i, accuracy, wide, 's');
}

void c_case(char c[1], va_list func, int flags[5], char *str, my_size_t *i,
            int wide, int accuracy) {
  c[0] = (char)va_arg(func, int);
  process_string(c, flags, str, i, accuracy, wide, 'c');
}

void d_case(long double num, int flags[5], int num_flags[3], char *str,
            my_size_t *i, va_list func, int wide, int accuracy, char type) {
  if (num_flags[0])
    num = (short)va_arg(func, int);
  else if (num_flags[1])
    num = va_arg(func, long);
  else
    num = va_arg(func, int);

  process_num(num, flags, str, i, wide, accuracy, type, 0);
}

void u_case(long double num, int flags[5], int num_flags[3], char *str,
            my_size_t *i, va_list func, int wide, int accuracy, char type) {
  if (num_flags[0])
    num = (unsigned short)va_arg(func, int);
  else if (num_flags[1])
    num = va_arg(func, unsigned long);
  else
    num = va_arg(func, unsigned int);

  process_num(num, flags, str, i, wide, accuracy, type, 0);
}

void p_case(uintptr_t up, char *str, my_size_t *i, va_list func, int flags[5],
            int wide, int accuracy, char type) {
  up = (uintptr_t)va_arg(func, void *);
  process_num(0, flags, str, i, wide, accuracy, type, up);
}

void process_p(uintptr_t up, char *str) {
  my_size_t i = 0;
  char *src = "(nil)";
  if (up == 0) {  // Обработка нуля
    while (src[i] != '\0') {
      str[i] = src[i];
      i++;
    }
  } else {
    while (up > 0) {
      int digit = up % 16;
      str[i++] = digit < 10 ? digit + '0' : digit - 10 + 'a';
      up /= 16;
    }

    str[i++] = 'x';
    str[i++] = '0';

    sort(str, i);
  }
}

void double_case(long double num, int flags[5], int num_flags[3], char *str,
                 my_size_t *i, va_list func, int wide, int accuracy,
                 char type) {
  if (num_flags[2])
    num = va_arg(func, long double);
  else
    num = va_arg(func, double);
  process_num(num, flags, str, i, wide, accuracy, type, 0);
}

void sort(char str[10], int idx) {
  for (int j = 0, k = idx - 1; j < k; j++, k--) {
    char tmp = str[j];
    str[j] = str[k];
    str[k] = tmp;
  }
}