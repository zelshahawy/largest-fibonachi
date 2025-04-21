# Makefile for macOS + Homebrew Boost+GMP

CXX      := clang++
# pick up Boost headers, and (via --prefix) GMP headers too
CXXFLAGS := -std=c++17 -O3 -pthread \
             -I$(shell brew --prefix boost)/include \
             -I$(shell brew --prefix gmp)/include

# library search paths + the actual libs
LDFLAGS  := -L$(shell brew --prefix boost)/lib \
             -L$(shell brew --prefix gmp)/lib \
             -lgmpxx -lgmp

SRCS     := main.cpp   # ← change to the name of your source file
TARGET   := fib_limit

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

run: all
	@./$(TARGET)

clean:
	rm -f $(TARGET)

