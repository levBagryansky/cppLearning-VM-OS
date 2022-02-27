message("Include testing")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(HashTable_tests test_hash_table.cpp)
target_link_libraries(HashTable_tests PUBLIC GTest::GTest GTest::Main)

enable_testing()

if (ADD_SANITIZERS)
    message("Build with sanitizers")

    target_compile_options(HashTable_tests PUBLIC -fsanitize=address -g)
    set_target_properties(HashTable_tests PROPERTIES LINK_FLAGS "-fsanitize=address")

    target_compile_options(Dictionary_tests PUBLIC -fsanitize=address -g)
    set_target_properties(Dictionary_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()