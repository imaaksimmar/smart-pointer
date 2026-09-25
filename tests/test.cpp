#include <gtest/gtest.h>
#include "../include/UniquePtr.hpp"
#include "../include/SharedPtr.hpp"
#include "../include/DynamicArray.hpp"


TEST(UniquePtrTest, Constructor) {
    UniquePtr<int> p(new int(42));
    EXPECT_EQ(*p, 42);
}

TEST(UniquePtrTest, MoveTransfer) {
    UniquePtr<int> a(new int(7));
    UniquePtr<int> b(std::move(a));
    EXPECT_EQ(a.Get(), nullptr);
    EXPECT_EQ(*b, 7);
}

TEST(UniquePtrTest, ArrayIndexAccess) {
    UniquePtr<int[]> arr(new int[3]{1, 2, 3});
    arr[1] = 20;
    EXPECT_EQ(arr[1], 20);
}


TEST(SharedPtrTest, Constructor) {
    SharedPtr<int> s(new int(10));
    EXPECT_EQ(*s, 10);
    EXPECT_EQ(s.UseCount(), 1U);
}

TEST(SharedPtrTest, UseCount) {
    SharedPtr<int> a(new int(1));
    SharedPtr<int> b = a;
    EXPECT_EQ(a.UseCount(), 2U);
}

TEST(SharedPtrTest, Move) {
    SharedPtr<int> a(new int(1));
    SharedPtr<int> b(std::move(a));
    EXPECT_EQ(b.UseCount(), 1U);
    EXPECT_EQ(a.UseCount(), 0U);
}


TEST(DynamicArrayTest, ConstructorSize) {
    DynamicArray<int> a(5);
    EXPECT_EQ(a.GetSize(), 5U);
}

TEST(DynamicArrayTest, IndexOperator) {
    DynamicArray<int> a(3);
    a[0] = 10;
    EXPECT_EQ(a[0], 10);
}

TEST(DynamicArrayTest, DeepCopy) {
    DynamicArray<int> a(2);
    a[0] = 1;
    DynamicArray<int> b(a);
    b[0] = 999;
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(b[0], 999);
}

TEST(DynamicArrayTest, Move) {
    DynamicArray<int> a(2);
    DynamicArray<int> b(std::move(a));
    EXPECT_EQ(a.GetSize(), 0U);
}

TEST(DynamicArrayTest, Resize) {
    DynamicArray<int> a(2);
    a[0] = 1;
    a[1] = 2;
    a.Resize(4);
    EXPECT_EQ(a.GetSize(), 4U);
    EXPECT_EQ(a[0], 1);
}

TEST(DynamicArrayTest, OutOfRangeThrows) {
    DynamicArray<int> a(3);
    EXPECT_THROW(a[3], std::out_of_range);
}