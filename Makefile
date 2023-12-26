CC = g++
CC_FLAGS = --std=C++17 -Wall -Werror -Wextra -g
GCOV_FLAGS = -lgtest --coverage -lstdc++
SRC = test.cc my_matrix_oop.cc

all : clean my_matrix_oop.a test

test: clean my_matrix_oop.a
	$(CC) $(CFLAGS) test.cc -L. my_matrix_oop.a -o test -lgtest
	./test

my_matrix_oop.a: my_matrix_oop.o
	ar rcs my_matrix_oop.a *.o
	ranlib my_matrix_oop.a

my_matrix_oop.o:
	$(CC) $(CFLAGS) -c my_matrix_oop.cc

gcov_report: clean
	$(CC) $(SRC) -o test_check $(GCOV_FLAGS)
	./test_check
	lcov --directory . --capture --ignore-errors mismatch --output-file test_check.info
	lcov --remove test_check.info "/usr/*" --output-file test_check.info
	genhtml -o report test_check.info 
	open report/index.html

clean:
	rm -rf *.gcno *.gcda *.o *.a *.info my_matrix_oop report test test_check test.log

clang:
	clang-format -style="{BasedOnStyle: Google}" -i *.cc *.h

val: clean my_matrix.a
	$(CC) $(CFLAGS) test.cc -L. my_matrix.a -o test -lgtest
	valgrind --tool=memcheck --leak-check=yes ./test

#valgrind --leak-check=full --show-leak-kinds=all

# valgrind --tool=memcheck --leak-check=yes