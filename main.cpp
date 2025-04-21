#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

using boost::multiprecision::cpp_int;
using Clock = std::chrono::high_resolution_clock;

struct Mat {
  cpp_int a, b, c, d;
};

Mat mat_mul(const Mat &x, const Mat &y) {
  // Launch two async tasks for the two “heavy” products
  auto f1 =
      std::async(std::launch::async, [&]() { return x.a * y.a + x.b * y.c; });
  auto f4 =
      std::async(std::launch::async, [&]() { return x.c * y.b + x.d * y.d; });
  // Compute the other two on this thread
  cpp_int m2 = x.a * y.b + x.b * y.d;
  cpp_int m3 = x.c * y.a + x.d * y.c;
  // Gather results
  Mat R;
  R.a = f1.get();
  R.b = std::move(m2);
  R.c = std::move(m3);
  R.d = f4.get();
  return R;
}

Mat mat_pow(Mat base, uint64_t e) {
  Mat result{1, 0, 0, 1}; // identity
  while (e) {
    if (e & 1)
      result = mat_mul(result, base);
    base = mat_mul(base, base);
    e >>= 1;
  }
  return result;
}

cpp_int fib_via_mat(uint64_t n) {
  Mat M{1, 1, 1, 0};
  Mat R = mat_pow(M, n);
  return R.b; // F_n
}

int main() {
  const double TIME_LIMIT = 2.0; // seconds
  double elapsed;
  uint64_t low = 0, high = 1, best = 0;
  while (true) {
    auto t0 = Clock::now();
    fib_via_mat(high);
    elapsed = std::chrono::duration<double>(Clock::now() - t0).count();
    if (elapsed > TIME_LIMIT)
      break;
    best = high;
    low = high;
    high <<= 1; // double
  }
  while (low < high - 1) {
    uint64_t mid = low + (high - low) / 2;
    auto t0 = Clock::now();
    fib_via_mat(mid);
    elapsed = std::chrono::duration<double>(Clock::now() - t0).count();
    if (elapsed <= TIME_LIMIT) {
      best = mid;
      low = mid;
    } else {
      high = mid;
    }
  }
  std::cout << "Maximum n in " << TIME_LIMIT << "s: " << best << "\n";
  std::cout << "Fib(" << best << ") has "
            << fib_via_mat(best).convert_to<std::string>().size()
            << " digits\n";
  return 0;
}
