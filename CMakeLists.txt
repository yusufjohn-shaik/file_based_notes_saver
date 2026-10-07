cmake_minimum_required(VERSION 3.10)
project(FileBasedNotesSaver CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_executable(notes_saver src/main.cpp ${SOURCES})

# Test executable
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_runner.cpp")
    add_executable(run_tests tests/test_runner.cpp ${SOURCES})
endif()
