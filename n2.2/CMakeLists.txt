cmake_minimum_required(VERSION 3.14)
project(ArrayProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

# Флаги покрытия (без кавычек!)
set(COVERAGE_FLAGS -g -O0 --coverage)

# Google Test — теперь с Array и List
find_package(GTest REQUIRED)
add_executable(test_gtest_array test_array_gtest.cpp)
target_compile_options(test_gtest_array PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_gtest_array PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_gtest_array GTest::GTest GTest::Main pthread)

add_executable(test_gtest_list test_list_gtest.cpp)
target_compile_options(test_gtest_list PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_gtest_list PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_gtest_list GTest::GTest GTest::Main pthread)

add_executable(test_dlist_gtest test_dlist_gtest.cpp)
target_compile_options(test_dlist_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_dlist_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_dlist_gtest GTest::GTest GTest::Main pthread)

add_executable(test_stack_gtest test_stack_gtest.cpp)
target_compile_options(test_stack_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_stack_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_stack_gtest GTest::GTest GTest::Main pthread)

add_executable(test_queue_gtest test_queue_gtest.cpp)
target_compile_options(test_queue_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_queue_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_queue_gtest GTest::GTest GTest::Main pthread)

add_executable(test_tree_gtest test_tree_gtest.cpp)
target_compile_options(test_tree_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_tree_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_tree_gtest GTest::GTest GTest::Main pthread)

add_executable(test_hashtable_gtest test_hashtable_gtest.cpp)
target_compile_options(test_hashtable_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_hashtable_gtest PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_hashtable_gtest GTest::GTest GTest::Main pthread)

# Boost Test
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
add_executable(test_boost_array test_array_boost.cpp)
target_compile_options(test_boost_array PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_boost_array PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_boost_array Boost::unit_test_framework)

add_executable(test_boost_list test_list_boost.cpp)
target_compile_options(test_boost_list PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_boost_list PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_boost_list Boost::unit_test_framework)

add_executable(test_dlist_boost test_dlist_boost.cpp)
target_compile_options(test_dlist_boost PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_dlist_boost PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_dlist_boost Boost::unit_test_framework)

add_executable(test_stack_boost test_stack_boost.cpp)
target_compile_options(test_stack_boost PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_stack_boost PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_stack_boost Boost::unit_test_framework)

add_executable(test_queue_boost test_queue_boost.cpp)
target_compile_options(test_queue_boost PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_queue_boost PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_queue_boost Boost::unit_test_framework)

add_executable(test_tree_boost test_tree_boost.cpp)
target_compile_options(test_tree_boost PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_tree_boost PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_tree_boost Boost::unit_test_framework)

add_executable(test_hashtable_boost test_hashtable_boost.cpp)
target_compile_options(test_hashtable_boost PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_hashtable_boost PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_hashtable_boost Boost::unit_test_framework)

# Catch2
find_package(Catch2 REQUIRED)
add_executable(test_catch_array test_array_catch.cpp)
target_compile_options(test_catch_array PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_catch_array PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_catch_array Catch2::Catch2WithMain)

add_executable(test_catch_list test_list_catch.cpp)
target_compile_options(test_catch_list PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_catch_list PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_catch_list Catch2::Catch2WithMain)

add_executable(test_dlist_catch test_dlist_catch.cpp)
target_compile_options(test_dlist_catch PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_dlist_catch PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_dlist_catch Catch2::Catch2WithMain)

add_executable(test_stack_catch test_stack_catch.cpp)
target_compile_options(test_stack_catch PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_stack_catch PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_stack_catch Catch2::Catch2WithMain)

add_executable(test_queue_catch test_queue_catch.cpp)
target_compile_options(test_queue_catch PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_queue_catch PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_queue_catch Catch2::Catch2WithMain)

add_executable(test_tree_catch test_tree_catch.cpp)
target_compile_options(test_tree_catch PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_tree_catch PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_tree_catch Catch2::Catch2WithMain)

add_executable(test_hashtable_catch test_hashtable_catch.cpp)
target_compile_options(test_hashtable_catch PRIVATE ${COVERAGE_FLAGS})
target_link_options(test_hashtable_catch PRIVATE ${COVERAGE_FLAGS})
target_link_libraries(test_hashtable_catch Catch2::Catch2WithMain)

# Benchmark
add_executable(run_benchmark benchmark.cpp)
target_compile_options(run_benchmark PRIVATE ${COVERAGE_FLAGS})
target_link_options(run_benchmark PRIVATE ${COVERAGE_FLAGS})
