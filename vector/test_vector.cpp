#include <gtest/gtest.h>

#include <vector>

#include "vector.hpp"

TEST(vector1, vector_simple_constructor) {
  Vector<int> vec;
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.size(), 0);
}

TEST(vector2, vector_parametrized_constructor) {
  Vector<int> vec1(5);
  std::vector<int> vec2(5);
  ASSERT_EQ(vec1.size(), 5);
  ASSERT_EQ(vec1.size(), vec2.size());
}

TEST(vector3, vector_init_size_constructor) {
  Vector<int> vec{1, 2, 3, 4};
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.at(3), 4);
}

TEST(vector4, vector_copy_constructor) {
  Vector<int> vec2{1, 2, 3, 4};
  Vector<int> vec3(vec2);
  ASSERT_EQ(vec2.size(), vec3.size());
  ASSERT_EQ(vec2.at(2), vec3.at(2));
}

TEST(vector5, vector_move_constructor) {
  Vector<int> vec1{1, 2, 3, 4};
  Vector<int> vec2(std::move(vec1));
  ASSERT_EQ(vec2.at(0), 1);
  ASSERT_EQ(vec2.at(1), 2);
  ASSERT_EQ(vec2.at(2), 3);
  ASSERT_EQ(vec2.at(3), 4);
  ASSERT_EQ(vec2.size(), 4);
}

TEST(vector6, vector_at) {
  Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  ASSERT_EQ(vec1.at(1), 2);
  ASSERT_EQ(vec1.at(1), vec2.at(1));
}

TEST(vector7, vector_operator_square_brackets) {
  Vector<int> vec1{1, 2, 3, 4};
  ASSERT_EQ(vec1[3], 4);
}

TEST(vector8, vector_front) {
  Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  int s21_value = vec1.front();
  int std_value = vec2.front();
  ASSERT_EQ(s21_value, 1);
  ASSERT_EQ(s21_value, std_value);
  Vector<int> vec3;
}

TEST(vector9, vector_back) {
  Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  int s21_value = vec1.back();
  int std_value = vec2.back();
  ASSERT_EQ(s21_value, 4);
  ASSERT_EQ(s21_value, std_value);
  Vector<int> vec3;
}

TEST(vector11, vector_empty) {
  Vector<int> vec1;
  std::vector<int> vec2;
  ASSERT_TRUE(vec1.empty());
  ASSERT_TRUE(vec2.empty());
  ASSERT_EQ(vec1.empty(), vec2.empty());
}

TEST(vector12, vector_size) {
  Vector<int> vec1;
  std::vector<int> vec2;
  ASSERT_EQ(vec1.size(), vec2.size());

  Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  ASSERT_EQ(vec3.size(), 3);
  ASSERT_EQ(vec3.size(), vec4.size());
}

TEST(vector14, vector_reserve) {
  Vector<int> vec1;
  std::vector<int> vec2;
  vec1.reserve(5);
  vec2.reserve(5);
  ASSERT_EQ(vec1.capacity(), 5);
  ASSERT_EQ(vec2.capacity(), 5);

  Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  vec3.reserve(10);
  vec4.reserve(10);
  ASSERT_EQ(vec3.at(2), 3);
  ASSERT_EQ(vec4.at(2), 3);
  vec3[7] = 9;
  vec4[7] = 9;
  ASSERT_EQ(vec3.size(), 3);
  ASSERT_EQ(vec3[7], 9);
  ASSERT_EQ(vec4.size(), 3);
  ASSERT_EQ(vec4[7], 9);
}

TEST(vector15, vector_shrink_to_fit) {
  Vector<int> vec1;
  std::vector<int> vec2;
  vec1.shrink_to_fit();
  vec2.shrink_to_fit();
  ASSERT_EQ(vec1.capacity(), 0);
  ASSERT_EQ(vec2.capacity(), 0);

  Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  vec3.reserve(10);
  vec4.reserve(10);

  vec3.shrink_to_fit();
  vec4.shrink_to_fit();
  ASSERT_EQ(vec3.capacity(), 3);
  ASSERT_EQ(vec3.at(1), 2);
  ASSERT_EQ(vec4.capacity(), 3);
  ASSERT_EQ(vec4.at(1), 2);
}

