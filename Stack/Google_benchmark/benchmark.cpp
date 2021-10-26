#include <benchmark/benchmark.h>
#include "../Bool_Stack.h"

static void CustomArguments(benchmark::internal::Benchmark* b) {
    for (int i = 110; i <= 205; ++i)
        b->Arg(i);
}

static void BM_fillStack(benchmark::State& state){
    double factor = double(state.range(0)) / 100;
    for (auto _ : state) {
        Stack<int> stack;
        stack.changeFactor(factor);
        for (int i = 0; i < 1e7; ++i) {
            stack.push(666);
        }
        benchmark::DoNotOptimize(stack);
    }
}
BENCHMARK(BM_fillStack) ->Apply(CustomArguments) ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
