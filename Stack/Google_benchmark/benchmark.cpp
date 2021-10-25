#include <benchmark/benchmark.h>
#include "../Bool_Stack.h"

void fillStack(long double factor){
    Stack<int> stack;
    for (int i = 0; i < 1e6; ++i) {
        stack.push(rand());
    }
}

static void CustomArguments(benchmark::internal::Benchmark* b) {
    for (int i = 150; i <= 250; ++i)
        b->Arg({i});
}

static void BM_fillStack(benchmark::State& state){
    double factor = double(state.range(0)) / 100;
    for (auto _ : state) {
        Stack<int> stack;
        for (int i = 0; i < 1e6; ++i) {
            stack.pushWithFactor(rand(), factor);
        }
    }
}
BENCHMARK(BM_fillStack) ->Apply(CustomArguments) -> Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