TEST(vector16, vector_begin) {
  Vector<int> vec1;
  ASSERT_EQ(vec1.begin(), nullptr);

  Vector<int> vec2{1, 2, 3};
  ASSERT_EQ(*vec2.begin(), 1);
}

TEST(vector17, vector_end) {
  Vector<int> vec1;
  ASSERT_EQ(vec1.end(), nullptr);

  Vector<int> vec2{1, 2, 3};
  std::vector<int> vec3{1, 2, 3};
  ASSERT_EQ(*(vec2.end() - 1), 3);
  ASSERT_EQ(*(vec3.end() - 1), 3);
}

TEST(vector18, vector_clear) {
  Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  vec3.clear();
  vec4.clear();
  ASSERT_EQ(vec3.size(), 0);
  ASSERT_EQ(vec4.size(), 0);
}

TEST(vector19, vector_insert) {
  Vector<int> vec3{1, 2, 3};
  std::vector<int> vec4{1, 2, 3};
  auto it = vec3.begin();
  auto it_orig = vec4.begin();
  ++it;
  ++it_orig;
  vec3.insert(it, 777);
  vec4.insert(it_orig, 777);
  ASSERT_EQ(vec3[0], vec4[0]);
  ASSERT_EQ(vec3[1], vec4[1]);
  ASSERT_EQ(vec3[2], vec4[2]);
  ASSERT_EQ(vec3[3], vec4[3]);
  std::cout << vec3.capacity() << std::endl;
  ASSERT_EQ(vec3.size(), vec4.size());
  ASSERT_EQ(vec3.capacity(), vec4.capacity());
}

TEST(vector20, vector_erase) {
  Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  auto s21it = vec1.begin();
  auto stdit = vec2.begin();
  s21it += 2;
  stdit += 2;
  vec1.erase(s21it);
  vec2.erase(stdit);
  ASSERT_EQ(vec1[0], vec2[0]);
  ASSERT_EQ(vec1[1], vec2[1]);
  ASSERT_EQ(vec1[2], vec2[2]);
  ASSERT_EQ(vec1.size(), vec2.size());
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector21, vector_push_back) {
  Vector<int> vec1{1, 2, 3};
  std::vector<int> vec2{1, 2, 3};
  int tmp1 = 4;
  vec1.push_back(tmp1);
  vec2.push_back(tmp1);
  ASSERT_EQ(vec1[0], vec2[0]);
  ASSERT_EQ(vec1[1], vec2[1]);
  ASSERT_EQ(vec1[2], vec2[2]);
  ASSERT_EQ(vec1[3], vec2[3]);
  ASSERT_EQ(vec1.size(), vec2.size());
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector22, vector_pop_back) {
  Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  vec1.pop_back();
  vec2.pop_back();
  ASSERT_EQ(vec1[0], vec2[0]);
  ASSERT_EQ(vec1[1], vec2[1]);
  ASSERT_EQ(vec1[2], vec2[2]);
  ASSERT_EQ(vec1.size(), vec2.size());
  ASSERT_EQ(vec1.capacity(), vec2.capacity());
}

TEST(vector23, vector_swap) {
  Vector<int> vec1{1, 2, 3, 4, 6};
  Vector<int> vec2{5, 6, 7, 8};
  vec1.swap(vec2);
  ASSERT_EQ(vec1[0], 5);
  ASSERT_EQ(vec1[1], 6);
  ASSERT_EQ(vec1[2], 7);
  ASSERT_EQ(vec1[3], 8);

  ASSERT_EQ(vec2[0], 1);
  ASSERT_EQ(vec2[1], 2);
  ASSERT_EQ(vec2[2], 3);
  ASSERT_EQ(vec2[3], 4);
  ASSERT_EQ(vec2[4], 6);

  ASSERT_EQ(vec1.size(), 4);
  ASSERT_EQ(vec2.size(), 5);
}

TEST(vector24, vector_iterators) {
  Vector<int> vec1{1, 2, 3, 4};
  std::vector<int> vec2{1, 2, 3, 4};
  typename Vector<int>::iterator s21it;
  typename std::vector<int>::iterator stdit;
  s21it = vec1.begin();
  stdit = vec2.begin();
  ASSERT_EQ(*s21it, *stdit);
  ++s21it;
  ASSERT_EQ(*s21it, vec1.at(1));
  --s21it;
  ASSERT_EQ(s21it, vec1.begin());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
