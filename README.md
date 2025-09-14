# largest-fibonachi

CPP program that uses the boost library and matrix multiplication to get the highest fibonachi number where each fibonachi
operation takes a maximum of 2 seconds time.

It uses threads for the clock, and prints what the index of the fibonachi number, and the number of digits.
Compiled using clang and into a program called `fib_limit`

Current Score:

On average I have
- Maximum n: 65246723
- Fib(65246723) has 13635759 digits. In words, 13 million, 635 thousand, 759 digits.

# How to run on your own machine.

Pixi is used to make that easy. Simply, run the following

- pixi run configure
- pixi run build
- pixi run run

You obviously need to have pixi installed. This is known to work on all platforms
with pixi version 0.46.
