#include <gtest/gtest.h>

#include <list>
#include <string>

#include "list.hpp"

TEST(List, test_default_constructor) {
  List<int> test;
  std::list<int> origin;
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_constructor_init) {
  List<int> test(2);
  std::list<int> origin(2);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_init_list) {
  List<std::string> test{"Hello", " world"};
  std::list<std::string> origin{"Hello", " world"};
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_init_list_pair) {
  List<std::pair<int, double>> test{{1, 1.2}, {3, 4.5}};
  std::list<std::pair<int, double>> origin{{1, 1.2}, {3, 4.5}};
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_init_list2) {
  List<char> test{'H', 'e', 'l', 'l', 'o', ' ', ' ', 'w', 'o', 'r', 'l', 'd'};
  std::list<char> origin{'H', 'e', 'l', 'l', 'o', ' ',
                         ' ', 'w', 'o', 'r', 'l', 'd'};
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_init_list_fail) {
  List<char> test{'H', 'e', 'l', 'l', 'o', ' ', ' ',
                  'w', 'o', 'r', 'l', 'd', '!'};
  std::list<char> origin{'H', 'e', 'l', 'l', 'o', ' ', ' ',
                         'w', 'o', 'r', 'l', 'd', '!'};
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_constructor_copy) {
  List<char> test{'H', 'i'};
  std::list<char> origin{'H', 'i'};
  List<char> testCopy(test);
  std::list<char> originCopy(origin);
  ASSERT_EQ(testCopy.size(), originCopy.size());
  ASSERT_EQ(testCopy.front(), originCopy.front());
  ASSERT_EQ(testCopy.back(), originCopy.back());
}

TEST(List, test_constructor_copy2) {
  List<double> test{1.278453, 9.87654321};
  std::list<double> origin{1.278453, 9.87654321};
  List<double> testCopy(test);
  std::list<double> originCopy(origin);
  ASSERT_EQ(testCopy.size(), originCopy.size());
  ASSERT_EQ(testCopy.front(), originCopy.front());
  ASSERT_EQ(testCopy.back(), originCopy.back());
}

TEST(List, test_constructor_move) {
  List<double> test{1.278453, 9.87654321};
  std::list<double> origin{1.278453, 9.87654321};
  List<double> testMove(std::move(test));
  std::list<double> originMove(std::move(origin));
  ASSERT_EQ(testMove.size(), originMove.size());
  ASSERT_EQ(testMove.front(), originMove.front());
  ASSERT_EQ(testMove.back(), originMove.back());
}

TEST(List, test_iterator) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  auto testIt = test.begin();
  auto originIt = origin.begin();
  while (testIt != test.end()) {
    ASSERT_EQ(*testIt, *originIt);
    ++testIt;
    ++originIt;
  }
  --testIt;
  --originIt;
  ASSERT_EQ(*testIt, *originIt);
}

TEST(List, test_ConstIterator_1) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  auto testIt = test.cbegin();
  auto originIt = origin.cbegin();
  while (testIt != test.cend()) {
    ASSERT_EQ(*testIt, *originIt);
    ++testIt;
    ++originIt;
  }
  --testIt;
  --originIt;
  ASSERT_EQ(*testIt, *originIt);
}

TEST(List, test_ConstIterator_2) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  auto testIt = test.cend();
  --testIt;
  auto originIt = origin.cend();
  --originIt;
  while (testIt != test.cbegin()) {
    ASSERT_EQ(*testIt, *originIt);
    --testIt;
    --originIt;
  }
  ASSERT_EQ(*testIt, *originIt);
}

TEST(List, test_clear) {
  List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.clear();
  origin.clear();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_pop_back_1) {
  List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.pop_back();
  origin.pop_back();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_pop_back_2) {
  List<int> test{1};
  std::list<int> origin{1};
  test.pop_back();
  origin.pop_back();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_pop_front_1) {
  List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.pop_front();
  origin.pop_front();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_EQ(test.front(), origin.front());
}

TEST(List, test_pop_front_2) {
  List<int> test{1};
  std::list<int> origin{1};
  test.pop_front();
  origin.pop_front();
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_push_back_1) {
  List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.push_back(3.3);
  origin.push_back(3.3);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.back(), origin.back());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_push_back_2) {
  List<int> test;
  std::list<int> origin;
  test.push_back(1);
  origin.push_back(1);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_push_front_1) {
  List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  test.push_front(3.3);
  origin.push_front(3.3);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.back(), origin.back());
  ASSERT_EQ(test.front(), origin.front());
}

