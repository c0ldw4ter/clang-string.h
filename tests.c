#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(S21_MEMCHR) {
  char str1[] = "abcdef";
  int a = 'a';
  size_t n1 = 3;
  ck_assert_ptr_eq(s21_memchr(str1, a, n1), memchr(str1, a, n1));

  char str2[] = "abcdef";
  int b = 'z';
  size_t n2 = 5;
  ck_assert_ptr_eq(s21_memchr(str2, b, n2), memchr(str2, b, n2));

  char str3[] = "abcdef";
  int c = 'a';
  size_t n3 = 0;
  ck_assert_ptr_eq(s21_memchr(str3, c, n3), memchr(str3, c, n3));

  char str4[] = "abcdef";
  int c1 = '\0';
  size_t n4 = 7;
  ck_assert_ptr_eq(s21_memchr(str4, c1, n4), memchr(str4, c1, n4));
}
END_TEST

START_TEST(S21_MEMCMP) {
  char str1[] = "abcdef";
  char str2[] = "abcxyz";
  ck_assert_int_eq(s21_memcmp(str1, str2, 3), memcmp(str1, str2, 3));
  ck_assert_msg(s21_memcmp(str1, str2, 4) < 0 && memcmp(str1, str2, 4) < 0,
                "FAILURE!");
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
  ck_assert_int_eq(s21_memcmp("", "", 0), memcmp("", "", 0));
  ck_assert_msg(
      s21_memcmp("abcd", "wxyz", 4) < 0 && memcmp("abcd", "wxyz", 4) < 0,
      "FAILURE!");
  ck_assert_int_eq(s21_memcmp("ab", "abc", 2), memcmp("ab", "abc", 2));
  ck_assert_msg(s21_memcmp("abc", "ab", 3) > 0 && memcmp("abc", "ab", 3) > 0,
                "FAILURE!");
}
END_TEST

START_TEST(S21_MEMCPY) {
  char dest1[100] = {0};
  char dest2[100] = {0};
  ck_assert_msg(
      memcmp(s21_memcpy(dest1, "abc", 3), memcpy(dest2, "abc", 3), 100) == 0,
      "FAILURE!");
  ck_assert_msg(
      memcmp(s21_memcpy(dest1, "abc", 1), memcpy(dest2, "abc", 1), 100) == 0,
      "FAILURE!");
  ck_assert_msg(
      memcmp(s21_memcpy(dest1, "", 0), memcpy(dest2, "", 0), 100) == 0,
      "FAILURE!");
  ck_assert_msg(memcmp(s21_memcpy(dest1, "abcdef", 4),
                       memcpy(dest2, "abcdEf", 4), 100) == 0,
                "FAILURE!");
}
END_TEST

START_TEST(S21_MEMSET) {
  char dest1[100] = "abcdef";
  char dest2[100] = "abcdef";
  ck_assert_msg(
      memcmp(s21_memset(dest1, 'a', 2), memset(dest2, 'a', 2), 100) == 0,
      "FAILURE!");
  ck_assert_msg(memcmp(s21_memset(dest1, dest1[2], 4),
                       memset(dest2, dest2[2], 4), 100) == 0,
                "FAILURE!");
  ck_assert_msg(memcmp(s21_memset(dest1, dest1[2], 10),
                       memset(dest2, dest2[2], 10), 100) == 0,
                "FAILURE!");
  ck_assert_msg(
      memcmp(s21_memset(dest1, ' ', 2), memset(dest2, ' ', 2), 100) == 0,
      "FAILURE!");
}
END_TEST

START_TEST(S21_STRNCAT) {
  char dest1[100] = "abcdef";
  char dest2[100] = "abcdef";
  char app[10] = "12345";
  ck_assert_msg(
      memcmp(s21_strncat(dest1, app, 3), strncat(dest2, app, 3), 100) == 0,
      "FAILURE!");
  ck_assert_msg(
      memcmp(s21_strncat(dest1, app, 0), strncat(dest2, app, 0), 100) == 0,
      "FAILURE!");
  ck_assert_msg(
      memcmp(s21_strncat(dest1, app, 20), strncat(dest2, app, 20), 100) == 0,
      "FAILURE!");
}
END_TEST

