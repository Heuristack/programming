#include <benchmark/benchmark.h>

static void StringCreationMove(benchmark::State & state) {
    for (auto _ : state) {
        std::string x = "move is faster than copy when string is longer";
        benchmark::DoNotOptimize(x);
        std::string created_string_move(std::move(x));
        benchmark::DoNotOptimize(created_string_move);
    }
}
BENCHMARK(StringCreationMove);

static void StringCreationCopy(benchmark::State & state) {
    for (auto _ : state) {
        std::string x = "move is faster than copy when string is longer";
        benchmark::DoNotOptimize(x);
        std::string created_string_copy(x);
        benchmark::DoNotOptimize(created_string_copy);
    }
}
BENCHMARK(StringCreationCopy);

BENCHMARK_MAIN();
