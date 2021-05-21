#ifndef TST_NITROGENREFRIGERATORTEST_H
#define TST_NITROGENREFRIGERATORTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorTest)
{
  EXPECT_EQ(1, 1);
  ASSERT_THAT(0, Eq(0));
}

#endif // TST_NITROGENREFRIGERATORTEST_H
