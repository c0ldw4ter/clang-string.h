#ifndef S21_SCANF_H
#define S21_SCANF_H

#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int tipe_hex(const char **s, void *p, int is_short, int is_long);
int tipe_oct(const char **s, void *p, int is_short, int is_long);
int tipe_float(const char **s, void *p, int is_long);
int tipe_uint(const char **s, void *p, int is_short, int is_long);
int tipe_int(const char **s, void *p, int is_short, int is_long);

void star_str(const char **s);
void star_char(const char **s);
void star(const char **s);

int s21_sscanf(const char *str, const char *format, ...);

int s21_isspace(int ch);
int s21_isdigit(int ch);

int s21_isxdigit(int c);
int detect_base(const char **ptr);
int tohex(char c);

#endif  // S21_SCANF_H
