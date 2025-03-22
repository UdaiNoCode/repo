#!/bin/bash

# Переменные
SRC_DIR="src"
INCLUDE_DIR="include"
TESTS_DIR="tests"
BUILD_DIR="build"
CLANG_FORMAT="clang-format"
CMAKE="cmake"
MAKE="make"
AI_SCRIPT="scripts/ai_check.py"

# Итоговая оценка
TOTAL_GRADE=0

# Функция для проверки стиля кода
function check_style() {
    echo "Проверка стиля кода с помощью clang-format..."
    find ${SRC_DIR} ${INCLUDE_DIR} -name '*.h' -o -name '*.cpp' | xargs ${CLANG_FORMAT} --dry-run --Werror
    if [ $? -ne 0 ]; then
        echo "Ошибка: стиль кода не соответствует требованиям."
        return 20  # Штраф за стиль кода
    else
        echo "Стиль кода в порядке."
        return 0
    fi
}

# Функция для сборки проекта
function build_project() {
    echo "Сборка проекта..."
    mkdir -p ${BUILD_DIR}
    cd ${BUILD_DIR}
    ${CMAKE} ..
    ${MAKE}
    if [ $? -ne 0 ]; then
        echo "Ошибка: сборка проекта не удалась."
        return 30  # Штраф за неудачную сборку
    else
        echo "Проект успешно собран."
        return 0
    fi
    cd ..
}

# Функция для запуска тестов
function run_tests() {
    echo "Запуск тестов..."
    cd ${BUILD_DIR}
    ./test_vector
    if [ $? -ne 0 ]; then
        echo "Ошибка: тесты не прошли."
        return 30  # Штраф за проваленные тесты
    else
        echo "Все тесты прошли успешно."
        return 0
    fi
    cd ..
}

# Функция для анализа кода с помощью DeepSeek
function analyze_with_ai() {
    echo "Анализ кода с помощью DeepSeek..."
    python3 ${AI_SCRIPT} --code-dir ${SRC_DIR} --include-dir ${INCLUDE_DIR}
    if [ $? -ne 0 ]; then
        echo "Ошибка: анализ кода не удался."
        return 0  # Нейросеть не смогла оценить код
    else
        # Получаем оценку от нейросети
        AI_GRADE=$(grep "Оценка от нейросети:" check.log | awk '{print $4}')
        echo "Оценка от нейросети: ${AI_GRADE}"
        return ${AI_GRADE}
    fi
}

# Основной код
echo "Начало проверки лабораторной работы..."

# Шаг 1: Проверка стиля кода
check_style
STYLE_PENALTY=$?
TOTAL_GRADE=$((100 - STYLE_PENALTY))

# Шаг 2: Сборка проекта
build_project
BUILD_PENALTY=$?
TOTAL_GRADE=$((TOTAL_GRADE - BUILD_PENALTY))

# Шаг 3: Запуск тестов
run_tests
TESTS_PENALTY=$?
TOTAL_GRADE=$((TOTAL_GRADE - TESTS_PENALTY))

# Шаг 4: Анализ кода с помощью DeepSeek
analyze_with_ai
AI_GRADE=$?
TOTAL_GRADE=$((TOTAL_GRADE + AI_GRADE))

# Итоговая оценка (не более 100 баллов)
if [ ${TOTAL_GRADE} -gt 100 ]; then
    TOTAL_GRADE=100
fi

echo "Итоговая оценка: ${TOTAL_GRADE}/100"