START_TEST(S21_STRCHR) {
  char msg[50] = "Hello, World!";
  ck_assert_msg(strcmp(s21_strchr(msg, '\0'), strchr(msg, '\0')) == 0,
                "FAILURE!");
  ck_assert_msg(strcmp(s21_strchr(msg, ','), strchr(msg, ',')) == 0,
                "FAILURE!");
  ck_assert_msg(strcmp(s21_strchr(msg, ' '), strchr(msg, ' ')) == 0,
                "FAILURE!");
  ck_assert_msg(strcmp(s21_strchr("", '\0'), strchr("", '\0')) == 0,
                "FAILURE!");
  ck_assert_msg(s21_strchr(msg, 'X') == strchr(msg, 'X'), "FAILURE!");
}
END_TEST

START_TEST(S21_STRNCMP) {
  ck_assert_int_eq(s21_strncmp("", "", 1), strncmp("", "", 1));
  ck_assert_int_gt(s21_strncmp("abc", "a", 2), 0);
  ck_assert_int_lt(s21_strncmp("abc", "az", 2), 0);
  ck_assert_int_eq(s21_strncmp("a", "abc", 1), strncmp("a", "abc", 1));
  ck_assert_int_eq(s21_strncmp("ab", "aaa", 2), strncmp("ab", "aaa", 2));
  ck_assert_int_eq(s21_strncmp("abcdef", "abcdeF", 5),
                   strncmp("abcdef", "abcdeF", 5));
  ck_assert_int_eq(s21_strncmp("abcdef", "abcdef", 9),
                   strncmp("abcdef", "abcdef", 9));
  ck_assert_int_eq(s21_strncmp("abcdeF", "abcdef", 9),
                   strncmp("abcdeF", "abcdef", 9));
  ck_assert_int_eq(s21_strncmp("abc", "abcdef", 9),
                   strncmp("abc", "abcdef", 9));
}
END_TEST

START_TEST(S21_STRNCPY) {
  char dest1[50] = "abcde";
  char dest2[50] = "abcde";
  ck_assert_msg(strcmp(s21_strncpy(dest1, "", 1), strncpy(dest2, "", 1)) == 0,
                "FAILURE!");
  ck_assert_msg(
      strcmp(s21_strncpy(dest1, "TEST?", 6), strncpy(dest2, "TEST?", 6)) == 0,
      "FAILURE!");
  ck_assert_msg(
      strcmp(s21_strncpy(dest1, "HAhaHA", 9), strncpy(dest2, "HAhaHA", 9)) == 0,
      "FAILURE!");
  ck_assert_msg(strcmp(s21_strncpy(dest1, "", 2), strncpy(dest2, "", 2)) == 0,
                "FAILURE!");
}
END_TEST

START_TEST(S21_STRCSPN) {
  ck_assert_msg(s21_strcspn("", "") == strcspn("", ""), "FAILURE!");
  ck_assert_msg(s21_strcspn("", "test") == strcspn("", "test"), "FAILURE!");
  ck_assert_msg(s21_strcspn("testing cspn func", "ezt") ==
                    strcspn("testing cspn func", "ezt"),
                "FAILURE!");
  ck_assert_msg(s21_strcspn("testing cspn func", "EZT") ==
                    strcspn("testing cspn func", "EZT"),
                "FAILURE!");
  ck_assert_msg(s21_strcspn("test was success!", " ") ==
                    strcspn("test was success!", " "),
                "FAILURE!");
}
END_TEST

