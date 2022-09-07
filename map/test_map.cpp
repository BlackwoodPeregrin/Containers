#include <gtest/gtest.h>

#include <map>

#include "map.hpp"

TEST(map, map_default_constr_1) {
  Map<int, float> my_map;
  ASSERT_EQ(my_map.Size(), 0);
}

TEST(map, map_initializer_const_1) {
  Map<int, float> my_map{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  ASSERT_EQ(my_map.Size(), 3);
}

TEST(map, map_default_constr_2) {
  Map<int, float> my_map{};
  ASSERT_EQ(my_map.Size(), 0);
}

TEST(map, map_initializer_const_2) {
  Map<int, float> my_map{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  Map<int, float> my_map2(my_map);
  ASSERT_EQ(my_map2.Size(), 3);
}

TEST(map, map_copy_constr) {
  Map<int, float> my_map{};
  Map<int, float> my_map2(my_map);
  ASSERT_EQ(my_map2.Size(), 0);
}

TEST(map, map_move_constr_1) {
  Map<int, float> my_map{};
  Map<int, float> my_map2(std::move(my_map));
  ASSERT_EQ(my_map2.Size(), 0);
}

TEST(map, map_move_constr_2) {
  Map<int, float> my_map{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  Map<int, float> my_map2(std::move(my_map));
  ASSERT_EQ(my_map2.Size(), 3);
  ASSERT_EQ(my_map.Size(), 0);
}

TEST(map, map_operator_assign_copy_1) {
  Map<int, float> my_map{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  Map<int, float> my_map2;
  my_map2 = my_map;
  ASSERT_EQ(my_map2.Size(), 3);
  ASSERT_EQ(my_map.Size(), 3);
}

TEST(map, map_operator_assign_move_1) {
  Map<int, float> my_map{{4, 3.4}, {6, 4.8}, {2, 4.5}};
  Map<int, float> my_map2;
  my_map2 = std::move(my_map);
  ASSERT_EQ(my_map2.Size(), 3);
  ASSERT_EQ(my_map.Size(), 0);
}

TEST(map, map_at_1) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(my_map.at(6), "second");
}

TEST(map, map_at_2) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(my_map.at(2), "third");
}

TEST(map, map_at_3) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(my_map.at(6), "second");
}

TEST(map, map_operator_SB_1) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(my_map[4], "first");
}

TEST(map, map_operator_SB_2) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_EQ(my_map[4], "first");
}

TEST(map, map_operator_SB_3) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  my_map[4] = "qwerty";
  ASSERT_EQ(my_map[4], "qwerty");
}

TEST(map, map_operator_SB_4) {
  Map<int, std::string> my_map{};
  my_map[4] = "qwerty";
  ASSERT_EQ(my_map[4], "qwerty");
}

TEST(map, map_IsEmpty_1) {
  Map<int, std::string> my_map{};
  ASSERT_TRUE(my_map.IsEmpty());
}

TEST(map, map_IsEmpty_2) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  my_map.Clear();
  ASSERT_TRUE(my_map.IsEmpty());
}

TEST(map, map_IsEmpty_3) {
  Map<int, std::string> my_map{};
  my_map.Clear();
  ASSERT_TRUE(my_map.IsEmpty());
}

TEST(map, map_insert_1) {
  Map<int, std::string> my_map{};
  my_map.Insert(5, "qwerty");
  my_map.Insert(8, "qwerty");
  my_map.Insert(9, "qwerty");
  my_map.Insert(4, "qwerty");
  my_map.Insert(6, "qwerty");
  ASSERT_EQ(my_map[6], "qwerty");
}

TEST(map, map_insert_2) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  my_map.Insert(1, "qwerty");
  ASSERT_EQ(my_map[1], "qwerty");
}

TEST(map, map_insert_3) {
  Map<int, std::string> my_map{};
  my_map.Insert(5, "qwerty");
  my_map.Insert(3, "wer");
  my_map.Insert(4, "ty");
  ASSERT_EQ(my_map[5], "qwerty");
}

TEST(map, map_insert_4) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  my_map.Insert(1, "qwerty");
  my_map.Insert(-1, "qwerty");
  my_map.Insert(-2, "qwerty");
  my_map.Insert(-3, "qwerty");
  my_map.Insert(7, "qwerty");
  my_map.Insert(8, "qwerty");
  my_map.Insert(9, "qwerty");
  ASSERT_EQ(my_map[1], "qwerty");
}