TEST(List, test_push_front_2) {
  List<int> test;
  std::list<int> origin;
  test.push_front(1);
  origin.push_front(1);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
  ASSERT_EQ(test.front(), origin.front());
}

TEST(List, test_push_front_3) {
  List<double> test{1.1};
  std::list<double> origin{1.1};
  test.push_front(3.3);
  origin.push_front(3.3);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.back(), origin.back());
  ASSERT_EQ(test.front(), origin.front());
}

TEST(List, test_swap_1) {
  List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  List<double> test1{3.3, 4.4};
  std::list<double> origin1{3.3, 4.4};
  test.swap(test1);
  origin.swap(origin1);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_swap_2) {
  List<double> test{1.1, 2.2};
  std::list<double> origin{1.1, 2.2};
  List<double> test1;
  std::list<double> origin1;
  test.swap(test1);
  origin.swap(origin1);
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_swap_3) {
  List<double> test;
  std::list<double> origin;
  List<double> test1{1.1, 2.2};
  std::list<double> origin1{1.1, 2.2};
  test.swap(test1);
  origin.swap(origin1);
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_erase_1) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  auto itT = test.begin();
  auto itO = origin.begin();
  test.erase(itT);
  origin.erase(itO);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_erase_2) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  auto itT = --test.end();
  auto itO = --origin.end();
  test.erase(itT);
  origin.erase(itO);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.front(), origin.front());
  ASSERT_EQ(test.back(), origin.back());
}

TEST(List, test_erase_3) {
  List<double> test{1.11};
  std::list<double> origin{1.11};
  auto itT = --test.end();
  auto itO = --origin.end();
  test.erase(itT);
  origin.erase(itO);
  ASSERT_EQ(test.size(), origin.size());
  ASSERT_EQ(test.empty(), origin.empty());
}

TEST(List, test_insert_1) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  auto itT = test.begin();
  ++itT;
  ++itT;
  auto itO = origin.begin();
  ++itO;
  ++itO;
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);

  ASSERT_EQ(*itT, *itO);
  itT = test.begin();
  itO = origin.begin();
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);
  ASSERT_EQ(*itT, *itO);
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_insert_2) {
  List<double> test{1.11};
  std::list<double> origin{1.11};
  auto itT(test.begin());
  auto itO = origin.begin();
  itT = test.insert(itT, 777.77);
  itO = origin.insert(itO, 777.77);
  ASSERT_EQ(*itT, *itO);
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_splice_1) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  List<double> sT{777.777, 888.88};
  std::list<double> oT{777.777, 888.88};
  auto cItT = test.cbegin();
  auto cItO = origin.cbegin();
  test.splice(cItT, sT);
  origin.splice(cItO, oT);
  auto itT = test.begin();
  auto itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
  List<double> sT2{777.777, 888.88};
  std::list<double> oT2{777.777, 888.88};
  cItT = test.cend();
  --cItT;
  cItO = origin.cend();
  --cItO;
  test.splice(cItT, sT2);
  origin.splice(cItO, oT2);
  itT = test.begin();
  itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_splice_2) {
  List<double> test{1.11};
  std::list<double> origin{1.11};
  List<double> sT{777.777};
  std::list<double> oT{777.777};
  auto cItT = test.cbegin();
  auto cItO = origin.cbegin();
  test.splice(cItT, sT);
  origin.splice(cItO, oT);
  auto itT = test.begin();
  auto itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_sort_1) {
  List<double> test{2.22, 5.55, 1.11, 3.33, 4.44};
  std::list<double> origin{2.22, 5.55, 1.11, 3.33, 4.44};
  test.sort();
  origin.sort();
  auto itT = test.begin();
  auto itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_sort_2) {
  List<std::string> test{"2.22", "5.55", "1.11", "3.33", "4.44"};
  std::list<std::string> origin{"2.22", "5.55", "1.11", "3.33", "4.44"};
  test.sort();
  origin.sort();
  auto itT = test.begin();
  auto itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_reverse_1) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  std::list<double> origin{1.11, 2.22, 3.33, 4.44, 5.55};
  test.reverse();
  origin.reverse();
  auto itT = test.begin();
  auto itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_reverse_2) {
  List<std::string> test{"1.11", "2.22", "3.33", "4.44", "5.55"};
  std::list<std::string> origin{"1.11", "2.22", "3.33", "4.44", "5.55"};
  test.reverse();
  origin.reverse();
  auto itT = test.begin();
  auto itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
}

