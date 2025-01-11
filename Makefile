CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage

SOURCES=$(wildcard s21_*.c)
OBJS=$(SOURCES:.c=.o)

%.o : %.c
	$(CC) -c $<

all : s21_string.a

s21_string.a : $(OBJS) s21_string.h
	ar rsc s21_string.a $(OBJS)

test : s21_string.a tests.c
	$(CC) $(FLAGS) tests.c s21_string.a -o test.out -lcheck -lm
	./test.out

gcov_report : tests.c
	$(CC) tests.c $(SOURCES) -o test.out -lcheck -lm $(GCOVFLAGS)
	./test.out
#	gcovr --html report.html
	lcov -t "s21_string_test" -o rep.info -c -d .
	genhtml -o report rep.info

clean :
	rm -r ./report *.o *.a *.out *.gc* *.info

rebuild : clean all