TEST(map, map_InsertOrAssign_1) {
  Map<int, std::string> my_map{};
  my_map.InsertOrAssign(4, "first");
  ASSERT_EQ(my_map[4], "first");
}

TEST(map, map_InsertOrAssign_2) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  my_map.InsertOrAssign(4, "wer");
  ASSERT_EQ(my_map[4], "wer");
}

TEST(map, map_insert_5) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  my_map.Insert(8, "qwerty");
  ASSERT_EQ(my_map[8], "qwerty");
}

TEST(map, map_Contains_1) {
  Map<int, std::string> my_map{{4, "first"}, {6, "second"}, {2, "third"}};
  ASSERT_TRUE(my_map.Contains(2));
}

TEST(map, map_insert_6) {
  Map<int, std::string> my_map{};
  my_map.Insert(5, "qwerty");
  my_map.Insert(8, "ке");
  my_map.Insert(7, "нг");
  ASSERT_EQ(my_map[5], "qwerty");
}

TEST(map, map_insert_7) {
  Map<int, std::string> my_map{};
  my_map.Insert(10, "qwerty");
  my_map.Insert(16, "ке");
  my_map.Insert(14, "нг");
  my_map.Insert(13, "нг");
  my_map.Insert(8, "нг");
  my_map.Insert(12, "нг");
  ASSERT_EQ(my_map[10], "qwerty");
}

TEST(map, map_erase_1) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  std::pair<double, int> ff11 = {17.5, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  my_map.Insert(ff4);
  my_map.Insert(ff5);
  my_map.Insert(ff6);
  my_map.Insert(ff7);
  my_map.Insert(ff8);
  my_map.Insert(ff9);
  my_map.Insert(ff10);
  my_map.Insert(ff11);
  Map<double, int>::Iterator it(my_map.begin());
  ASSERT_EQ(my_map.Size(), 13);
  ++it;
  ++it;
  ++it;
  ++it;
  auto z2 = *it;
  ASSERT_EQ(z2.first, ff4.first);
  ASSERT_EQ(z2.second, ff4.second);
}

TEST(map, map_erase_2) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  my_map.Insert(ff4);
  my_map.Insert(ff5);
  my_map.Insert(ff6);
  my_map.Insert(ff7);
  my_map.Insert(ff8);
  my_map.Insert(ff9);
  my_map.Insert(ff10);
  Map<double, int>::Iterator it(my_map.begin());
  ++it;
  ++it;
  ++it;
  ++it;
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 11);
  Map<double, int>::Iterator it2(my_map.begin());
  ++it2;
  ++it2;
  ++it2;
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff6.first);
}

TEST(map, map_erase_3) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  my_map.Insert(ff4);
  my_map.Insert(ff5);
  my_map.Insert(ff6);
  my_map.Insert(ff7);
  my_map.Insert(ff8);
  my_map.Insert(ff9);
  my_map.Insert(ff10);
  Map<double, int>::Iterator it(my_map.begin());
  ++it;
  ++it;
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 11);
  Map<double, int>::Iterator it2(my_map.begin());
  ++it2;
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff5.first);
}

TEST(map, map_erase_4) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};

  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  Map<double, int>::Iterator it(my_map.begin());
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 2);
  Map<double, int>::Iterator it2(my_map.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f.first);
}

TEST(map, map_erase_5) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};

  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  Map<double, int>::Iterator it(my_map.begin());
  ++it;
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 2);
  Map<double, int>::Iterator it2(my_map.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff.first);
}

TEST(map, map_erase_6) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  Map<double, int>::Iterator it(my_map.begin());
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 1);
  Map<double, int>::Iterator it2(my_map.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f1.first);
}

TEST(map, map_erase_7) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {12, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  Map<double, int>::Iterator it(my_map.begin());
  ++it;
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 1);
  Map<double, int>::Iterator it2(my_map.begin());
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f1.first);
}

TEST(map, map_erase_8) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  Map<double, int>::Iterator it(my_map.begin());
  ++it;
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 4);
  Map<double, int>::Iterator it2(my_map.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f.first);
}

TEST(map, map_erase_9) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {13, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  Map<double, int>::Iterator it(my_map.begin());

  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 4);
  Map<double, int>::Iterator it2(my_map.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, f.first);
}

TEST(map, map_erase_10) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {13, 10};
  std::pair<double, int> ff4 = {10, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  my_map.Insert(ff4);
  Map<double, int>::Iterator it(my_map.begin());
  ++it;
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 5);
  Map<double, int>::Iterator it2(my_map.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff3.first);
}