TEST(List, test_unique_1) {
  List<double> test{1.11, 1.1, 2.22, 2, 3.33, 3.33, 4.44, 4.445, 5.55, 5.55};
  std::list<double> origin{1.11, 1.1,  2.22,  2,    3.33,
                           3.33, 4.44, 4.445, 5.55, 5.55};
  test.unique();
  origin.unique();
  auto itT = test.begin();
  auto itO = origin.begin();
  while (itT != test.end()) {
    ASSERT_EQ(*itT, *itO);
    ++itT;
    ++itO;
  }
  ASSERT_EQ(test.size(), origin.size());
}

TEST(List, test_operator_assig_l) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  List<double> test1{1.11, 2.22, 3.33, 4.44, 5.55};
  List<double> check;
  check = test;
  auto itT = test1.begin();
  auto itC = check.begin();
  while (itT != test1.end()) {
    ASSERT_EQ(*itT, *itC);
    ++itT;
    ++itC;
  }
  ASSERT_EQ(test1.size(), check.size());
}

TEST(List, test_operator_assig_r) {
  List<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  List<double> test1{1.11, 2.22, 3.33, 4.44, 5.55};
  List<double> check;
  check = std::move(test);
  ASSERT_TRUE(test.empty());
  auto itT = test1.begin();
  auto itC = check.begin();
  while (itT != test1.end()) {
    ASSERT_EQ(*itT, *itC);
    ++itT;
    ++itC;
  }
  ASSERT_EQ(test1.size(), check.size());
}

TEST(List, test_iter_r) {
  List<double> origin{1.1, 2.2};
  List<double> origin1{1.1, 2.2};
  auto a = origin.begin();
  auto a1 = origin.begin();
  auto b = origin1.begin();
  ASSERT_TRUE(a == a1);
  ASSERT_FALSE(a == b);
}

TEST(List, List_constructor1) {
  List<int> l;
  std::list<int> l_origin;
  ASSERT_EQ(l.empty(), l_origin.empty());
  List<double> l1;
  std::list<double> l1_origin;
  ASSERT_EQ(l1.empty(), l1_origin.empty());
  List<std::string> l2;
  std::list<std::string> l2_origin;
  ASSERT_EQ(l2.empty(), l2_origin.empty());
  List<char> l3;
  std::list<char> l3_origin;
  ASSERT_EQ(l3.empty(), l3_origin.empty());
  List<size_t> l4;
  std::list<size_t> l4_origin;
  ASSERT_EQ(l4.empty(), l4_origin.empty());
  List<bool> l5;
  std::list<bool> l5_origin;
  ASSERT_EQ(l5.empty(), l5_origin.empty());
}

TEST(List, List_constructor2) {
  List<int> l(10);
  std::list<int> l_origin(10);
  ASSERT_EQ(l.size(), l_origin.size());
  List<double> l1(10);
  std::list<double> l1_origin(10);
  ASSERT_EQ(l1.size(), l1_origin.size());
  List<std::string> l2(10);
  std::list<std::string> l2_origin(10);
  ASSERT_EQ(l2.size(), l2_origin.size());
  List<char> l3(10);
  std::list<char> l3_origin(10);
  ASSERT_EQ(l3.size(), l3_origin.size());
  List<size_t> l4(10);
  std::list<size_t> l4_origin(10);
  ASSERT_EQ(l4.size(), l4_origin.size());
  List<bool> l5(10);
  std::list<bool> l5_origin(10);
  ASSERT_EQ(l5.size(), l5_origin.size());
}

