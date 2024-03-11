# https://google.github.io/googletest/quickstart-cmake.html
# テスト環境構築 ############################################################################################
cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# minishell関連のソースをgoogleTestに追加 ############################################################################################
file(GLOB_RECURSE LIB_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../../src/*.c)

# main.cを除外
list(REMOVE_ITEM LIB_SRCS ../../src/main.c)

add_library(libminishell ${LIB_SRCS})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DREADLINE_LIBRARY -O0 -g")
include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/../../include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../libft"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../readline-8.2"
)
link_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/../../libft"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../readline-8.2"
)
target_link_libraries(libminishell ft readline)

# テストファイルのビルド ############################################################################################
file(GLOB_RECURSE TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ./src/*.cpp)

foreach(testSrc ${TEST_SRCS})
  # Extract the filename without an extension (NAME_WE)
  get_filename_component(testName ${testSrc} NAME_WE)

  # Add compile target
  add_executable(${testName} ${testSrc})

  # Link to GoogleTest
  target_link_libraries(${testName} GTest::gtest_main libminishell)

  # Move testing binaries into a testBin directory
  set_target_properties(${testName} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

  # Add it to test execution
  add_test(NAME ${testName}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/${testName})
endforeach(testSrc)
