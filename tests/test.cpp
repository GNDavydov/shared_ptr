// Copyright 2021 GNDavydov

#include <gtest/gtest.h>

#include "shared_ptr.hpp"

TEST(Shared_ptr, Init) {
    SharedPtr<int> shp_1;
    SharedPtr<int> shp_2(nullptr);
    SharedPtr<int> shp_3(new int(5));

    int* pInt = new int(7);
    SharedPtr<int> shp_4(pInt);

    EXPECT_EQ(shp_1.get(), nullptr);
    EXPECT_EQ(shp_2.get(), nullptr);
    EXPECT_EQ(*shp_3, 5);
    EXPECT_EQ(*shp_4, 7);
}

TEST(Shared_ptr, Copy) {
    SharedPtr<int> shp_1;
    SharedPtr<int> shp_2(shp_1);
    EXPECT_EQ(shp_1.get(), nullptr);

    EXPECT_EQ(shp_2.get(), nullptr);

    SharedPtr<int> shp_3(new int(5));
    SharedPtr<int> shp_4(shp_3);
    EXPECT_EQ(*shp_3, 5);
    EXPECT_EQ(*shp_4, 5);

    shp_1 = shp_3;
    EXPECT_EQ(*shp_1, 5);
    EXPECT_EQ(*shp_3, 5);
}

TEST(Shared_ptr, Move) {
    SharedPtr<int> shp_1;
    SharedPtr<int> shp_2(std::move(shp_1));
    EXPECT_EQ(shp_1.get(), nullptr);
    EXPECT_EQ(shp_2.get(), nullptr);

    SharedPtr<int> shp_3(new int(5));
    SharedPtr<int> shp_4(std::move(shp_3));
    EXPECT_EQ(shp_3.get(), nullptr);
    EXPECT_EQ(*shp_4, 5);

    shp_1 = std::move(shp_4);
    EXPECT_EQ(*shp_1, 5);
    EXPECT_EQ(shp_4.get(), nullptr);
}

TEST(Shared_ptr, UseCount) {
    SharedPtr<int> shp_1;
    SharedPtr<int> shp_2(new int(3));
    EXPECT_EQ(shp_1.use_count(), 0);
    EXPECT_EQ(shp_2.use_count(), 1);

    shp_1 = shp_2;
    EXPECT_EQ(shp_1.use_count(), 2);
    EXPECT_EQ(shp_2.use_count(), 2);

    {
        SharedPtr<int> shp_3(shp_1);
        EXPECT_EQ(shp_1.use_count(), 3);
        EXPECT_EQ(shp_2.use_count(), 3);
    }

    EXPECT_EQ(shp_1.use_count(), 2);
    EXPECT_EQ(shp_2.use_count(), 2);
}

TEST(Shared_ptr, Swap) {
    SharedPtr<int> shp_1(new int(7));
    SharedPtr<int> shp_2(new int(5));
    shp_1.swap(shp_2);
    EXPECT_EQ(*shp_1, 5);
    EXPECT_EQ(*shp_2, 7);
}

TEST(Shared_ptr, Reset) {
    SharedPtr<int> shp_1(new int(7));
    SharedPtr<int> shp_2(shp_1);

    shp_1.reset();
    EXPECT_EQ(shp_1.use_count(), 0);
    EXPECT_EQ(shp_1.get(), nullptr);
    EXPECT_EQ(shp_2.use_count(), 1);
    EXPECT_EQ(*shp_2, 7);

    shp_1.reset(new int(5));
    EXPECT_EQ(shp_1.use_count(), 1);
    EXPECT_EQ(*shp_1, 5);
}

TEST(Shared_ptr, Bool) {
    SharedPtr<int> shp_1(new int(7));
    SharedPtr<int> shp_2(nullptr);
    SharedPtr<int> shp_3(shp_1);

    EXPECT_TRUE(shp_1.operator bool());
    EXPECT_FALSE(shp_2.operator bool());
    EXPECT_TRUE(shp_3.operator bool());

    shp_3.reset();
    EXPECT_FALSE(shp_3.operator bool());
}

TEST(Shared_ptr, Get) {
    int* p_int = new int(7);
    SharedPtr<int> shp_1(p_int);

    EXPECT_EQ(p_int, shp_1.get());
    EXPECT_EQ(shp_1.operator->(), shp_1.get());
}

TEST(Shared_ptr, Comparison) {
    SharedPtr<int> shp_1(new int(7));
    SharedPtr<int> shp_2(shp_1);

    EXPECT_TRUE(shp_1 == shp_2);

    shp_1.reset();
    EXPECT_TRUE(shp_1 != shp_2);
    EXPECT_TRUE(shp_1 == nullptr);
}

