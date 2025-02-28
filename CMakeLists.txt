cmake_minimum_required(VERSION 3.28)

project(callbackmanager C CXX ASM)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
# set(CMAKE_EXE_LINKER_FLAGS "-Wl,-allow-multiple-definition")

set(CMAKE_CXX_FLAGS_RELEASE "-g")
# set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-O0 -g")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
set (_NEED_OPTIMIZATION_DOWNGRADE FALSE)
else()
set (_NEED_OPTIMIZATION_DOWNGRADE TRUE)
endif()
MESSAGE("optimization downgrade needed: ${_NEED_OPTIMIZATION_DOWNGRADE}")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# if(${_NEED_OPTIMIZATION_DOWNGRADE})
# target_compile_options(gtest
#         PUBLIC "-O2"
# )
# target_compile_options(gtest_main
#         PUBLIC "-O2"
# )
# endif()

enable_testing()

add_executable(${CMAKE_PROJECT_NAME}_example)
# if(${_NEED_OPTIMIZATION_DOWNGRADE})
# target_compile_options(${CMAKE_PROJECT_NAME}_example
#         PUBLIC "-O2"
# )
# endif()
target_sources(${CMAKE_PROJECT_NAME}_example
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/example/callback_examples.cpp
)
target_sources(${CMAKE_PROJECT_NAME}_example
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/callbackmanager.cpp
)

target_link_libraries( ${CMAKE_PROJECT_NAME}_example
)

add_executable(${CMAKE_PROJECT_NAME}_test)
# if(${_NEED_OPTIMIZATION_DOWNGRADE})
# target_compile_options(${CMAKE_PROJECT_NAME}_test
#         PUBLIC "-O2"
# )
# endif()
target_sources(${CMAKE_PROJECT_NAME}_test
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/test/callbackmanager_test.cpp
)
target_sources(${CMAKE_PROJECT_NAME}_test
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/callbackmanager.cpp
)

target_link_libraries( ${CMAKE_PROJECT_NAME}_test

        GTest::gtest_main
        GTest::gmock_main
)

add_executable(${CMAKE_PROJECT_NAME}_function
        ${CMAKE_CURRENT_SOURCE_DIR}/example/functions.cpp
)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)


