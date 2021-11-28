project(QueueOnStack)

include_directories(Stack/include)

file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp include/*.h)

add_subdirectory(Stack)

include_directories(include)

add_executable(${PROJECT_NAME} ${ALL_CPP_FILES})
