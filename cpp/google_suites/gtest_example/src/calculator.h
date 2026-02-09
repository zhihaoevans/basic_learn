#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

class Calculator {
 public:
  int Add(int a, int b) const;
  int Sub(int a, int b) const;
  long long Mul(long long a, long long b) const;
  double Div(double a, double b) const;
  double Sqrt(double x) const;
  std::size_t Factorial(std::size_t n) const;
  long long SumVector(const std::vector<int>& v) const;
  bool IsEven(int x) const;
  bool IsPrime(int x) const;
  std::string Repeat(const std::string& s, int n) const;
};
