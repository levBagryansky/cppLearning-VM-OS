message("Include testing")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_tests test.cpp ../src/BoolStack.cpp)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main)
enable_testing()
