#include <benchmark/benchmark.h>

const int NUM_OF_LINE = 1e3;
const int SIZE_OF_LINE = 1e4;

static void BM_SUM_WITH_LOCALITY_EX1(benchmark::State& state){
	int** matrix = (int**) calloc(NUM_OF_LINE, sizeof (int*));
	for (int i = 0; i < NUM_OF_LINE; ++i) {
		matrix[i] = (int*) calloc(SIZE_OF_LINE, sizeof (int*));
	}
	long long sum = 0;

	for (auto _: state) {
		for (int i = 0; i < NUM_OF_LINE; ++i) {
			for (int j = 0; j < SIZE_OF_LINE; ++j) {
				sum += matrix[i][j];
			}
		}
		sum = 0;

	}

	for (int i = 0; i < NUM_OF_LINE; ++i) {
		free(matrix[i]);
	}
	free(matrix);
}
BENCHMARK(BM_SUM_WITH_LOCALITY_EX1)-> Unit(benchmark::kMillisecond);

static void BM_SUM_WITHOUT_LOCALITY_EX1(benchmark::State& state){
	int** matrix = (int**) calloc(NUM_OF_LINE, sizeof (int*));
	for (int i = 0; i < NUM_OF_LINE; ++i) {
		matrix[i] = (int*) calloc(SIZE_OF_LINE, sizeof (int*));
	}

	long long sum = 0;

	for (auto _: state) {
		for (int j = 0; j < SIZE_OF_LINE; ++j) {
			for (int i = 0; i < NUM_OF_LINE; ++i) {
				sum += matrix[i][j];
			}
		}
	}

	for (int i = 0; i < NUM_OF_LINE; ++i) {
		free(matrix[i]);
	}
	free(matrix);
}
BENCHMARK(BM_SUM_WITHOUT_LOCALITY_EX1)-> Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();