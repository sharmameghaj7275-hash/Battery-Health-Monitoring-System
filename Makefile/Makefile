CC=gcc
CXX=g++
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -Iinclude
CXXFLAGS=-std=c++17 -Wall -Wextra -Iinclude
SRC=src/main.c src/battery.c
.PHONY: all run test clean
all: battery_monitor
battery_monitor: $(SRC) include/battery.h
	$(CC) $(CFLAGS) $(SRC) -o $@
run: all
	./battery_monitor
test: src/battery.c include/battery.h tests/test_battery.cpp
	$(CC) $(CFLAGS) -c src/battery.c -o battery_test.o
	$(CXX) $(CXXFLAGS) tests/test_battery.cpp battery_test.o -lgtest -lgtest_main -pthread -o test_runner
	./test_runner
clean:
	rm -f battery_monitor test_runner battery_test.o
