message("Include testing")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_tests test_hash_table.cpp ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main)

enable_testing()

if (ADD_SANITIZERS)
    message("Build with sanitizers")

    target_compile_options(${PROJECT_NAME}_tests PUBLIC -fsanitize=address -g)
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address")

    target_compile_options(Dictionary_tests PUBLIC -fsanitize=address -g)
    set_target_properties(Dictionary_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()

add_custom_target(run_tests
        COMMENT "running test"
        COMMAND ./${PROJECT_NAME}_tests
        )
add_dependencies(run_tests ${PROJECT_NAME}_tests)

add_custom_target(run_tests_valgrind
        COMMENT "running test with valgrind"
        COMMAND valgrind ./${PROJECT_NAME}_tests
        )
add_dependencies(run_tests_valgrind ${PROJECT_NAME}_tests)

add_custom_target(run_all_tests)
add_dependencies(run_all_tests run_tests_valgrind run_tests)
