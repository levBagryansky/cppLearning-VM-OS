find_package(benchmark REQUIRED)

add_executable(benchmark_run benchmark.cpp ${SOURCE_FILES})

target_link_libraries(benchmark_run benchmark::benchmark)

add_dependencies(benchmark_run ${PROJECT_NAME}_tests)
