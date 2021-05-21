#ifndef TST_TTT_H
#define TST_TTT_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(NitrogenRefrigeratorTest, ttt)
{
  EXPECT_EQ(1, 1);
  ASSERT_THAT(0, Eq(0));
}

#endif // TST_TTT_H
