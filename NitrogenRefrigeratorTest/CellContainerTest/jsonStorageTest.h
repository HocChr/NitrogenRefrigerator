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
  NitrogenRefrigoratorKernel::CasetteStack defaultRefrigerator;

  defaultRefrigerator.insertCasette(std::make_unique<Casette>(3, 3), 0);
  defaultRefrigerator.insertCasette(std::make_unique<Casette>(1, 3), 1);
  defaultRefrigerator.insertCasette(nullptr, 2);
  defaultRefrigerator.insertCasette(std::make_unique<Casette>(3, 1), 3);
  defaultRefrigerator.insertCasette(std::make_unique<Casette>(3, 3), 4);

  // act
  storage.storeNitrogenRefrigerator("refrigeratorStackUnitTestDefault.json", defaultRefrigerator);
  NitrogenRefrigoratorKernel::CasetteStack storedRefrigerator =
      storage.getStoredNitrogenRefrigerator("refrigeratorStackUnitTestDefault.json");

  // assert
  EXPECT_EQ(storedRefrigerator == defaultRefrigerator, true);
}


#endif // JSONSTORAGETEST_H
