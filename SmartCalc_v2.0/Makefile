MODEL = polish_calc
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror --coverage
TESTFLAGS = -lgtest -lgtest_main -pthread
GCOV_FLAG = --coverage
UNAME := $(shell uname)

DIR_VIEW = ./view/
DIR_MODEL = ./model/
DIR_TESTS = ./tests/
DIR_OBJ = ./obj/
DIR_BUILD_TESTS = ./build_tests/
DIR_BUILD = ./build/
LIB_NAME = $(DIR_BUILD)$(MODEL).a
DIR_REPORT = ./report/
DIR_DIST = SmartCalc_v2.0

SRC = $(wildcard $(DIR_MODEL)*.cc)
OBJ = $(patsubst $(DIR_MODEL)%.cc, $(DIR_OBJ)%.o, $(SRC))
TEST_SRC = $(wildcard $(DIR_TESTS)*.cc)
TEST_OBJ = $(patsubst $(DIR_TESTS)%.cc, $(DIR_OBJ)%.o, $(TEST_SRC))
TEST_EXECUTABLE = $(DIR_BUILD_TESTS)$(MODEL)_test

ifeq ($(UNAME), Linux)
	OPEN_CMD = xdg-open
	QTFLAGS = CONFIG+=qtquickcompiler
endif
ifeq ($(UNAME), Darwin)
	OPEN_CMD = open
	LCOV_FLAG = --ignore-errors inconsistent
	QTFLAGS = -spec macx-clang CONFIG+=qtquickcompiler
endif

all: dir $(MODEL).a test

$(MODEL).a: dir $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)

$(DIR_OBJ)%.o: $(DIR_MODEL)%.cc | dir
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR_OBJ)%.o: $(DIR_TESTS)%.cc | dir
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(TEST_EXECUTABLE): $(TEST_OBJ) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(GCOV_FLAG) $(TESTFLAGS) $^ -o $@

test: $(TEST_EXECUTABLE)
	$(TEST_EXECUTABLE)

install: uninstall
	@mkdir -p $(DIR_BUILD)
	cd $(DIR_BUILD) && qmake ../calculator.pro $(QTFLAGS) && /usr/bin/make -j8
	cd $(DIR_BUILD) && rm -rf Makefile *.h *.o *.cpp
	open $(DIR_BUILD)

uninstall:
	rm -rf $(DIR_BUILD)

dvi:
	doxygen config_file
	open documentarion/html/index.html


gcov_report:
	lcov -c -d ./obj/ -o ./build_tests/test.info --ignore-errors inconsistent --ignore-errors mismatch
	lcov --remove ./build_tests/test.info '/Library/Developer/CommandLineTools/*' -o ./build_tests/test_filtered.info
	lcov --extract ./build_tests/test.info '/Users/erosrolf/CPP3_SmartCalc_v2.0-1/src/model/*' -o ./build_tests/test.info
	genhtml ./build_tests/test.info -o $(DIR_REPORT)
	$(OPEN_CMD) report/index.html
	rm -rf *.gcda *.gcno *.info *.dSYM

dir:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(DIR_BUILD)
	@mkdir -p $(DIR_BUILD_TESTS)

dist: clean
	mkdir -p $(DIR_DIST)
	cp -R * $(DIR_DIST)
	tar cvzf $(DIR_DIST).tgz $(DIR_DIST)
	rm -rf $(DIR_DIST)


style_check:
	cp ../materials/linters/.clang-format ../src/
	@find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -n {}'
	@find $(DIR_TESTS) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -n {}'
	@find $(DIR_MODEL) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -n {}'
	@find $(DIR_VIEW) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Checking {}" && clang-format -n {}'
	rm -rf .clang-format

style_repair: clean
	cp ../materials/linters/.clang-format ../src/
	@find . -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Formatting {}" && clang-format -i {}'
	@find $(DIR_TESTS) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Formatting {}" && clang-format -i {}'
	@find $(DIR_MODEL) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Formatting {}" && clang-format -i {}'
	@find $(DIR_VIEW) -type f -name '*.cc' -or -name '*.h' | xargs -I {} sh -c 'echo "Formatting {}" && clang-format -i {}'
	rm -rf .clang-format

clean:
	rm -rf $(DIR_BUILD) $(DIR_OBJ) $(DIR_BUILD_TESTS) $(DIR_REPORT) ./documentarion $(DIR_DIST).tgz $(DIR_DIST)
