project(Google_benchmark)

add_subdirectory(libTests)

add_subdirectory(lib)

include_directories(${benchmark_SOURCE_DIR}/include)

add_executable(Google_benchmark_run benchmark.cpp ../src/BoolStack.cpp)

target_link_libraries(Google_benchmark_run benchmark benchmark_main)
