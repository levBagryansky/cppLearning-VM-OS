message("Include testing")

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}_tests test.cpp ${ALL_CPP_FILES})

target_link_libraries(${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main)
enable_testing()

if (ADD_SANITIZERS)
    message("Build with sanitizers")
    target_compile_options(${PROJECT_NAME}_tests PUBLIC -fsanitize=address -g)
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()

if (USING_ON_STACK)
    add_definitions(-DUSING_ON_STACK)
elseif(USING_ON_LIST)
    add_definitions(-DOSING_ON_LIST)
endif()
