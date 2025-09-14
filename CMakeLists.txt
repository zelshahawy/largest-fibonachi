cmake_minimum_required(VERSION 3.20)
project(fib_limit LANGUAGES CXX)

# Find GMP via pkg-config (brings include + link flags)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GMP REQUIRED IMPORTED_TARGET gmp)

add_executable(fib_limit src/main.cpp)
target_compile_features(fib_limit PRIVATE cxx_std_20)

# Boost.Multiprecision is header-only; we just need Boost headers.
target_include_directories(fib_limit PRIVATE $ENV{CONDA_PREFIX}/include)

# Link against GMP only
target_link_libraries(fib_limit PRIVATE PkgConfig::GMP)

