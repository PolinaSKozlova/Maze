#all, install, uninstall, clean, dvi, dist, tests, gcov_report
CC = g++
CC_FLAGS = -Wall -Wextra -Werror -std=c++17 #-pedantic-errors
TEST_FLAGS = -lgtest -pthread
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage --coverage
SANITIZER_FLAGS = #-fsanitize=address
SRCS=$(wildcard maze*.cc,*/maze*.cc)
OBJ_FILES=$(patsubst %.cc,%.o,$(SRCS))
REPORT_DIR = report
MAZE_CREATOR = MAZE/maze_creator/maze_ideal.cc
MAZE_READER = MAZE/maze_reader/maze_ordinary.cc
MAZE_SOLUTION = MAZE/maze_solution/maze_solution.cc
CAVE_GENERATOR = MAZE/cave_generator/cave*.cc


all: install

install:
	cmake -S ./MAZE -B build -G "Unix Makefiles"
	make -C build
	cd ./build && rm -rf CMakeFiles MAZE_autogen cmake_install.cmake CMakeCache.txt Makefile
	open build

uninstall:
	rm -rf build

clean:
	rm -rf *.o *.gcno *.gcda *.info *.a $(REPORT_DIR) m_tests run *.dSYM MAZE.tar.gz MAZE/CMakeLists.txt.user

dvi:
	makeinfo -o report --html --no-warn --no-validate --force doc.texi
	open report/index.html

dist:
	tar -czf MazeAPP.tar.gz Makefile MAZE maze* doc.texi
	open .

tests: 
	clear
	$(CC) $(CC_FLAGS) $(MAZE_CREATOR) $(MAZE_READER) $(MAZE_SOLUTION) $(CAVE_GENERATOR) maze_tests/*_tests.cc -o m_tests $(TEST_FLAGS)
	./m_tests

gcov_report:
	clear
	$(CC) $(CC_FLAGS) $(COVERAGE_FLAGS) $(MAZE_CREATOR) $(MAZE_READER) $(MAZE_SOLUTION) $(CAVE_GENERATOR) maze_tests/*_tests.cc -o m_tests $(TEST_FLAGS)
	./m_tests
	lcov -t "$@" -o $@.info -c -d . --no-external  --ignore-errors mismatch --quiet
	lcov -r $@.info "*include*" -o $@.info  --ignore-errors unused --quiet
	genhtml -o ./$(REPORT_DIR) $@.info
	open ./report/index.html

%.o:%.cc
	$(CC) -c $(FLAGS) $< -o $@ -I .

valgrind: tests
	valgrind --leak-check=full \
        	 --show-leak-kinds=all \
         	 --track-origins=yes \
         	 --verbose \
			 ./m_tests

leaks: run
	CK_FORK=no leaks -atExit -- ./run 

.PHONY:
	all, clean, tests, gcov_report, install, uninstall, dvi, dist

clang:
	clang-format -i --style=Google MAZE/**/*.cc MAZE/**/*.h
	clang-format -n --style=Google MAZE/**/*.cc MAZE/**/*.h

cppcheck:
	cppcheck --enable=all --language=c++ --std=c++17 --suppress=missingIncludeSystem MAZE/maze*/*.cc MAZE/maze*/*.h
