#include <benchmark/benchmark.h>
#include "../Bool_Stack.h"

void fillStack(int factor){
    Stack<int> stack;
    for (int i = 0; i < 1e6; ++i) {
        stack.push(rand());
    }
}


static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state)
        std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();