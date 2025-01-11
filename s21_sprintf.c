#include "s21_string.h"

void s21_reverse(char *str, int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

int s21_int_str(long num, char *str, int precision, bool is_unsigned) {
  int i = 0;
  bool is_negative = false;

  if (!is_unsigned && num < 0) {
    is_negative = true;
    num = -num;
  }

  if (num == 0) {
    str[i++] = '0';
  } else {
    while (num != 0) {
      str[i++] = (char)((num % 10) + '0');
      num /= 10;
    }
  }

  while (i < precision) {
    str[i++] = '0';
  }

  if (is_negative) {
    str[i++] = '-';
  }

  s21_reverse(str, i);
  str[i] = '\0';
  return i;
}

void s21_putchar(char **buffer, char c) {
  **buffer = c;
  (*buffer)++;
}

void s21_putstr(char **buffer, const char *str, int len) {
  for (int i = 0; i < len; i++) {
    s21_putchar(buffer, str[i]);
  }
}

void s21_putint(char **buffer, long num, int width, int precision,
                bool left_align, bool show_sign, bool space, bool is_unsigned) {
  char num_str[50];
  int len = s21_int_str(num, num_str, precision, is_unsigned);

  if (show_sign && num >= 0) {
    s21_putchar(buffer, '+');
  } else if (space && num >= 0) {
    s21_putchar(buffer, ' ');
  }

  if (width > len && !left_align) {
    for (int i = 0; i < width - len; i++) {
      s21_putchar(buffer, ' ');
    }
  }

  s21_putstr(buffer, num_str, len);

  if (width > len && left_align) {
    for (int i = 0; i < width - len; i++) {
      s21_putchar(buffer, ' ');
    }
  }
}

void s21_putfloat(char **buffer, double num, int precision, bool show_sign,
                  bool space) {
  if (precision < 0) {
    precision = 6;
  }

  if (num < 0) {
    s21_putchar(buffer, '-');
    num = -num;
  } else if (show_sign) {
    s21_putchar(buffer, '+');
  } else if (space) {
    s21_putchar(buffer, ' ');
  }

  long int_part = (long)num;
  double frac_part = num - (double)int_part;

  char int_str[20];
  int int_len = s21_int_str(int_part, int_str, 0, false);
  s21_putstr(buffer, int_str, int_len);

  s21_putchar(buffer, '.');

  // Умножаем дробную часть на 10^precision и округляем
  frac_part = round(frac_part * pow(10, precision));

  char frac_str[20];
  int frac_len = s21_int_str((long)frac_part, frac_str, precision, true);
  s21_putstr(buffer, frac_str, frac_len);
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char *buffer = str;
  const char *p = format;

  while (*p) {
    if (*p == '%') {
      p++;

      bool left_align = false;
      bool show_sign = false;
      bool space = false;
      while (*p == '-' || *p == '+' || *p == ' ') {
        if (*p == '-') {
          left_align = true;
        } else if (*p == '+') {
          show_sign = true;
        } else if (*p == ' ') {
          space = true;
        }
        p++;
      }

      int width = 0;
      while (*p >= '0' && *p <= '9') {
        width = width * 10 + (*p - '0');
        p++;
      }

      int precision = -1;
      if (*p == '.') {
        precision = 0;
        p++;
        while (*p >= '0' && *p <= '9') {
          precision = precision * 10 + (*p - '0');
          p++;
        }
      }

      bool length_long = false;
      bool length_short = false;
      if (*p == 'l') {
        length_long = true;
        p++;
      } else if (*p == 'h') {
        length_short = true;
        p++;
      }

      switch (*p) {
        case 'd':
        case 'i': {
          long i;
          if (length_long) {
            i = va_arg(args, long);
          } else if (length_short) {
            i = (short)va_arg(args, int);
          } else {
            i = va_arg(args, int);
          }
          s21_putint(&buffer, i, width, precision, left_align, show_sign, space,
                     false);
          break;
        }
        case 'u': {
          unsigned long u;
          if (length_long) {
            u = va_arg(args, unsigned long);
          } else if (length_short) {
            u = (unsigned short)va_arg(args, unsigned int);
          } else {
            u = va_arg(args, unsigned int);
          }
          s21_putint(&buffer, (long)u, width, precision, left_align, false,
                     false, true);
          break;
        }
        case 'c': {
          int c = va_arg(args, int);
          s21_putchar(&buffer, (char)c);
          break;
        }
        case 's': {
          char *s = va_arg(args, char *);
          int len = s21_strlen(s);
          if (precision >= 0 && precision < len) {
            len = precision;
          }
          if (width > len && !left_align) {
            for (int i = 0; i < width - len; i++) {
              s21_putchar(&buffer, ' ');
            }
          }
          s21_putstr(&buffer, s, len);
          if (width > len && left_align) {
            for (int i = 0; i < width - len; i++) {
              s21_putchar(&buffer, ' ');
            }
          }
          break;
        }
        case 'f': {
          double d = va_arg(args, double);
          s21_putfloat(&buffer, d, precision, show_sign, space);
          break;
        }
        case '%': {
          s21_putchar(&buffer, '%');
          break;
        }
      }
    } else {
      s21_putchar(&buffer, *p);
    }
    p++;
  }

  va_end(args);
  *buffer = '\0';

  return (int)(buffer - str);
}