START_TEST(S21_STRERROR) {
  char *err1 = s21_strerror(0);
  char *err2 = strerror(0);
  ck_assert_int_eq(strcmp(err1, err2), 0);

  char *err3 = s21_strerror(106);
  char *err4 = strerror(106);
  ck_assert_int_eq(strcmp(err3, err4), 0);

  char *err5 = s21_strerror(29925917);
  char *err6 = strerror(29925917);
  ck_assert_int_eq(strcmp(err5, err6), 0);

  char *err7 = s21_strerror(-29925917);
  char *err8 = strerror(-29925917);
  ck_assert_int_eq(strcmp(err7, err8), 0);
}

START_TEST(S21_STRLEN) {
  ck_assert_msg(s21_strlen("") == strlen(""), "FAILURE!");
  ck_assert_msg(s21_strlen("ab\0c") == strlen("ab\0c"), "FAILURE!");
  ck_assert_msg(s21_strlen("123 ") == strlen("123 "), "FAILURE!");
  ck_assert_msg(s21_strlen(" l") == strlen(" l"), "FAILURE!");
  ck_assert_msg(s21_strlen("\0abc") == strlen("\0abc"), "FAILURE!");
}
END_TEST

START_TEST(S21_STRPBRK) {
  char example[20] = "this is";
  ck_assert_ptr_eq(s21_strpbrk(example, "abs"), strpbrk(example, "abs"));
  ck_assert_ptr_eq(s21_strpbrk(example, "th"), strpbrk(example, "th"));
  ck_assert_ptr_eq(s21_strpbrk(example, "hi"), strpbrk(example, "hi"));
  ck_assert_ptr_eq(s21_strpbrk(example, ""), strpbrk(example, ""));
  ck_assert_ptr_eq(s21_strpbrk(example, "dplf"), strpbrk(example, "dplf"));
}
END_TEST

START_TEST(S21_STRRCHR) {
  char example[20] = "Hello, World!";
  ck_assert_ptr_eq(s21_strrchr(example, '\0'), strrchr(example, '\0'));
  ck_assert_ptr_eq(s21_strrchr(example, ','), strrchr(example, ','));
  ck_assert_ptr_eq(s21_strrchr(example, 'h'), strrchr(example, 'h'));
  ck_assert_ptr_eq(s21_strrchr(example, ' '), strrchr(example, ' '));
  ck_assert_ptr_eq(s21_strrchr("", '\0'), strrchr("", '\0'));
}
END_TEST

START_TEST(S21_STRSTR) {
  char example[30] = "Testing s21_strstr func";
  ck_assert_ptr_eq(s21_strstr(example, ""), strstr(example, ""));
  ck_assert_ptr_eq(s21_strstr(example, "es"), strstr(example, "es"));
  ck_assert_ptr_eq(s21_strstr(example, "s21_strstr"),
                   strstr(example, "s21_strstr"));
  ck_assert_ptr_eq(s21_strstr(example, "no match"),
                   strstr(example, "no match"));
}
END_TEST

START_TEST(S21_STRTOK) {
  char str1[30] = "One two,three. four";
  char str2[30] = "One two,three. four";
  char delim[10] = " .,";
  char *res1 = s21_strtok(str1, delim);
  char *res2 = strtok(str2, delim);

  while (res1 != NULL || res2 != NULL) {
    ck_assert_int_eq(strcmp(res1, res2), 0);
    res1 = s21_strtok(NULL, delim);
    res2 = strtok(NULL, delim);
  }
  ck_assert_msg(res1 == res2, "FAILURE!");
}
END_TEST

