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
  NitrogenRefrigoratorKernel::Casette defaultRefrigerator(64, 64);

  // act
  storage.storeNitrogenRefrigerator("default64x64.json", defaultRefrigerator);
  Casette storedRefrigerator = storage.getStoredNitrogenRefrigerator("default64x64.json");
  storedRefrigerator.getDimensions(dimX, dimY);

  // assert
  EXPECT_EQ(dimX, 64);
  EXPECT_EQ(dimY, 64);
  for(unsigned i = 0; i < 64; ++i)
  {
    for(unsigned j = 0; j < 64; ++j)
    {
      EXPECT_EQ(storedRefrigerator(i, j) == defaultRefrigerator(i, j), true);
    }
  }
}


#endif // JSONSTORAGETEST_H
