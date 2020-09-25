// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <string>

#include "shared_ptr.hpp"

TEST(SharedPtr, EmptyConstructor) {
  SharedPtr<int> p;

  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, PointerConstructor) {
  SharedPtr<int> p(new int{5});

  ASSERT_EQ(*p.get(), 5);
  ASSERT_EQ(p.use_count(), 1);

  SharedPtr<int> v(new int{5});

  ASSERT_EQ(*v.get(), 5);
  ASSERT_EQ(v.use_count(), 1);
}
TEST(SharedPtr, CopyAssignment) {
  const SharedPtr p(new double{2.2});
  SharedPtr n(new double{3.4});

  n = p;

  ASSERT_EQ(*n, *p);
  ASSERT_EQ(n.use_count(), p.use_count());
}
TEST(SharedPtr, MoveAssignment) {
  SharedPtr p(new double{2.2});

  ASSERT_EQ(p.use_count(), 1);

  SharedPtr n(new double{3.4});

  n = std::move(p);

  ASSERT_EQ(*n, 2.2);
  ASSERT_EQ(n.use_count(), 1);

  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, CopyConstructor) {
  const SharedPtr p(new std::string{"Hello"});
  SharedPtr n(p);

  ASSERT_EQ(*n, *p);
  ASSERT_EQ(n.use_count(), p.use_count());
}
TEST(SharedPtr, MoveConstructor) {
  SharedPtr p(new std::string{"Hi"});
  SharedPtr n(std::move(p));

  ASSERT_EQ(*n, "Hi");
  ASSERT_EQ(n.use_count(), 1);

  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, Dereferencing) {
  SharedPtr p(new std::string{"Hi"});

  EXPECT_EQ(*p, "Hi");
}

TEST(SharedPtr, AccessThroughPointer) {
  SharedPtr p(new int{516237});
  SharedPtr v(new SharedPtr<int>{p});

  ASSERT_EQ(*v->get(), 516237);
}
TEST(SharedPtr, ResetEmpty) {
  SharedPtr p(new double{2.2});
  p.reset();
  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, ResetPointer) {
  SharedPtr p(new double{2.2});
  SharedPtr n(static_cast<const SharedPtr<double>>(p));
  p.reset(new double{3.4});
  ASSERT_EQ(*p, 3.4);
  ASSERT_EQ(p.use_count(), 1);
  ASSERT_EQ(*n, 2.2);
  ASSERT_EQ(p.use_count(), 1);
}
TEST(SharedPtr, Swap1) {
  SharedPtr ptr1{new int{1}};
  SharedPtr ptr2{new int{2}};

  ptr1.swap(ptr2);

  ASSERT_EQ(*(ptr2.get()), 1);
  ASSERT_EQ(ptr2.operator bool(), true);
  ASSERT_EQ(ptr2.use_count(), 1);

  ASSERT_EQ(*(ptr1.get()), 2);
  ASSERT_EQ(ptr2.operator bool(), true);
  ASSERT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtr, Swap2) {
  SharedPtr ptr1{new int{567}};
  SharedPtr ptr2{new int{123}};
  SharedPtr ptr3 = ptr1;

  ptr2.swap(ptr1);

  ASSERT_EQ(ptr2.use_count(), 2);
  ASSERT_EQ(ptr1.use_count(), 1);
}
TEST(SharedPtr, Get) {
  SharedPtr ptr1{new int{1}};
  *ptr1 = 2;

  ASSERT_EQ(*ptr1, 2);
  ASSERT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtr, BoolCheck)  //+
{
  SharedPtr<int> ptr1{};

  ASSERT_EQ(ptr1.operator bool(), false);

  SharedPtr ptr2(new int{23235});

  ASSERT_EQ(ptr2.operator bool(), true);
}
//TEST(SharedPtr, ThisCopyAssigment) {
//  SharedPtr ptr1{new int{5555}};
//  ptr1 = ptr1;
//  EXPECT_EQ(*ptr1, 5555);
//}
//TEST(SharedPtr, ThisMoveAssigment) {
//  SharedPtr ptr1{new int{5555}};
//  ptr1 = std::move(ptr1);
//  EXPECT_EQ(*ptr1, 5555);
//}
