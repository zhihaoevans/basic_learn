#include "calculator.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

int Calculator::Add(int a, int b) const { return a + b; }

int Calculator::Sub(int a, int b) const { return a - b; }

long long Calculator::Mul(long long a, long long b) const { return a * b; }

double Calculator::Div(double a, double b) const {
  if (b == 0.0) {
    std::abort();
  }
  return a / b;
}

double Calculator::Sqrt(double x) const {
  if (x < 0.0) {
    std::abort();
  }
  return std::sqrt(x);
}

std::size_t Calculator::Factorial(std::size_t n) const {
  std::size_t r = 1;
  for (std::size_t i = 2; i <= n; ++i) r *= i;
  return r;
}

long long Calculator::SumVector(const std::vector<int>& v) const {
  long long s = 0;
  for (int x : v) s += x;
  return s;
}

bool Calculator::IsEven(int x) const { return (x % 2) == 0; }

bool Calculator::IsPrime(int x) const {
  if (x <= 1) return false;
  if (x <= 3) return true;
  if ((x % 2) == 0 || (x % 3) == 0) return false;
  for (int i = 5; i * i <= x; i += 6) {
    if ((x % i) == 0 || (x % (i + 2)) == 0) return false;
  }
  return true;
}

std::string Calculator::Repeat(const std::string& s, int n) const {
  if (n < 0) {
    std::abort();
  }
  std::string r;
  r.reserve(s.size() * static_cast<std::size_t>(n));
  for (int i = 0; i < n; ++i) r += s;
  return r;
}