TEST(List, List_constructor3) {
  List<int> l{1, 2, 3, 4, 5};
  std::list<int> l_origin = {1, 2, 3, 4, 5};
  List<int>::Iterator iter = l.begin();
  std::list<int>::iterator iter_origin = l_origin.begin();
  ASSERT_EQ(l.size(), l_origin.size());
  for (size_t i = 0; i < l.size(); i++, ++iter, ++iter_origin) {
    ASSERT_EQ(*iter, *iter_origin);
  }

  List<double> l1{1.1, 2.1, 3.1, 4.1, 5.1};
  std::list<double> l1_origin{1.1, 2.1, 3.1, 4.1, 5.1};
  auto iter1 = l1.begin();
  auto iter1_origin = l1_origin.begin();
  ASSERT_EQ(l1.size(), l1_origin.size());
  for (size_t i = 0; i < l.size(); i++, ++iter1, ++iter1_origin) {
    ASSERT_EQ(*iter1, *iter1_origin);
  }

  List<std::string> l2{"Hello", "world"};
  std::list<std::string> l2_origin = {"Hello", "world"};
  auto iter2(l2.begin());
  auto iter2_origin(l2_origin.begin());
  ASSERT_EQ(l2.size(), l2_origin.size());
  for (size_t i = 0; i < l2.size(); i++, ++iter2, ++iter2_origin) {
    ASSERT_EQ(*iter2, *iter2_origin);
  }

  List<char> l3{'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
  std::list<char> l3_origin = {'H', 'e', 'l', 'l', 'o', ' ',
                               'w', 'o', 'r', 'l', 'd'};
  List<char>::Iterator iter3(l3.begin());
  std::list<char>::iterator iter3_origin(l3_origin.begin());
  ASSERT_EQ(l3.size(), l3_origin.size());
  for (size_t i = 0; i < l3.size(); i++, ++iter3, ++iter3_origin) {
    ASSERT_EQ(*iter3, *iter3_origin);
  }

  List<size_t> l4{10, 20, 30};
  std::list<size_t> l4_origin{10, 20, 30};
  ASSERT_EQ(l4.size(), l4_origin.size());
  List<size_t>::Iterator iter4 = (l4.begin());
  std::list<size_t>::iterator iter4_origin = (l4_origin.begin());
  for (size_t i = 0; i < l4.size(); i++, ++iter4, ++iter4_origin) {
    ASSERT_EQ(*iter4, *iter4_origin);
  }

  List<bool> l5{true, true, 0};
  std::list<bool> l5_origin = {true, true, 0};
  ASSERT_EQ(l5.size(), l5_origin.size());
  List<bool>::Iterator iter5 = (l5.begin());
  std::list<bool>::iterator iter5_origin = (l5_origin.begin());
  for (size_t i = 0; i < l5.size(); i++, ++iter5, ++iter5_origin) {
    ASSERT_EQ(*iter5, *iter5_origin);
  }
}

TEST(List, List_constructor4) {
  List<std::string> d{"a", "ab", "cd"};
  List<std::string> c(d);
  ASSERT_TRUE(c.equal(d));
  List<int> l{1, 2, 3, 4, 5};
  List<int> l_origin = l;
  ASSERT_TRUE(l_origin.equal(l));
  List<int> l1{1, 2, 3, 4, 5};
  List<int> l1_origin = l1;
  l1_origin.push_back(6);
  ASSERT_FALSE(l1_origin.equal(l1));
}

TEST(List, List_constructor5) {
  List<std::string> d{"a", "ab", "cd"};
  List<std::string> c(std::move(d));
  ASSERT_TRUE(d.empty());
  ASSERT_EQ(c.front(), "a");
  ASSERT_EQ(c.back(), "cd");
  ASSERT_EQ(c.size(), 3);

  List<int> l{1, 2, 3, 4, 5};
  List<int> l_origin = std::move(l);
  ASSERT_TRUE(l.empty());
  ASSERT_EQ(l_origin.front(), 1);
  ASSERT_EQ(l_origin.back(), 5);
  ASSERT_EQ(l_origin.size(), 5);
}

TEST(List, List_overload_operator_equal) {
  List<int> d{1, 2, 3, 4, 5};
  List<int> c;
  c = d;
  ASSERT_TRUE(c.equal(d));

  List<std::string> d1{"a", "ab", "cd"};
  List<std::string> c1;
  c1 = d1;
  ASSERT_TRUE(c1.equal(d1));
}

TEST(List, List_overload_operator_move_equal) {
  List<int> l{1, 2, 3, 4, 5};
  List<int> l_origin{1, 2, 3};
  l_origin = std::move(l);
  ASSERT_TRUE(l.empty());
  ASSERT_EQ(l_origin.front(), 1);
  ASSERT_EQ(l_origin.back(), 5);
  ASSERT_EQ(l_origin.size(), 5);
}

TEST(List, List_clear) {
  List<int> l{1, 2, 3, 4, 5};
  l.clear();
  ASSERT_TRUE(l.empty());
}

TEST(List, List_push_back_front) {
  List<int> test;
  test.push_back(1);
  test.push_back(11);
  test.push_back(2);
  test.push_back(3);
  List<int> result{1, 11, 2, 3};
  ASSERT_TRUE(test.equal(result));

  test.clear();
  test.push_front(1);
  test.push_front(11);
  test.push_front(2);
  test.push_front(3);
  List<int> result1{3, 2, 11, 1};
  ASSERT_TRUE(test.equal(result1));

  test.clear();
  test.push_front(100);
  test.push_front(1000);
  test.push_back(7);
  test.push_back(7);
  List<int> result2{1000, 100, 7, 7};
  ASSERT_TRUE(test.equal(result2));

  List<double> test1;
  test1.push_back(1.);
  test1.push_back(11.);
  test1.push_back(2.);
  test1.push_back(3.);
  List<double> result11{1.f, 11.f, 2.f, 3.f};
  ASSERT_TRUE(test1.equal(result11));

  test1.clear();
  test1.push_front(1.);
  test1.push_front(11.);
  test1.push_front(2.);
  test1.push_front(3.);
  List<double> result12{3.f, 2.f, 11.f, 1.f};
  ASSERT_TRUE(test1.equal(result12));

  test1.clear();
  test1.push_front(100.);
  test1.push_front(1000.);
  test1.push_back(7.);
  test1.push_back(7.);
  List<double> result22{1000.f, 100.f, 7.f, 7.f};
  ASSERT_TRUE(test1.equal(result22));
}

TEST(List, List_pop_back_front) {
  List<int> test;
  test.push_back(1);
  test.push_back(11);
  test.pop_back();
  List<int> result{1};
  ASSERT_TRUE(test.equal(result));

  List<int> test1;
  test1.push_back(1);
  test1.push_back(2);
  test1.push_back(3);
  test1.push_back(4);
  test1.push_back(5);
  test1.pop_back();
  test1.pop_front();
  test1.pop_back();
  List<int> result1{2, 3};
  ASSERT_TRUE(test1.equal(result1));
}

TEST(List, List_swap) {
  List<int> d{3, 1, 1, 3, 2, 2, 4, 5, 5};
  List<int> c{1, 3, 2, 4, 5, 5};
  d.swap(c);
  std::list<int> d1{3, 1, 1, 3, 2, 2, 4, 5, 5};
  std::list<int> c1{1, 3, 2, 4, 5, 5};
  d1.swap(c1);
  ASSERT_EQ(d.front(), d1.front());
  ASSERT_EQ(d.size(), d1.size());
}

TEST(List, List_equal) {
  List<int> d{1, 2, 3, 4, 5};
  List<int> d_origin{1, 2, 3, 4, 5};
  ASSERT_EQ(d.equal(d_origin), true);
  ASSERT_EQ(d_origin.equal(d), true);
}

TEST(List, List_end) {
  List<int> d{1, 2, 3, 4, 5};
  List<int>::Iterator iter = d.end();
  --iter;
  ASSERT_EQ(*iter, 5);
  List<int>::Iterator iter1(d.end());
  --iter1;
  ASSERT_EQ(*iter1, 5);
  List<int>::Iterator iter2(iter1);
  ASSERT_EQ(*iter2, 5);
}

TEST(List, List_erase) {
  List<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
  std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
  List<int>::Iterator iter_d = d.end();
  --iter_d;
  d.erase(iter_d);
  std::list<int>::iterator iter_c = c.end();
  --iter_c;
  c.erase(iter_c);
  ASSERT_EQ(d.back(), c.back());
}

TEST(List, List_erase1) {
  List<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
  std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
  List<int>::Iterator iter_d = d.begin();
  d.erase(iter_d);
  std::list<int>::iterator iter_c = c.begin();

  c.erase(iter_c);
  ASSERT_EQ(d.back(), c.back());
}

TEST(List, List_erase2) {
  List<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
  std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
  List<int>::Iterator iter_d = d.begin();
  ++iter_d;
  d.erase(iter_d);
  std::list<int>::iterator iter_c = c.begin();
  ++iter_c;
  c.erase(iter_c);
  ASSERT_EQ(d.back(), c.back());
}

TEST(List, List_insert1) {
  List<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
  std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
  List<int>::Iterator iter_d = d.begin();
  std::list<int>::iterator iter_c = c.begin();
  d.insert(iter_d, 1);
  c.insert(iter_c, 1);
  ASSERT_EQ(d.front(), c.front());
  ++iter_d;
  ++iter_c;
  d.insert(iter_d, 21);
  c.insert(iter_c, 21);
  ASSERT_EQ(d.size(), c.size());
}

TEST(List, List_insert2) {
  List<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
  std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
  List<int>::Iterator iter_d = d.end();
  std::list<int>::iterator iter_c = c.end();
  --iter_d;
  --iter_c;
  d.insert(iter_d, 1);
  c.insert(iter_c, 1);
  ASSERT_EQ(d.front(), c.front());
  --iter_d;
  --iter_c;
  d.insert(iter_d, 21);
  c.insert(iter_c, 21);
  ASSERT_EQ(d.size(), c.size());
}

TEST(List, List_splice1) {
  List<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> d_insert{100, 200, 300};
  List<int> d_result{100, 200, 300, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::list<int> c{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> c_insert{100, 200, 300};

  List<int>::ConstIterator iter_d = d.cbegin();
  std::list<int>::const_iterator iter_c = c.begin();

  d.splice(iter_d, d_insert);
  c.splice(iter_c, c_insert);
  ASSERT_TRUE(d.equal(d_result));

  ASSERT_EQ(d.front(), c.front());
  ASSERT_EQ(d.back(), c.back());
  ASSERT_EQ(d.size(), c.size());
}

TEST(List, List_splice2) {
  List<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> d_insert{100, 200, 300};
  List<int> d_result{1, 100, 200, 300, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::list<int> c{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> c_insert{100, 200, 300};

  List<int>::ConstIterator iter_d = d.cbegin();
  std::list<int>::const_iterator iter_c = c.begin();
  ++iter_d;
  ++iter_c;

  d.splice(iter_d, d_insert);
  c.splice(iter_c, c_insert);
  ASSERT_TRUE(d.equal(d_result));

  ASSERT_EQ(d.front(), c.front());
  ASSERT_EQ(d.back(), c.back());
  ASSERT_EQ(d.size(), c.size());
}

TEST(List, List_splice3) {
  List<int> d{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  List<int> d_insert{100, 200, 300};
  List<int> d_result{1, 2, 3, 4, 5, 6, 7, 8, 9, 100, 200, 300, 10};

  std::list<int> c{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> c_insert{100, 200, 300};

  List<int>::ConstIterator iter_d = d.cend();
  std::list<int>::const_iterator iter_c = c.end();
  --iter_d;
  --iter_c;

  d.splice(iter_d, d_insert);
  c.splice(iter_c, c_insert);
  ASSERT_TRUE(d.equal(d_result));

  ASSERT_EQ(d.front(), c.front());
  ASSERT_EQ(d.back(), c.back());
  ASSERT_EQ(d.size(), c.size());
}

TEST(List, List_sort) {
  List<int> d{7, 9, 3, 6, 1, 15, 4, 5, 0};
  std::list<int> c{7, 9, 3, 6, 1, 15, 4, 5, 0};
  d.sort();
  c.sort();
  ASSERT_EQ(d.front(), c.front());
  ASSERT_EQ(d.size(), c.size());
}

TEST(List, List_reverse) {
  List<int> d{1, 2, 3, 4, 5};
  d.reverse();
  std::list<int> d1{1, 2, 3, 4, 5};
  d1.reverse();
  ASSERT_EQ(d.front(), d1.front());
  ASSERT_EQ(d.back(), d1.back());
  ASSERT_EQ(d.size(), d1.size());
}

TEST(List, List_unique) {
  List<int> d{1, 1, 1, 3, 2, 2, 4, 5, 5};
  std::list<int> c{1, 1, 1, 3, 2, 2, 4, 5, 5};
  d.unique();
  c.unique();
  ASSERT_EQ(d.front(), c.front());
  ASSERT_EQ(d.size(), c.size());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
