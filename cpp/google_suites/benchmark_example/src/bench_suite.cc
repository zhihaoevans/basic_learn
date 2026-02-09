#include <benchmark/benchmark.h>

#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

static void BM_VectorPushBack(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(state.range(0));
    for (int i = 0; i < state.range(0); ++i) v.push_back(i);
    benchmark::DoNotOptimize(v);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_VectorPushBack)->Range(8, 8 << 12)->Complexity();

static void BM_StringConcat(benchmark::State& state) {
  std::string s;
  s.reserve(static_cast<std::size_t>(state.range(0)));
  for (auto _ : state) {
    s.clear();
    for (int i = 0; i < state.range(0); ++i) s += 'x';
    benchmark::DoNotOptimize(s);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StringConcat)->Range(8, 8 << 12)->Complexity();

static void BM_StringAppend(benchmark::State& state) {
  std::string s;
  s.reserve(static_cast<std::size_t>(state.range(0)));
  for (auto _ : state) {
    s.clear();
    for (int i = 0; i < state.range(0); ++i) s.append(1, 'x');
    benchmark::DoNotOptimize(s);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StringAppend)->Range(8, 8 << 12)->Complexity();

static void BM_ManualTimer(benchmark::State& state) {
  for (auto _ : state) {
    auto start = std::chrono::steady_clock::now();
    volatile double x = 0.0;
    for (int i = 0; i < state.range(0); ++i) x += std::sqrt(static_cast<double>(i + 1));
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    state.SetIterationTime(elapsed.count());
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(BM_ManualTimer)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 20)
    ->UseManualTime();

static void BM_SortStd(benchmark::State& state) {
  std::vector<int> v(static_cast<std::size_t>(state.range(0)));
  std::mt19937 rng(42);
  for (auto _ : state) {
    std::generate(v.begin(), v.end(), [&] { return static_cast<int>(rng()); });
    std::sort(v.begin(), v.end());
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(BM_SortStd)->Range(1 << 10, 1 << 18);

static void insertion_sort(std::vector<int>& v) {
  for (std::size_t i = 1; i < v.size(); ++i) {
    int key = v[i];
    std::size_t j = i;
    while (j > 0 && v[j - 1] > key) {
      v[j] = v[j - 1];
      --j;
    }
    v[j] = key;
  }
}

static void BM_SortInsertion(benchmark::State& state) {
  std::vector<int> v(static_cast<std::size_t>(state.range(0)));
  std::mt19937 rng(42);
  for (auto _ : state) {
    std::generate(v.begin(), v.end(), [&] { return static_cast<int>(rng()); });
    insertion_sort(v);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(BM_SortInsertion)->Range(1 << 10, 1 << 14);

BENCHMARK_MAIN();
