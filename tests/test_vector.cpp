#define CATCH_CONFIG_MAIN  // Это макрос для создания main() в Catch2
#include "catch.hpp"
#include "../include/vector.h"  // Подключаем ваш вектор

TEST_CASE("Vector initialization", "[vector]") {
    myStd::vector<int> vec;
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 4);

    myStd::vector<int> vec2 = {1, 2, 3};
    REQUIRE(vec2.size() == 3);
    REQUIRE(vec2.capacity() >= 3);
}

TEST_CASE("Vector push_back and size", "[vector]") {
    myStd::vector<int> vec;
    vec.push_back(10);
    REQUIRE(vec.size() == 1);
    REQUIRE(vec[0] == 10);

    vec.push_back(20);
    REQUIRE(vec.size() == 2);
    REQUIRE(vec[1] == 20);
}

TEST_CASE("Vector operator[]", "[vector]") {
    myStd::vector<int> vec = {1, 2, 3};
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);

    // Проверка на выход за границы
    REQUIRE_THROWS_AS(vec[3], std::out_of_range);
}

TEST_CASE("Vector resize", "[vector]") {
    myStd::vector<int> vec = {1, 2, 3};
    vec.resize(5);
    REQUIRE(vec.size() == 5);
    REQUIRE(vec[3] == 0);  // Новые элементы инициализируются значением по умолчанию

    vec.resize(2);
    REQUIRE(vec.size() == 2);
    REQUIRE(vec[1] == 2);
}

TEST_CASE("Vector clear", "[vector]") {
    myStd::vector<int> vec = {1, 2, 3};
    vec.clear();
    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 4);  // После clear capacity не меняется
}

TEST_CASE("Vector insert", "[vector]") {
    myStd::vector<int> vec = {1, 2, 3};
    vec.insert(vec.begin() + 1, 10);
    REQUIRE(vec.size() == 4);
    REQUIRE(vec[1] == 10);
    REQUIRE(vec[2] == 2);
}

TEST_CASE("Vector erase", "[vector]") {
    myStd::vector<int> vec = {1, 2, 3, 4};
    vec.erase(vec.begin() + 1);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec[1] == 3);

    vec.erase(vec.begin(), vec.begin() + 2);
    REQUIRE(vec.size() == 1);
    REQUIRE(vec[0] == 4);
}

TEST_CASE("Vector comparison operators", "[vector]") {
    myStd::vector<int> vec1 = {1, 2, 3};
    myStd::vector<int> vec2 = {1, 2, 3};
    myStd::vector<int> vec3 = {4, 5, 6};

    REQUIRE(vec1 == vec2);
    REQUIRE(vec1 != vec3);
    REQUIRE(vec1 < vec3);
    REQUIRE(vec3 > vec1);
}

TEST_CASE("Vector assign", "[vector]") {
    myStd::vector<int> vec;
    vec.assign(3, 10);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 10);
    REQUIRE(vec[1] == 10);
    REQUIRE(vec[2] == 10);

    myStd::vector<int> vec2 = {1, 2, 3};
    vec.assign(vec2.begin(), vec2.end());
    REQUIRE(vec.size() == 3);
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
    REQUIRE(vec[2] == 3);
}

TEST_CASE("Vector swap", "[vector]") {
    myStd::vector<int> vec1 = {1, 2, 3};
    myStd::vector<int> vec2 = {4, 5, 6};
    vec1.swap(vec2);

    REQUIRE(vec1.size() == 3);
    REQUIRE(vec1[0] == 4);
    REQUIRE(vec2.size() == 3);
    REQUIRE(vec2[0] == 1);
}

TEST_CASE("Vector iterators", "[vector]") {
    myStd::vector<int> vec = {1, 2, 3};
    auto it = vec.begin();
    REQUIRE(*it == 1);

    ++it;
    REQUIRE(*it == 2);

    auto rit = vec.rbegin();
    REQUIRE(*rit == 3);
}

TEST_CASE("Vector max_size", "[vector]") {
    myStd::vector<int> vec;
    REQUIRE(vec.max_size() == 2305843009213693951);
}
