project(Google_benchmark)

add_subdirectory(lib)
include_directories(${Google_benchmark_SOURCE_DIR}/include ${Google_benchmark_SOURCE_DIR})

add_executable(Google_benchmark_run benchmark.cpp ../Bool_Stack.cpp)

target_link_libraries(Google_benchmark_run benchmark benchmark_main)
