.PHONY: all run test test-asan benchmark clean

CXX = g++
CXXFLAGS = -std=c++17 -Wall -I include
GTEST = -isystem googletest/googletest/include -I googletest/googletest -pthread googletest/googletest/src/gtest-all.cc

all: lab
lab: src/main.cpp
	$(CXX) $(CXXFLAGS) $< -o lab

run: lab
	./lab

test: tests/run_tests.cpp tests/test.cpp
	$(CXX) $(CXXFLAGS) $(GTEST) $^ -o run_tests
	./run_tests

test-asan: tests/run_tests.cpp tests/test.cpp
	clang++ $(CXXFLAGS) -fsanitize=address,undefined -g -O1 -fno-omit-frame-pointer $(GTEST) $^ -o run_tests_asan
	./run_tests_asan

benchmark: tests/benchmark.cpp
	$(CXX) $(CXXFLAGS) -O2 $< -o run_benchmark
	./run_benchmark

clean:
	rm -f lab run_tests run_tests_asan run_benchmark benchmark_results.csv