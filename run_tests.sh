#!/bin/bash
set -e

BUILD_DIR="build"

echo "=== Cleaning old build ==="
rm -rf "$BUILD_DIR"

echo "=== Creating build directory ==="
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo "=== Configuring CMake ==="
cmake ..

echo "=== Building project ==="
cmake --build . -- -j$(nproc)

echo "=== Running all test executables ==="
# Αναζήτηση για executables με "test" στο όνομα
for test_exec in $(find . -maxdepth 1 -type f -executable -name "*test*"); do
    echo "--- Running $test_exec ---"
    "$test_exec" --gtest_color=yes --gtest_threads=4
done

echo "=== All tests completed successfully ==="
cd ..
