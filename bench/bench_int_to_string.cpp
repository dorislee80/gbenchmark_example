#include <string>
#include <benchmark/benchmark.h>

#include "conversion.h"


static void BM_IntToString(benchmark::State& state) {
  std::string x;

  for (auto _ : state) {
    benchmark::DoNotOptimize(
      x = gbenchmarkexample::IntToString(static_cast<int>(state.range(0)))
    );
  }
}


BENCHMARK(BM_IntToString)->Arg(7463);
BENCHMARK(BM_IntToString)->Arg(87653433);


BENCHMARK_MAIN();