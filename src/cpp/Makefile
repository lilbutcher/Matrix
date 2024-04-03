CC=g++
CFLAGS= -c -Wall -Werror -Wextra -std=c++17
LDFLAGS=-static
SOURCES=S21Matrix.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=s21_matrix_oop.a

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar rcs	$@	$(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@



clean:
	rm -f $(OBJECTS) $(LIBRARY) unit_tests ./tests/tests.o a.out S21Matrix.h.gch S21Matrix.gcno


test:
	$(CC) --coverage -c S21Matrix.cpp
	$(CC) $(CFLAGS) -o ./tests/tests.o ./tests/tests.cpp
	$(CC) -o unit_tests ./tests/tests.o $(LIBRARY) -lgtest
	./unit_tests

gcov_report:
	gcov $(SOURCES)
	$(CC) -fprofile-arcs -ftest-coverage -o unit_tests $(SOURCES) ./tests/tests.cpp -lgtest
	./unit_tests
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage_report

leaks:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./unit_tests
