# gbenchmark_example

Google benchmarking framework can be used with Google Testing/Mocking framework together to do micro benchmarking for C++ programs.

# Installation

To install Google benchmarking library, please execute the following commands

> $ git clone https://github.com/google/benchmark.git
> $ cd benchmark
> $ git clone https://github.com/google/googletest.git benchmark/googletest
> $ mkdir build && cd build
> $ cmake ../benchmark
> $ make
> $ make install

Note that the installation of the benchmarking library requires the source code of the Google testing framework.

# Add a benchmark into CMakeLists.txt

It's similar to add a test into the CMake-based project. 

> add_executable(int_to_string_benchmark "bench/bench_int_to_string.cpp" "src/conversion.cpp" "src/conversion.h")
> target_link_libraries(int_to_string_benchmark -lbenchmark -pthread)
> add_test(NAME int_to_string_benchmark COMMAND int_to_string_benchmark)

First, add_executable() builds an executable called "int_to_string_benchmark" from the source files containing functions you want to benchmark (conversion.cpp/.h) and the source files containing code driving the benchmarking (bench_int_to_string.cpp).

Secondly, target_link_libraries() links the benchmark library (-lbenchmark) and POSIX thread library (-pthread).

Lastly, add_test() registers the benchmark as a new test because benchmarking tasks, like a testing task, are driven by CTest.

# A simple example

Converstion.cpp/.h defines a function IntToString() converting an integer to its string representation.

> std::string IntToString(int v);

Bench_int_to_string.cpp contains the code registering and driving the benchmark.

> #include <string>
> #include <benchmark/benchmark.h>
>
> #include "conversion.h"
>
> static void BM_IntToString(benchmark::State& state) {
>   std::string x;
>
>   for (auto _ : state) {
>      benchmark::DoNotOptimize(
>       x = gbenchmarkexample::IntToString(static_cast<int>(state.range(0)))
>      );
>   }
> }
>
> BENCHMARK(BM_IntToString)->Arg(7463);
> BENCHMARK(BM_IntToString)->Arg(87653433);
>
> BENCHMARK_MAIN();
  
  
