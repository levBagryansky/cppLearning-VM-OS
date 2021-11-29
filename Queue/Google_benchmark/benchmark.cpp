#include <benchmark/benchmark.h>
#include "QueueOnList-impl.h"
#include "QueueOnStack-impl.h"

const int BIG_NUMBER = 1e6;

static void BM_PushQueueOnStack(benchmark::State& state){
	for (auto _ : state) {
		OnStack::Queue<int> q;
		for (int i = 0; i < BIG_NUMBER; ++i) {
			q.push(i);
		}
	}
}
BENCHMARK(BM_PushQueueOnStack);

static void BM_PushQueueOnList(benchmark::State& state){
	for (auto _ : state) {
		OnList::Queue<int> q;
		for (int i = 0; i < BIG_NUMBER; ++i) {
			q.push(i);
		}
	}
}
BENCHMARK(BM_PushQueueOnList);

static void BM_PushPopQueueOnStack(benchmark::State& state){
	for (auto _ : state) {
		OnStack::Queue<int> q;
		for (int i = 0; i < BIG_NUMBER; ++i) {
			q.push(i);
		}
		for (int i = 0; i < BIG_NUMBER; ++i) {
			q.pop();
		}
	}
}
BENCHMARK(BM_PushPopQueueOnStack);

static void BM_PushPopQueueOnList(benchmark::State& state){
	for (auto _ : state) {
		OnList::Queue<int> q;
		for (int i = 0; i < BIG_NUMBER; ++i) {
			q.push(i);
		}
		for (int i = 0; i < BIG_NUMBER; ++i) {
			q.pop();
		}
	}
}
BENCHMARK(BM_PushPopQueueOnList);

BENCHMARK_MAIN();