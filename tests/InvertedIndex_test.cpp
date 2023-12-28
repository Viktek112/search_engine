#include "../include/InvertedIndex.h"
#include "gtest/gtest.h"

TEST(wordCleaningTest, HandlesZeroInput) {
EXPECT_EQ(wordCleaning(""), "");
}

TEST(wordCleaningTest, HandlesPositiveInput) {
EXPECT_EQ(wordCleaning("!@#$%^&*()_+{}-=[]{};':\"\\|,<.>/?`~test!@#$%^&*()_+{}-=[]{};':\"\\|,<.>/?`~"), "test");
EXPECT_EQ(wordCleaning("&&test's&&"), "test's");
}
