#include <benchmark/benchmark.h>

const int NUM_OF_LINE = 1e3;
const int SIZE_OF_LINE = 1e4;
const int MATRIX_SIZE = 10e2;

void MatrixMult1(int size, double **A, double **B, double **C);

void MatrixMult2(int size, double **A, double **B, double **C);

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

static void BM_SUM_WITH_LOCALITY_EX2(benchmark::State& state){
	double **matrix_A = (double **) calloc(MATRIX_SIZE, sizeof (double *));
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix_A[i] = (double *) calloc(MATRIX_SIZE, sizeof (double *));
	}
	double **matrix_B = (double **) calloc(MATRIX_SIZE, sizeof (double *));
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix_B[i] = (double *) calloc(MATRIX_SIZE, sizeof (double *));
	}
	double **matrix_C = (double **) calloc(MATRIX_SIZE, sizeof (double *));
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix_C[i] = (double *) calloc(MATRIX_SIZE, sizeof (double *));
	}

	for (auto _: state) {
		MatrixMult2(MATRIX_SIZE, matrix_A, matrix_B, matrix_C);
	}

	for (int i = 0; i < MATRIX_SIZE; ++i) {
		free(matrix_A[i]);
		free(matrix_B[i]);
		free(matrix_C[i]);
	}
	free(matrix_A);
	free(matrix_B);
	free(matrix_C);
}
BENCHMARK(BM_SUM_WITH_LOCALITY_EX2)-> Unit(benchmark::kMillisecond);

static void BM_SUM_WITHOUT_LOCALITY_EX2(benchmark::State& state){
	double **matrix_A = (double **) calloc(MATRIX_SIZE, sizeof (double *));
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix_A[i] = (double *) calloc(MATRIX_SIZE, sizeof (double *));
	}
	double **matrix_B = (double **) calloc(MATRIX_SIZE, sizeof (double *));
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix_B[i] = (double *) calloc(MATRIX_SIZE, sizeof (double *));
	}
	double **matrix_C = (double **) calloc(MATRIX_SIZE, sizeof (double *));
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix_C[i] = (double *) calloc(MATRIX_SIZE, sizeof (double *));
	}

	for (auto _: state) {
		MatrixMult1(MATRIX_SIZE, matrix_A, matrix_B, matrix_C);
	}

	for (int i = 0; i < MATRIX_SIZE; ++i) {
		free(matrix_A[i]);
		free(matrix_B[i]);
		free(matrix_C[i]);
	}
	free(matrix_A);
	free(matrix_B);
	free(matrix_C);
}
BENCHMARK(BM_SUM_WITHOUT_LOCALITY_EX2)-> Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();

void MatrixMult1(int size, double **A, double **B, double **C)
{
	double sum;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			sum = 0.0;
			for (int k = 0; k < size; k++)
				sum += A[i][k]*B[k][j];
			C[i][j] = sum;
		}
}

void MatrixMult2(int size, double **A, double **B, double **C)
{
	double r;

	for (int i = 0; i < size; i++)
		for (int k = 0; k < size; k++) {
			r = A[i][k];
			for (int j = 0; j < size; j++)
				C[i][j] += r*B[k][j];
		}
}
