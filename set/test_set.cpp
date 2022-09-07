#include <set>

#include "gtest/gtest.h"
#include "set.hpp"

TEST(set, set_1) {
  Set<int> tree{};
  ASSERT_TRUE(tree.IsEmpty());
}

TEST(set, set_2) {
  Set<int> tree{};
  auto it = tree.Insert(45).first;
  ASSERT_EQ(tree.Size(), 1);
  ASSERT_EQ(*it, 45);
}

TEST(set, set_3) {
  Set<int> tree{1, 2, 3};
  std::set<int> original{1, 2, 3};
  auto it = tree.begin();
  auto it_or = original.begin();
  ASSERT_EQ(*it, *it_or);
  --it;
  --it;
  --it;
  --it_or;
  --it_or;
  --it_or;
  ASSERT_EQ(*it, *it_or);

  it = tree.end();
  it_or = original.end();
  ASSERT_EQ(*it, *it_or);
  ++it;
  ++it;
  ++it;
  ++it_or;
  ++it_or;
  ++it_or;
  ASSERT_EQ(*it, *it_or);
}

TEST(set, set_4) {
  Set<int> tree;
  std::set<int> original;
  for (int i = -50000; i <= 50000; i++) {
    tree.Insert(i);
    original.insert(i);
    ASSERT_EQ(tree.Size(), original.size());
    ASSERT_EQ(*tree.begin(), *original.begin());
  }
  for (int i = -50000; i <= 50000; i++) {
    tree.Erase(tree.Find(i));
    original.erase(original.find(i));
    ASSERT_EQ(tree.Size(), original.size());
    if (i < 50000) {
      ASSERT_EQ(*tree.begin(), *original.begin());
    }
  }
}

TEST(set, set_6) {
  Set<int> tree1{1, 2, 3};
  Set<int> tree2(std::move(tree1));
  ASSERT_TRUE(tree1.IsEmpty());
  ASSERT_EQ(tree2.Size(), 3);
  ASSERT_EQ(*tree2.begin(), 1);
  ASSERT_EQ(*tree2.end(), 3);
}

TEST(set, set_7) {
  Set<int> tree{1};
  auto it = tree.end();
  --it;
  ASSERT_EQ(*tree.begin(), *it);
  auto tmp = tree.end();
  ASSERT_TRUE(it != tmp);
}

TEST(set, set_8) {
  Set<int> tree{1, 2, 3};
  Set<int>::ConstIterator it(tree.cbegin());
  ASSERT_EQ(*it, 1);
}

TEST(set, set_9) {
  Set<int> tree;
  for (int i = -500000; i <= 500000; i++) tree.Insert(std::rand());
  auto it = tree.begin();
  for (int i = -2500; i <= 2500; i++) ++it;
  for (int i = -2500; i <= 2500; i++) --it;
  ASSERT_TRUE(it == tree.begin());
  for (int i = -500000; i <= 500000; i++) {
    int tmp = std::rand();
    tree.Erase(tree.Find(tmp));
  }
  tree.Clear();
  ASSERT_TRUE(tree.IsEmpty());
}

TEST(set, set_10) {
  Set<int> tree1{1, -77, 24, 38, 999, -17, -7, -16, 14};
  Set<int> tree2(tree1);
  ASSERT_TRUE(!tree1.IsEmpty());
  ASSERT_TRUE(!tree2.IsEmpty());
  tree2.Erase(tree2.Find(-17));
  tree2.Erase(tree2.Find(999));
  tree2.Erase(tree2.Find(14));
  tree2.Erase(tree2.Find(38));
  tree2.Erase(tree2.Find(1));
  tree2.Erase(tree2.Find(-16));
  tree2.Erase(tree2.Find(24));
  tree2.Erase(tree2.Find(-7));
  tree2.Erase(tree2.Find(-77));
  ASSERT_TRUE(!tree1.IsEmpty());
  ASSERT_TRUE(tree2.IsEmpty());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