START_TEST(S21_SPRINTF) {
  char MESSAGE_1[500];
  char MESSAGE_2[500];

  char TEST_c = '5';
  int TEST_d = -21475;
  int TEST_i = -50000;
  double TEST_f = -50.4324;
  char TEST_s[20] = "FLAMES";
  int TEST_u = -3857;

  s21_sprintf(MESSAGE_1, "|%c|%d|%i|%f|%s|%u|%%|", TEST_c, TEST_d, TEST_i,
              TEST_f, TEST_s, TEST_u);
  sprintf(MESSAGE_2, "|%c|%d|%i|%f|%s|%u|%%|", TEST_c, TEST_d, TEST_i, TEST_f,
          TEST_s, TEST_u);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #1.1 - FAILED!");

  char TEST_c2 = '5';
  TEST_d = 0;
  TEST_i = -50000;
  TEST_f = 50.4324;
  char TEST_s2[20] = " ";
  TEST_u = -3857;

  s21_sprintf(MESSAGE_1, "|%c|%+d|%i|%+f|%s|%u|%%|", TEST_c2, TEST_d, TEST_i,
              TEST_f, TEST_s2, TEST_u);
  sprintf(MESSAGE_2, "|%c|%+d|%i|%+f|%s|%u|%%|", TEST_c2, TEST_d, TEST_i,
          TEST_f, TEST_s2, TEST_u);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #1.2 - FAILED!");

  char TEST_c3 = '5';
  TEST_d = 0;
  TEST_i = -50000;
  TEST_f = 50.4324;
  char TEST_s3[20] = "";
  TEST_u = -3857;

  s21_sprintf(MESSAGE_1, "|%c|% d|%5i|% f|%s|%u|%%|", TEST_c3, TEST_d, TEST_i,
              TEST_f, TEST_s3, TEST_u);
  sprintf(MESSAGE_2, "|%c|% d|%5i|% f|%s|%u|%%|", TEST_c3, TEST_d, TEST_i,
          TEST_f, TEST_s3, TEST_u);
  ck_assert_msg(strcmp(MESSAGE_1, MESSAGE_2) == 0, "TEST #1.3 - FAILED!");
}
END_TEST

