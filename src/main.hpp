#pragma once

#include <boost/multiprecision/gmp.hpp>
#include <cstdint>

// high-precision integer type
using BigInt = boost::multiprecision::mpz_int;

// 2×2 matrix of BigInt
struct Mat {
  BigInt a, b, c, d;
};

// multiply two 2×2 matrices
Mat mat_mul(const Mat &x, const Mat &y);

// fast exponentiation by squaring of a 2×2 matrix
Mat mat_pow(Mat base, uint64_t exp);

// compute the n-th Fibonacci via matrix exponentiation
BigInt fib(uint64_t n);
