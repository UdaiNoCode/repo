cmake_minimum_required(VERSION 3.10)
project(LabCheck)

# Настройка компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление исходных файлов
add_executable(main src/main.cpp)

# Добавление тестов
add_executable(test_vector tests/test_vector.cpp)
target_link_libraries(test_vector PRIVATE Catch2::Catch2)
