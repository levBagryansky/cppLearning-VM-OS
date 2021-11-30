message("Include testing")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

if (ADD_SANITIZERS)
    message("Build with sanitizers")
    target_compile_options(${PROJECT_NAME}_tests PUBLIC -fsanitize=address -g)
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()

add_definitions(-DUSING_ON_STACK)
add_executable(${PROJECT_NAME}_tests_stack test.cpp ${ALL_CPP_FILES})
target_link_libraries(${PROJECT_NAME}_tests_stack PUBLIC GTest::GTest GTest::Main)

add_definitions(-DOSING_ON_LIST)
add_executable(${PROJECT_NAME}_tests_list test.cpp ${ALL_CPP_FILES})
target_link_libraries(${PROJECT_NAME}_tests_list PUBLIC GTest::GTest GTest::Main)

