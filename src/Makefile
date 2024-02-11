CC = g++
CFLAGS = -std=c++17
SOURCE_BACKEND = $(wildcard ./backend/*.cc)
SOURCE_FRONTEND = $(wildcard ./frontend/*.cc)
HEADERS_BACKEND = $(wildcard ./backend/*.h)
HEADERS_FRONTEND = $(wildcard ./frontend/*.h)
MATRIX_FILES = $(wildcard ./backend/s21_matrix/*.cc ./backend/s21_matrix/*.h)
TESTS = $(wildcard test_3dviewer.cc)
OBJECTS = $(patsubst %.cc,%.o, ${SOURCE})
QMAKE_PATH = /home/jexwerqwez/Qt5.12.12/5.12.12/gcc_64/bin/qmake
BUILD_SRC = ./build
CFLAGS_TEST =`pkg-config --cflags --libs check`
CFLAGS_GCOV =-fprofile-arcs -ftest-coverage
DIR = report/tests

_UNAME_ := $(shell uname -s)

ifeq ($(_UNAME_), Linux)
	OPEN_CMD = xdg-open
	BREW = .
	BROWSER_APP = firefox 
endif

ifeq ($(_UNAME_), Darwin) # MacOS
	OPEN_CMD = open
	BREW = ${HOME}/homebrew
	BROWSER_APP = /Applications/Google\ Chrome.app
endif


PATH := $(PATH):$(BREW)/bin
GCOV = --coverage
PROJECT_NAME := 3DViewer

all: clean style ${PROJECT_NAME}.a tests gcov_report

tests: $(MATRIX_FILES) $(TESTS) ${SOURCE_BACKEND} ${HEADERS_BACKEND}
	$(info                                         )
	$(info ----------------------------------------)
	$(info Build tests                             )
	$(info ----------------------------------------)
	$(CC) $^ -lgtest -o $@
	./$@

pro:
	mkdir -p ${BUILD_SRC}
	cd ${BUILD_SRC} && ${QMAKE_PATH} ../frontend/3DViewer.pro
	cd ${BUILD_SRC} && make

install: clean pro
	$(info                                         )
	$(info ----------------------------------------)
	$(info Install the project                     )
	$(info ----------------------------------------)
	cd ${BUILD_SRC} && ./3DViewer

uninstall:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Uninstall the project                   )
	$(info ----------------------------------------)
	make clean
	-rm -rf ../${BUILD_SRC}


gcov_report: clean
	mkdir report
	@$(CC) $(CFLAGS) $(CFLAGS_TEST) $(CFLAGS_GCOV) $(HEADERS_BACKEND) $(HEADERS_FRONTEND) $(SOURCE_BACKEND) $(SOURCE_FRONTEND) $(TESTS) -o $(DIR) $(ADD_LIB)
	@$(DIR)
	@gcov tests
	@lcov --capture --directory report --output-file report/main_coverage.info
	@genhtml report/main_coverage.info --output-directory report/lcov_report/index.html

ifeq ($(_UNAME_), Darwin) # MacOS
	open $(BROWSER_APP)./ report/src/index.html
else
	$(BROWSER_APP)./ report/src/index.html
endif

lcov:
ifeq ("", "$(shell PATH=$(PATH) which lcov)")
	$(error Need to install lcov)
endif

dvi:
	$(info                                         )
	$(info ----------------------------------------)
	$(info Generate DVI file                       )
	$(info ----------------------------------------)
	open dvi.txt

dist: clean pro
	$(info                                         )
	$(info ----------------------------------------)
	$(info Create a distribution package           )
	$(info ----------------------------------------)
	tar cvzf Archive_3DViewer_v1.0.tgz ${BUILD_SRC}
	-rm -rf ${BUILD_SRC}

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	# -rm -rf qMakefile
	-rm -rf ${BUILD_SRC}
	-rm -rf Archive_3DViewer_v1.0.tgz
	-rm -rf tests