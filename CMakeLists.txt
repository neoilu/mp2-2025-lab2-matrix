cmake_minimum_required(VERSION 3.10)
project(mp2_lab2_matrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к include
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest
)

# Тестовые исходники
file(GLOB TEST_SOURCES "test/*.cpp")

# Google Test
set(GTEST_SOURCES
    gtest/gtest-all.cc
)

# Создаём тестовый исполняемый файл
add_executable(matrix_test
    ${TEST_SOURCES}
    ${GTEST_SOURCES}
)

# Линкуем pthread (требуется для gtest на Linux/macOS)
target_link_libraries(matrix_test pthread)

# Включаем CTest
enable_testing()
add_test(NAME matrix_test COMMAND matrix_test)