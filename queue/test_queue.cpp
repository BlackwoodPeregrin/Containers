#include <gtest/gtest.h>

#include <queue>

#include "queue.hpp"

TEST(queue, queue_1) {
  Queue<int> queue{};
  ASSERT_TRUE(queue.IsEmpty());
}

TEST(queue, queue_2) {
  Queue<int> queue{};
  queue.Push(45);
  std::queue<int> que_orig{};
  que_orig.push(45);
  ASSERT_EQ(queue.Front(), que_orig.front());
  ASSERT_EQ(queue.Back(), que_orig.back());
}

TEST(queue, queue_3) {
  Queue<int> queue{1, 2, 3};
  std::queue<int> que_orig({1, 2, 3});
  ASSERT_EQ(queue.Size(), que_orig.size());
  while (!queue.IsEmpty()) {
    ASSERT_EQ(queue.Front(), que_orig.front());
    queue.Pop();
    que_orig.pop();
  }
}

TEST(queue, queue_4) {
  Queue<int> queue{55, 44, 33};
  std::queue<int> que_orig({55, 44, 33});
  ASSERT_EQ(queue.Size(), que_orig.size());
  ASSERT_EQ(queue.Front(), que_orig.front());
  ASSERT_EQ(queue.Back(), que_orig.back());
  queue.Pop();
  que_orig.pop();
  ASSERT_EQ(queue.Front(), que_orig.front());
  ASSERT_EQ(queue.Back(), que_orig.back());
  queue.Pop();
  que_orig.pop();
  ASSERT_EQ(queue.Front(), que_orig.front());
  ASSERT_EQ(queue.Back(), que_orig.back());
  queue.Pop();
  que_orig.pop();
  ASSERT_EQ(queue.Size(), que_orig.size());
}

TEST(queue, queue_5) {
  Queue<int> queue1{1, 2, 3};
  Queue<int> queue2{4, 5, 6, 7};
  queue1.swap(queue2);

  std::queue<int> queue1_orig({1, 2, 3});
  std::queue<int> queue2_orig({4, 5, 6, 7});
  queue1_orig.swap(queue2_orig);

  ASSERT_EQ(queue1.Size(), queue1_orig.size());
  ASSERT_EQ(queue1.Front(), queue1_orig.front());
  ASSERT_EQ(queue1.Back(), queue1_orig.back());
  queue1.Pop();
  queue1_orig.pop();
  ASSERT_EQ(queue1.Front(), queue1_orig.front());
  ASSERT_EQ(queue1.Back(), queue1_orig.back());
  queue1.Pop();
  queue1_orig.pop();
  ASSERT_EQ(queue1.Front(), queue1_orig.front());
  ASSERT_EQ(queue1.Back(), queue1_orig.back());
  queue1.Pop();
  queue1_orig.pop();
  ASSERT_EQ(queue1.Front(), queue1_orig.front());
  ASSERT_EQ(queue1.Back(), queue1_orig.back());
  queue1.Pop();
  queue1_orig.pop();
  ASSERT_EQ(queue1.Size(), queue1_orig.size());

  ASSERT_EQ(queue2.Size(), queue2_orig.size());
  ASSERT_EQ(queue2.Front(), queue2_orig.front());
  ASSERT_EQ(queue2.Back(), queue2_orig.back());
  queue2.Pop();
  queue2_orig.pop();
  ASSERT_EQ(queue2.Front(), queue2_orig.front());
  ASSERT_EQ(queue2.Back(), queue2_orig.back());
  queue2.Pop();
  queue2_orig.pop();
  ASSERT_EQ(queue2.Front(), queue2_orig.front());
  ASSERT_EQ(queue2.Back(), queue2_orig.back());
  queue2.Pop();
  queue2_orig.pop();
  ASSERT_EQ(queue2.Size(), queue2_orig.size());
}

TEST(queue, queue_9) {
  Queue<double> queue1{45, 56, 67};
  Queue<double> queue2(queue1);
  std::queue<double> q_origin1({45, 56, 67});
  std::queue<double> q_origin2(q_origin1);

  ASSERT_EQ(queue2.Size(), q_origin2.size());
  ASSERT_EQ(queue2.Front(), q_origin2.front());
  ASSERT_EQ(queue2.Back(), q_origin2.back());
  queue2.Pop();
  q_origin2.pop();
  ASSERT_EQ(queue2.Front(), q_origin2.front());
  ASSERT_EQ(queue2.Back(), q_origin2.back());
  queue2.Pop();
  q_origin2.pop();
  ASSERT_EQ(queue2.Front(), q_origin2.front());
  ASSERT_EQ(queue2.Back(), q_origin2.back());
  queue2.Pop();
  q_origin2.pop();
  ASSERT_EQ(queue2.Size(), q_origin2.size());
}

TEST(queue, queue_10) {
  Queue<int> queue1{45, 56, 67};
  Queue<int> queue2{};
  queue2 = std::move(queue1);

  std::queue<double> q_origin1({45, 56, 67});
  std::queue<double> q_origin2{};
  q_origin2 = std::move(q_origin1);

  ASSERT_EQ(queue1.IsEmpty(), q_origin1.empty());
  ASSERT_EQ(queue2.Front(), q_origin2.front());
  ASSERT_EQ(queue2.Back(), q_origin2.back());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
