#include "main.hpp"
#include <chrono>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;

Mat mat_mul(const Mat &x, const Mat &y) {
  return Mat{x.a * y.a + x.b * y.c, x.a * y.b + x.b * y.d,
             x.c * y.a + x.d * y.c, x.c * y.b + x.d * y.d};
}

Mat mat_pow(Mat base, uint64_t exp) {
  Mat result{1, 0, 0, 1};
  while (exp) {
    if (exp & 1)
      result = mat_mul(result, base);
    base = mat_mul(base, base);
    exp >>= 1;
  }
  return result;
}

BigInt fib(uint64_t n) {
  Mat M{1, 1, 1, 0};
  return mat_pow(M, n).b;
}

int main() {
  const double TIME_LIMIT = 2.0;
  uint64_t low = 0, high = 1, best = 0;
  double elapsed;

  // Exponential bracket
  while (true) {
    auto start = Clock::now();
    fib(high);
    elapsed = std::chrono::duration<double>(Clock::now() - start).count();
    if (elapsed > TIME_LIMIT)
      break;
    best = high;
    low = high;
    high <<= 1;
  }

  // Binary search
  while (low < high - 1) {
    uint64_t mid = low + (high - low) / 2;
    auto start = Clock::now();
    fib(mid);
    elapsed = std::chrono::duration<double>(Clock::now() - start).count();
    if (elapsed <= TIME_LIMIT) {
      best = mid;
      low = mid;
    } else {
      high = mid;
    }
  }

  BigInt F = fib(best);
  std::string s = F.convert_to<std::string>();

  std::cout << "Maximum n in " << TIME_LIMIT << "s: " << best << "\n"
            << "Fib(" << best << ") has " << s.size() << " digits\n";
  return 0;
}
