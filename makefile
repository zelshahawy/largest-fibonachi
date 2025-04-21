# Makefile for macOS + Homebrew Boost

CXX      := clang++
CXXFLAGS := -std=c++17 -O3 -pthread \
             -I$(shell brew --prefix boost)/include
LDFLAGS  := -L$(shell brew --prefix boost)/lib

SRCS     := main.cpp     # or fib_limit.cpp if you renamed it
TARGET   := fib_limit

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

run: all
	@./$(TARGET)

clean:
	rm -f $(TARGET)

