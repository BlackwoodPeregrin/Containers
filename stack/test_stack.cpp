#include <gtest/gtest.h>

#include <stack>

#include "stack.hpp"

TEST(stack, stack_1) {
  Stack<int> stack{};
  ASSERT_TRUE(stack.IsEmpty());
}

TEST(stack, stack_2) {
  Stack<int> stack{};
  stack.Push(45);
  ASSERT_EQ(stack.Pop(), 45);
  ASSERT_TRUE(stack.IsEmpty());
}

TEST(stack, stack_3) {
  Stack<int> stack{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::stack<int> original({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

  while (!stack.IsEmpty() && !original.empty()) {
    ASSERT_EQ(stack.Top(), original.top());
    stack.Pop();
    original.pop();
  }
}

TEST(stack, stack_4) {
  Stack<int> stack{55, 44, 33};
  std::stack<int> original({55, 44, 33});
  ASSERT_EQ(stack.Size(), original.size());

  while (!stack.IsEmpty() && !original.empty()) {
    ASSERT_EQ(stack.Top(), original.top());
    stack.Pop();
    original.pop();
  }
}

TEST(stack, stack_5) {
  Stack<int> stack1{1, 2, 3};
  Stack<int> stack2{4, 5, 6, 7};
  //
  std::stack<int> orig_stack1({1, 2, 3});
  std::stack<int> orig_stack2({4, 5, 6, 7});
  //
  stack1.Swap(stack2);
  orig_stack1.swap(orig_stack2);
  ASSERT_EQ(stack1.Size(), orig_stack1.size());

  while (!stack1.IsEmpty() && !orig_stack1.empty()) {
    ASSERT_EQ(stack1.Top(), orig_stack1.top());
    stack1.Pop();
    orig_stack1.pop();
  }

  ASSERT_EQ(stack2.Size(), orig_stack2.size());

  while (!stack2.IsEmpty() && !orig_stack2.empty()) {
    ASSERT_EQ(stack2.Top(), orig_stack2.top());
    stack2.Pop();
    orig_stack2.pop();
  }
}

TEST(stack, stack_6) {
  Stack<int> stack1{1, 2, 3};
  Stack<int> stack2(std::move(stack1));
  //
  std::stack<int> orig_stack1({1, 2, 3});
  std::stack<int> orig_stack2(std::move(orig_stack1));
  //
  ASSERT_TRUE(stack1.IsEmpty());
  ASSERT_TRUE(orig_stack1.empty());
  ASSERT_EQ(stack2.Size(), orig_stack2.size());

  while (!stack2.IsEmpty() && !orig_stack2.empty()) {
    ASSERT_EQ(stack2.Top(), orig_stack2.top());
    stack2.Pop();
    orig_stack2.pop();
  }
}

TEST(stack, stack_9) {
  Stack<int> stack1{1, 2, 3};
  Stack<int> stack2{};
  //
  std::stack<int> orig_stack1({1, 2, 3});
  std::stack<int> orig_stack2{};
  //
  stack2 = std::move(stack1);
  orig_stack2 = std::move(orig_stack1);
  ASSERT_TRUE(stack1.IsEmpty());
  ASSERT_TRUE(orig_stack1.empty());
  ASSERT_EQ(stack2.Size(), orig_stack2.size());
  while (!stack2.IsEmpty() && !orig_stack2.empty()) {
    ASSERT_EQ(stack2.Top(), orig_stack2.top());
    stack2.Pop();
    orig_stack2.pop();
  }
}

TEST(stack, stack_12) {
  Stack<std::string> stack{"a", "b", "c"};
  std::stack<std::string> orig_stack({"a", "b", "c"});
  ASSERT_EQ(stack.Size(), orig_stack.size());
  while (!stack.IsEmpty() && !orig_stack.empty()) {
    ASSERT_EQ(stack.Top(), orig_stack.top());
    stack.Pop();
    orig_stack.pop();
  }
}

TEST(stack, stack_13) {
  Stack<double> stack1{67, 56, 45};
  Stack<double> stack2(stack1);
  //
  std::stack<int> orig_stack1({67, 56, 45});
  std::stack<int> orig_stack2(orig_stack1);
  //
  ASSERT_EQ(stack2.Size(), orig_stack2.size());
  while (!stack2.IsEmpty() && !orig_stack2.empty()) {
    ASSERT_EQ(stack2.Top(), orig_stack2.top());
    stack2.Pop();
    orig_stack2.pop();
  }
  ASSERT_EQ(stack1.Size(), orig_stack1.size());
  while (!stack1.IsEmpty() && !orig_stack1.empty()) {
    ASSERT_EQ(stack1.Top(), orig_stack1.top());
    stack1.Pop();
    orig_stack1.pop();
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
