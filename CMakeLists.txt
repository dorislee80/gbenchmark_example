cmake_minimum_required(VERSION 3.10)
project(gbenchmark)

set(CMAKE_CXX_STANDARD 11)

include_directories("src")


add_executable(gbenchmark "src/main.cpp" "src/conversion.cpp" "src/conversion.h")


message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")


enable_testing()


#
# benchmark
#

add_executable(int_to_string_benchmark "bench/bench_int_to_string.cpp" "src/conversion.cpp" "src/conversion.h")
target_link_libraries(int_to_string_benchmark -lbenchmark -pthread)
add_test(NAME int_to_string_benchmark COMMAND int_to_string_benchmark)

add_executable(branch_prediction_benchmark "bench/bench_branch_prediction")
target_link_libraries(branch_prediction_benchmark -lbenchmark -pthread)
add_test(NAME branch_prediction_benchmark COMMAND branch_prediction_benchmark)