CC = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra -pedantic

OBJ = $(FUNC:.c=.o)
FUNC = $(wildcard *.c)

all: string.a

my_string.a: $(OBJ)
	ar rcs my_string.a $^ 

clean:
	rm -f *.o *.a *.info
	rm -f ./tests/TEST*
	rm -rf ./tests/coverage_report/
.c.o:
	$(CC) $(FLAGS)  -c $< -o $@	

rebuild: clean all

clang:
	clang-format -i *.c *.h ./tests/test.c

test: my_string.a
	$(CC) $(FLAGS) ./tests/test.c my_string.a -o ./tests/TEST -lcheck -lm -lpthread -lrt -lsubunit
	./tests/TEST

gcov_report: my_string.a
	$(CC) --coverage $(FLAGS) ./tests/test.c my_string.a -o ./tests/TEST -lcheck -lm -lpthread -lrt -lsubunit
	./tests/TEST
	lcov -t "bombardiro_crocodilo_meow" -o bombardiro_crocodilo_meow.info -c -d .
	genhtml -o ./tests/coverage_report bombardiro_crocodilo_meow.info
