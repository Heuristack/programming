#include <benchmark/benchmark.h>

static void StringCreation(benchmark::State & state) {
    for (auto _ : state) {
        std::string created_string("hello");
        benchmark::DoNotOptimize(created_string);
    }
}
BENCHMARK(StringCreation);

static void StringCreationMove(benchmark::State & state) {
    std::string x = "hello";
    for (auto _ : state) {
        std::string created_string_move(std::move(x));
        benchmark::DoNotOptimize(created_string_move);
    }
}
BENCHMARK(StringCreationMove);

static void StringCreationCopy(benchmark::State & state) {
    std::string x = "hello";
    for (auto _ : state) {
        std::string created_string_copy(x);
        benchmark::DoNotOptimize(created_string_copy);
    }
}
BENCHMARK(StringCreationCopy);

static void StringCreationCopyByChar(benchmark::State & state) {
    char const * x = "hello";
    for (auto _ : state) {
        std::string created_string_by_char(x);
        benchmark::DoNotOptimize(created_string_by_char);
    }
}
BENCHMARK(StringCreationCopyByChar);

BENCHMARK_MAIN();
