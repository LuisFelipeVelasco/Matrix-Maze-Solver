CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O0
LDFLAGS = -lcurl
TARGET = main
SRCS = $(wildcard *.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LDFLAGS)

run: all
	./$(TARGET)

debug: all
	gdb ./$(TARGET)

gdbserver: all
	@echo "Iniciando gdbserver en puerto :2345"
	gdbserver :2345 ./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_BIN) *.o

# GoogleTest build
TEST_BIN = test_runner
TEST_SRC = tests/test_main.cpp
TEST_DEPS = Visual.cpp Avatar.cpp Board.cpp 

google-test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(TEST_DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRC) $(TEST_DEPS) -lgtest -lgtest_main $(LDFLAGS)