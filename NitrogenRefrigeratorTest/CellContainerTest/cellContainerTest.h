#ifndef CELLCONTAINERTEST_H
#define CELLCONTAINERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../NitrogenRefrigerator/CellContainer/cellcontainer.h"

using namespace testing;

TEST(NitrogenRefrigeratorTest, MyTest)
{
  // arrange
  CellContainer cellContainer;

  CellContainer::Dataset dataSet{
    CellContainer::Date{2021, 5, 21, 13, 53},
    12,
    "Christian"
  };

  // act
  cellContainer.addDataset(std::move(dataSet));

  // assert
  EXPECT_EQ(cellContainer.getNumberOfDatasets(), 1);
  EXPECT_EQ(cellContainer.getNumberOfCells(), 12);
}

#endif // CELLCONTAINERTEST_H
