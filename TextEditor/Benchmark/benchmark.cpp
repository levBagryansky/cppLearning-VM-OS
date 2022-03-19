#include <benchmark/benchmark.h>
#include "TextEditor.h"

const std::string path_to_load = "../../Texts/lord_of_rings.txt";
const std::string path_to_edit = "../../Texts/Hamlet.txt";

static void CustomThreads(benchmark::internal::Benchmark* b) {
    for (int i = 2; i <= 1e3; i *= 1.5) {
        b->Arg(i);
    }
}

static void BM_EditHamlet(benchmark::State& state) {
    int n_threads = int(state.range(0));
    TextEditor te;
    te.Upload(path_to_load);
    for (auto _ : state) {
        te.EditText( path_to_edit, "correct.txt", n_threads);
        benchmark::DoNotOptimize(te);
    }
}
BENCHMARK(BM_EditHamlet)->Apply(CustomThreads)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
