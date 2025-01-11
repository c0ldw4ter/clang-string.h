#include "s21_sscanf.h"

#include "s21_string.h"

void star(const char **s) {
  while (s21_isspace(**s)) {
    (*s)++;
  }
  while (**s == '-' || **s == '+') {
    (*s)++;
  }

  while (s21_isdigit(**s)) {
    (*s)++;
  }
}

void star_char(const char **s) {
  while (s21_isspace(**s)) {
    (*s)++;
  }
  if (**s != '\0') {
    (*s)++;
  }
}

void star_str(const char **s) {
  while (s21_isspace(**s)) {
    (*s)++;
  }
  while (**s != ' ' && **s != '\0') {
    (*s)++;
  }
}

int tipe_int(const char **s, void *p, int is_short, int is_long) {
  int count = 0;
  int sing = 1;

  while (s21_isspace(**s)) {
    (*s)++;
  }
  while (**s == '-' || **s == '+') {
    if (**s == '-') sing = -1;
    if (**s == '+') {
    }
    (*s)++;
  }
  long long num = 0;
  int digits_read = 0;
  while (s21_isdigit(**s)) {
    num = num * 10 + (**s - '0');
    (*s)++;
    digits_read++;
  }
  if (digits_read == 0) return count;

  num *= sing;
  count++;

  if (is_short) {
    short *sp = (short *)p;
    *sp = (short)num;

  } else if (is_long == 1) {
    long *lp = (long *)p;
    *lp = (long)num;

  } else if (is_long == 2) {
    long long *llp = (long long *)p;
    *llp = num;
  }

  else {
    int *ip = (int *)p;
    *ip = (int)num;
  }
  return count;
}
int tipe_uint(const char **s, void *p, int is_short, int is_long) {
  int count = 0;

  while (s21_isspace(**s)) {
    (*s)++;
  }
  while (**s == '-' || **s == '+') {
    (*s)++;
  }
  unsigned long long num = 0;
  int digits_read = 0;
  while (s21_isdigit(**s)) {
    num = num * 10 + (**s - '0');
    (*s)++;
    digits_read++;
  }
  if (digits_read == 0) return count;

  count++;

  if (is_short) {
    unsigned short *sp = (unsigned short *)p;
    *sp = (unsigned short)num;
  } else if (is_long == 1) {
    unsigned long *lp = (unsigned long *)p;
    *lp = (unsigned long)num;
  } else if (is_long == 2) {
    unsigned long long *llp = (unsigned long long *)p;
    *llp = num;
  } else {
    unsigned int *ip = (unsigned int *)p;
    *ip = (unsigned int)num;
  }

  return count;
}

int tipe_float(const char **s, void *p, int is_long) {
  int count = 0;
  int sing = 1;

  while (s21_isspace(**s)) {
    (*s)++;
  }
  while (**s == '-' || **s == '+') {
    if (**s == '-') sing = -1;
    if (**s == '+') {
    }
    (*s)++;
  }
  long double num = 0;
  int digit = 0;
  while (s21_isdigit(**s)) {
    num = num * 10.0f + (**s - '0');
    (*s)++;
    digit++;
  }
  if (**s == '.') {
    (*s)++;

    long double div = 10.0f;
    while (s21_isdigit(**s)) {
      num += (**s - '0') / div;
      div *= 10.0f;
      (*s)++;
    }
  }
  if (digit == 0) return count;
  num *= sing;
  count++;
  if (is_long == 2) {
    long double *lf = (long double *)p;
    *lf = num;
  } else {
    float *fp = (float *)p;
    *fp = (float)num;
  }
  return count;
}

