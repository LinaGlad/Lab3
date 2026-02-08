#!/bin/bash
set -e

echo "🛠 Сборка проекта..."
rm -rf build coverage_* *.info
mkdir build && cd build
cmake .. > /dev/null
make > /dev/null
cd ..

echo "🧪 Запуск тестов и сбор покрытия..."

TESTS=(
  test_gtest_array
  test_gtest_list
  test_dlist_gtest
  test_stack_gtest
  test_queue_gtest
  test_tree_gtest
  test_hashtable_gtest
  test_boost_array
  test_boost_list
  test_dlist_boost
  test_stack_boost
  test_queue_boost
  test_tree_boost
  test_hashtable_boost
  test_catch_array
  test_catch_list
  test_dlist_catch
  test_stack_catch
  test_queue_catch
  test_tree_catch
  test_hashtable_catch
)

for TEST in "${TESTS[@]}"; do
    echo "🔹 $TEST..."
    ./build/$TEST > /dev/null

    lcov --capture --directory build \
         --output-file ${TEST}.info \
         --ignore-errors mismatch,mismatch,empty,gcov \
         --quiet

    lcov --extract ${TEST}.info "${PWD}/*.h" \
         --output-file ${TEST}_filtered.info \
         --quiet

    genhtml ${TEST}_filtered.info \
            --output-directory coverage_${TEST} \
            --quiet \
            --ignore-errors source

    echo "   📄 coverage_${TEST}/index.html"
done

echo "⚡️ Бенчмарк..."
./build/run_benchmark