TEST(map, map_erase_11) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {14, 10};
  std::pair<double, int> ff4 = {10, 10};
  std::pair<double, int> ff5 = {15, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  my_map.Insert(ff4);
  my_map.Insert(ff5);
  Map<double, int>::Iterator it(my_map.begin());
  ++it;
  my_map.Erase(it);
  ASSERT_EQ(my_map.Size(), 6);
  Map<double, int>::Iterator it2(my_map.begin());
  ++it2;
  std::pair<double, int> z2 = *it2;
  ASSERT_EQ(z2.first, ff3.first);
}

TEST(map, map_erase_12) {
  Map<double, int> my_map;
  std::pair<double, int> kv1 = {1, 10};
  std::pair<double, int> kv2 = {2, 10};
  std::pair<double, int> kv3 = {3, 10};
  std::pair<double, int> kv4 = {4, 10};
  std::pair<double, int> kv5 = {5, 10};
  std::pair<double, int> kv6 = {6, 10};
  std::pair<double, int> kv7 = {7, 10};
  std::pair<double, int> kv8 = {8, 10};
  std::pair<double, int> kv9 = {9, 10};

  my_map.Insert(kv4);
  my_map.Insert(kv6);
  my_map.Insert(kv2);
  my_map.Insert(kv3);
  my_map.Insert(kv5);
  my_map.Insert(kv8);
  my_map.Insert(kv1);
  my_map.Insert(kv7);
  my_map.Insert(kv9);

  Map<double, int>::Iterator it = my_map.end();
  --it;
  ASSERT_EQ((*it).first, kv9.first);
  my_map.Erase(it);
  it = my_map.end();
  --it;
  ASSERT_EQ((*it).first, kv8.first);
  my_map.Erase(it);
  Map<double, int>::Iterator it1(my_map.begin());
  ASSERT_EQ((*it1).first, kv1.first);
  my_map.Erase(it1);
  Map<double, int>::Iterator it2(my_map.begin());
  ASSERT_EQ((*it2).first, kv2.first);
  my_map.Erase(it2);
  it2 = my_map.end();
  --it2;
  ASSERT_EQ((*it2).first, kv7.first);
  my_map.Erase(it2);
  Map<double, int>::Iterator it3(my_map.begin());
  ASSERT_EQ((*it3).first, kv3.first);
  my_map.Erase(it3);
  Map<double, int>::Iterator it4(my_map.begin());
  ASSERT_EQ((*it4).first, kv4.first);
  my_map.Erase(it4);
  it4 = my_map.begin();
  ASSERT_EQ((*it4).first, kv5.first);
  my_map.Erase(it4);
  it4 = my_map.begin();
  ASSERT_EQ((*it4).first, kv6.first);
  my_map.Erase(it4);
  ASSERT_EQ(my_map.Size(), 0);
}

TEST(map, map_iterator) {
  Map<double, int> my_map;
  std::pair<double, int> f = {16, 10};
  std::pair<double, int> f1 = {18, 10};
  std::pair<double, int> ff = {12, 10};
  std::pair<double, int> ff2 = {21, 10};
  std::pair<double, int> ff3 = {10, 10};
  std::pair<double, int> ff4 = {14, 10};
  std::pair<double, int> ff5 = {13, 10};
  std::pair<double, int> ff6 = {15, 10};
  std::pair<double, int> ff7 = {17, 10};
  std::pair<double, int> ff8 = {22, 10};
  std::pair<double, int> ff9 = {9, 10};
  std::pair<double, int> ff10 = {15.5, 10};
  my_map.Insert(f);
  my_map.Insert(f1);
  my_map.Insert(ff);
  my_map.Insert(ff2);
  my_map.Insert(ff3);
  my_map.Insert(ff4);
  my_map.Insert(ff5);
  my_map.Insert(ff6);
  my_map.Insert(ff7);
  my_map.Insert(ff8);
  my_map.Insert(ff9);
  my_map.Insert(ff10);
  Map<double, int>::Iterator it(my_map.begin());
  while (it != my_map.end()) {
    ++it;
  }
  --it;
  std::pair<double, int> z2 = *it;
  ASSERT_EQ(z2.first, ff8.first);

  while (it != my_map.begin()) {
    my_map.Erase(it);
    --it;
  }

  std::pair<double, int> z3 = *it;
  ASSERT_EQ(z3.first, ff9.first);

  my_map.Erase(it);

  ASSERT_EQ(my_map.Size(), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