int tipe_oct(const char **s, void *p, int is_short, int is_long) {
  int count = 0;
  unsigned long long num = 0;
  int digits_read = 0;

  while (s21_isspace(**s)) {
    (*s)++;
  }

  while (s21_isdigit(**s) && **s < '8') {
    num = num * 8 + (**s - '0');
    (*s)++;
    digits_read++;
  }

  if (digits_read == 0) {
    return count;
  }

  count++;

  if (is_short) {
    unsigned short *sp = (unsigned short *)p;
    *sp = (unsigned short)num;
  } else if (is_long == 1) {
    unsigned long *lp = (unsigned long *)p;
    *lp = (unsigned long)num;
  } else if (is_long == 2) {
    unsigned long long *llp = (unsigned long long *)p;
    *llp = num;
  } else {
    unsigned int *ip = (unsigned int *)p;
    *ip = (unsigned int)num;
  }

  return count;
}
int tipe_hex(const char **s, void *p, int is_short, int is_long) {
  int count = 0;
  unsigned long long num = 0;
  int digits_read = 0;

  while (s21_isspace(**s)) {
    (*s)++;
  }

  if (**s == '0' && ((*s)[1] == 'x' || (*s)[1] == 'X')) {
    (*s) += 2;
  }
  while (s21_isxdigit(**s)) {
    if (s21_isdigit(**s)) {
      num = num * 16 + (**s - '0');
    } else {
      num = num * 16 + (tolower(**s) - 'a' + 10);
    }
    (*s)++;
    digits_read++;
  }

  if (digits_read == 0) {
    return count;
  }

  count++;

  if (is_short) {
    unsigned short *sp = (unsigned short *)p;
    *sp = (unsigned short)num;
  } else if (is_long == 1) {
    unsigned long *lp = (unsigned long *)p;
    *lp = (unsigned long)num;
  } else if (is_long == 2) {
    unsigned long long *llp = (unsigned long long *)p;
    *llp = num;
  } else {
    unsigned int *ip = (unsigned int *)p;
    *ip = (unsigned int)num;
  }

  return count;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count = 0;

  const char *s = str;
  const char *f = format;

  while (s21_isspace(*s)) {
    s++;
  }
  if (*s == '\0') {
    va_end(args);
    return EOF;
  }
  if (*f == '\0') {
    va_end(args);
    return EOF;
  }
  while (*f != '\0') {
    while (s21_isspace(*f)) {
      f++;
    }

    if (*f == '%') {
      f++;
      int is_long = 0;
      int is_short = 0;
      int the_star = 0;
      if (*f == '%') {
        f++;
        while (s21_isspace(*s)) {
          s++;
        }
        if (*f == '%') {
          if (*s == *f) {
            s++;
            f++;
          }
        }
      }
      if (*f == '*') {
        the_star = 1;
        f++;
      }

      if (*f == 'h') {
        is_short = 1;
        f++;
      } else if (*f == 'l') {
        is_long = 1;
        f++;
        if (*f == 'l') {
          is_long++;
          f++;
        }
      } else if (*f == 'L') {
        is_long = 2;
        f++;
      }
      if (!s21_strchr("dfeEgGicspnuoXx", *f)) {
        va_end(args);
        return count;
      }

      switch (*f) {
        case 'd': {
          if (the_star)
            star(&s);
          else {
            void *p = va_arg(args, void *);
            // if ((tipe_int(&s, p, is_short, is_long)) == NULL)

            count += tipe_int(&s, p, is_short, is_long);
          }
          break;
        }
        case 'u': {
          if (the_star) {
            star(&s);
          } else {
            void *p = va_arg(args, void *);
            count += tipe_uint(&s, p, is_short, is_long);
          }
          break;
        }

        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'f': {
          if (the_star)
            star(&s);
          else {
            void *p = va_arg(args, void *);
            count += tipe_float(&s, p, is_long);
          }
          break;
        }
        case 's': {
          if (the_star)
            star_str(&s);

          else {
            char *p = va_arg(args, char *);

            while (s21_isspace(*s)) {
              s++;
            }

            while (*s != ' ' && *s != '\0') {
              *p++ = *s++;
            }
            *p = '\0';

            count++;
          }
          break;
        }
        case 'c': {
          if (the_star)
            star_char(&s);
          else {
            char *p = va_arg(args, char *);
            while (s21_isspace(*s)) {
              s++;
            }
            *p++ = *s++;
            count++;
          }
          break;
        }
        case 'o': {
          if (the_star) {
            star(&s);
          } else {
            void *p = va_arg(args, void *);
            int res = tipe_oct(&s, p, is_short, is_long);
            if (res == 0) {
              va_end(args);
              return count;
            }
            count += res;
          }
          break;
        }
        case 'x':
        case 'X': {
          if (the_star) {
            star(&s);
          } else {
            void *p = va_arg(args, void *);
            int res = tipe_hex(&s, p, is_short, is_long);
            if (res == 0) {
              va_end(args);
              return 0;
            }
            count += res;
          }
          break;
        }
        case 'i': {
          if (the_star) {
            star(&s);
          } else {
            void *p = va_arg(args, void *);
            int base = detect_base(&s);
            if (base == 10) {
              tipe_int(&s, p, is_short, is_long);
            } else if (base == 16) {
              tipe_hex(&s, p, is_short, is_long);
            } else {
              tipe_oct(&s, p, is_short, is_long);
            }
            count++;
          }
          break;
        }

        case 'n': {
          if (the_star) {
            star(&s);
          } else {
            int *p = va_arg(args, int *);
            *p = (int)(s - str);
            while (s21_isspace(*s)) {
              s++;
            }
            *p = (int)(s - str);
            // count++;
          }
          break;
        }

        case 'p': {
          if (the_star) {
            star(&s);
          } else {
            void **p = va_arg(args, void **);
            *p = NULL;

            while (s21_isspace(*s)) {
              s++;
            }

            if (*s == '0' && tolower(*(s + 1)) == 'x') {
              s += 2;
            }

            void *ptr = NULL;
            while (s21_isxdigit(*s)) {
              int digit = tohex(*s);
              ptr = (void *)((uintptr_t)ptr * 16 + digit);
              s++;
            }

            *p = ptr;
            count++;
          }
          break;
        }
        default:
          break;
      }
      f++;
    } else {
      if (*s == *f) {
        s++;
        f++;
      } else {
        break;
      }
    }
  }

  va_end(args);
  return count;
}

int s21_isspace(int ch) {
  int c = 0;
  if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f' ||
      ch == '\v') {
    c = 1;
  }
  return c;
}

int s21_isdigit(int ch) {
  int c = 0;
  if (ch >= '0' && ch <= '9') {
    c = 1;
  }
  return c;
}

int s21_isxdigit(int c) {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
         (c >= 'A' && c <= 'F');
}

int detect_base(const char **ptr) {
  int base = 10;
  while (s21_isspace(**ptr)) {
    (*ptr)++;
  }
  if (**ptr == '0') {
    (*ptr)++;
    if (**ptr == 'x' || **ptr == 'X') {
      base = 16;
      (*ptr)++;
    } else {
      base = 8;
    }
  }
  return base;
}

int tohex(char c) {
  int ch;
  if (c >= '0' && c <= '9') {
    ch = c - '0';
  } else if (c >= 'a' && c <= 'f') {
    ch = c - 'a' + 10;
  } else if (c >= 'A' && c <= 'F') {
    ch = c - 'A' + 10;
  } else {
    ch = -1;
  }
  return ch;
}
