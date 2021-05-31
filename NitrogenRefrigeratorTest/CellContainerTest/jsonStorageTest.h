#ifndef JSONSTORAGETEST_H
#define JSONSTORAGETEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../NitrogenRefrigerator/CellContainer/jsonStorage.h"

using namespace testing;

TEST(NitrogenRefrigeratorTest, JsonStorageCreateAndSafeDefaultData)
{
  // arrange
  JsonStorage storage;
  unsigned dimX, dimY;
  Vial defaultVial;

  // act
  storage.createAndSafeDefaultData("default64x64.json", 64, 64);
  NitrogenRefrigerator defaultRefrigerator = storage.getStoredNitrogenRefrigerator("default64x64.json");
  defaultRefrigerator.getDimensions(dimX, dimY);

  // assert
  EXPECT_EQ(dimX, 64);
  EXPECT_EQ(dimY, 64);
  for(unsigned i = 0; i < 64; ++i)
  {
    for(unsigned j = 0; j < 64; ++j)
    {
      EXPECT_EQ(defaultRefrigerator(i, j) == defaultVial, true);
    }
  }
}


#endif // JSONSTORAGETEST_H