START_TEST(S21_SSCANF) {
  char a, b, c;  // chars
  char a1, b1, c1;
  s21_sscanf("abcdefABCDEF", "%c %*c %c %c   ", &a, &b, &c);
  sscanf("abcdefABCDEF", "%c %*c %c %c   ", &a1, &b1, &c1);
  s21_sscanf("ab", "%2c", &c);
  s21_sscanf("ab", "%2c", &c1);
  ck_assert_int_eq(a, a1);
  ck_assert_int_eq(b, b1);
  ck_assert_int_eq(c, c1);

  int x, y, z = 0;  // ints
  int x1, y1, z1 = 0;
  s21_sscanf("+12 -23 .54", "%d %d%d", &x, &y, &z);
  sscanf("+12 -23 .54", "%d %d %d", &x1, &y1, &z1);
  ck_assert_int_eq(x, x1);
  ck_assert_int_eq(y, y1);
  ck_assert_int_eq(z, z1);

  s21_sscanf("0775 0x1324--123", " %i %*i %i-  %i", &x, &y, &z);
  sscanf("0775 0x1324--123", " %i %*i %i- %i", &x1, &y1, &z1);
  ck_assert_int_eq(x, x1);
  ck_assert_int_eq(y, y1);
  ck_assert_int_eq(z, z1);

  unsigned short usx, usx1;
  unsigned int ux, ux1;
  unsigned long ulx, ulx1;
  int ullx, ullx1;
  s21_sscanf("0 2112 -12324", "%o %lo %o", &ux, &ulx, &ullx);
  sscanf("0 2112 -12324", "%o %lo %o", &ux1, &ulx1, &ullx1);
  ck_assert_int_eq(ux, ux1);
  ck_assert_int_eq(ulx, ulx1);

  s21_sscanf("0 0x211a 12324 0x1", "%x %lx %x %hx", &ux, &ulx, &ullx, &usx);
  sscanf("0 0x211a 12324 0x1", "%x %lx %x %hx", &ux1, &ulx1, &ullx1, &usx1);
  ck_assert_int_eq(usx, usx1);
  ck_assert_int_eq(ux, ux1);
  ck_assert_int_eq(ulx, ulx1);
  ck_assert_int_eq(ullx, ullx1);

  x = 0, x1 = 0;  // errors
  s21_sscanf("a21", "%d", &x);
  sscanf("a21", "%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("a21", "b%d", &x);
  sscanf("a21", "b%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("--a21", "%d", &x);
  sscanf("--a21", "%d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21", "%1d", &x);
  sscanf("-21", "%1d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21", "%%%1d", &x);
  sscanf("-21", "%%%1d", &x1);
  ck_assert_int_eq(x, x1);
  s21_sscanf("-21   ", "%d %d", &x, &y);
  sscanf("-21   ", "%d %d", &x1, &y1);
  ck_assert_int_eq(x, x1);

  float fx, fx1;  // floats
  s21_sscanf("1 2 -123232.001 .995123 999.99", "%*E %*G %g", &fx);
  sscanf("1 2 -123232.001 .995123 999.99", "%*E %*G %g", &fx1);
  ck_assert_double_eq(fx, fx1);

  char str[100];  // strings
  char p_str[100];
  s21_sscanf("Hello world", "%*s %s", str);
  sscanf("Hello world", "%*s %s", p_str);
  ck_assert_msg(strcmp(str, p_str) == 0, "str fail");

  void *addr1 = s21_NULL, *addr2 = s21_NULL, *addr3 = s21_NULL;
  void *paddr1 = NULL, *paddr2 = NULL, *paddr3 = NULL;
  s21_sscanf("0x1abcd -0xfffffffff +0xffffffffffffffffffaaa", "%p %n%p %p",
             &addr1, &x, &addr2, &addr3);
  sscanf("0x1abcd -0xfffffffff +0xffffffffffffffffffaaa", "%p %n%p %p", &paddr1,
         &x1, &paddr2, &paddr3);

  float af1 = 0, af2 = 0, bf1 = 0, bf2 = 0, cf1 = 0, cf2 = 0, df1 = 0, df2 = 0;

  const char strf[] =
      "15.5        0.33                   -0.1111         435435.4534";
  const char fstr[] = "%G %G %G %G";

  int res1 = s21_sscanf(strf, fstr, &af1, &bf1, &cf1, &df1);
  int res2 = sscanf(strf, fstr, &af2, &bf2, &cf2, &df2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(af1, af2);
  ck_assert_ldouble_eq(bf1, bf2);
  ck_assert_ldouble_eq(cf1, cf2);
  ck_assert_ldouble_eq(df1, df2);

  long double al1 = 0, al2 = 0, bl1 = 0, bl2 = 0, cl1 = 0, cl2 = 0, dl1 = 0,
              dl2 = 0;
  const char strf3[] = "1.4441 1.313 -3.31 0.444";

  res1 = s21_sscanf(strf3, "%LG %LG %LG %LG", &al1, &bl1, &cl1, &dl1);
  res2 = sscanf(strf3, "%LG %LG %LG %LG", &al2, &bl2, &cl2, &dl2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(al1, al2);
  ck_assert_ldouble_eq_tol(bl1, bl2, 0.000001);
  ck_assert_ldouble_eq(cl1, cl2);
  ck_assert_ldouble_eq(dl1, dl2);

  res1 = s21_sscanf(strf3, "%u", &ullx1);
  res2 = sscanf(strf3, "%u", &ullx);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(ullx, ullx1);
}
END_TEST

START_TEST(S21_TO_UPPER) {
  char *ptr = s21_to_upper("abcde");
  ck_assert_msg(strcmp(ptr, "ABCDE") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_upper("aBcDe5");
  ck_assert_msg(strcmp(ptr, "ABCDE5") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_upper("!?123");
  ck_assert_msg(strcmp(ptr, "!?123") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_upper(" ");
  ck_assert_msg(strcmp(ptr, " ") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_upper("!?123a");
  ck_assert_msg(strcmp(ptr, "!?123A") == 0, "FAILURE!");
  free(ptr);
}
END_TEST

START_TEST(S21_TO_LOWER) {
  char *ptr = s21_to_lower("ABCDE");
  ck_assert_msg(strcmp(ptr, "abcde") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_lower("AbCdE5");
  ck_assert_msg(strcmp(ptr, "abcde5") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_lower("!?123");
  ck_assert_msg(strcmp(ptr, "!?123") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_lower(" ");
  ck_assert_msg(strcmp(ptr, " ") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_to_lower("!?123A");
  ck_assert_msg(strcmp(ptr, "!?123a") == 0, "FAILURE!");
  free(ptr);
}
END_TEST

START_TEST(S21_INSERT) {
  char *ptr = s21_insert("ABC", "xyz", 0);
  ck_assert_msg(strcmp(ptr, "xyzABC") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_insert("ABC", "xyz", 1);
  ck_assert_msg(strcmp(ptr, "AxyzBC") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_insert("ABC", "xyz", 2);
  ck_assert_msg(strcmp(ptr, "ABxyzC") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_insert("ABC", "xyz", 3);
  ck_assert_msg(strcmp(ptr, "ABCxyz") == 0, "FAILURE!");
  free(ptr);

  ck_assert_msg(s21_insert("AB", "xyz", 3) == NULL, "FAILURE!");
}
END_TEST

START_TEST(S21_TRIM) {
  char *ptr = s21_trim("abcdef", "a");
  ck_assert_msg(strcmp(ptr, "bcdef") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_trim("abacdef", "afb");
  ck_assert_msg(strcmp(ptr, "cde") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_trim("*abcdba*", "ab");
  ck_assert_msg(strcmp(ptr, "*abcdba*") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_trim("abc", "p");
  ck_assert_msg(strcmp(ptr, "abc") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_trim("aaababaaa", "a");
  ck_assert_msg(strcmp(ptr, "bab") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_trim("aaababaaa", "ba");
  ck_assert_msg(strcmp(ptr, "") == 0, "FAILURE!");
  free(ptr);

  ptr = s21_trim("    aaababaaa ", "");
  ck_assert_msg(strcmp(ptr, "aaababaaa") == 0, "FAILURE!");
  free(ptr);
}
END_TEST

Suite *string_suite() {
  Suite *s = suite_create("TESTING - s21_string");

  TCase *tc_core = tcase_create("s21_string_case");
  tcase_add_test(tc_core, S21_MEMCHR);
  tcase_add_test(tc_core, S21_MEMCMP);
  tcase_add_test(tc_core, S21_MEMCPY);
  tcase_add_test(tc_core, S21_MEMSET);
  tcase_add_test(tc_core, S21_STRNCAT);
  tcase_add_test(tc_core, S21_STRCHR);
  tcase_add_test(tc_core, S21_STRNCMP);
  tcase_add_test(tc_core, S21_STRNCPY);
  tcase_add_test(tc_core, S21_STRCSPN);
  tcase_add_test(tc_core, S21_STRERROR);
  tcase_add_test(tc_core, S21_STRLEN);
  tcase_add_test(tc_core, S21_STRPBRK);
  tcase_add_test(tc_core, S21_STRRCHR);
  tcase_add_test(tc_core, S21_STRSTR);
  tcase_add_test(tc_core, S21_STRTOK);
  tcase_add_test(tc_core, S21_SPRINTF);
  tcase_add_test(tc_core, S21_SSCANF);
  tcase_add_test(tc_core, S21_TO_UPPER);
  tcase_add_test(tc_core, S21_TO_LOWER);
  tcase_add_test(tc_core, S21_INSERT);
  tcase_add_test(tc_core, S21_TRIM);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  Suite *s = string_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed ? 1 : 0;
}
