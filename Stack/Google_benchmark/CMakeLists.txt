include_directories(${Google_benchmark_SOURCE_DIR}/include ${Google_benchmark_SOURCE_DIR})

add_executable(Google_benchmark_run benchmark.cpp ../BoolStack.cpp)

target_link_libraries(Google_benchmark_run benchmark.cpp)

add_dependencies(Google_benchmark_run ${PROJECT_NAME})
