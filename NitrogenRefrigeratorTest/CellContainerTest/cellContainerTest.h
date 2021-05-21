#ifndef CELLCONTAINERTEST_H
#define CELLCONTAINERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../../NitrogenRefrigerator/CellContainer/cellcontainer.h"

using namespace testing;
using namespace NitrogenRefrigoratorKernel;

// test struct date -----------------------------------------------------------

TEST(NitrogenRefrigeratorTest, DateHourSmaller)
{
  // arrange
  Date date1{2021, 5, 21, 15, 26};
  Date date2{2021, 5, 21, 16, 45};

  // assert
  EXPECT_EQ(date1 < date2, true);
  EXPECT_EQ(date1 > date2, false);
  EXPECT_EQ(date1 == date2, false);
}

TEST(NitrogenRefrigeratorTest, DateOperatorEqual)
{
  // arrange
  Date date1{2021, 5, 21, 15, 26};
  Date date2{2021, 5, 21, 15, 26};

  // assert
  EXPECT_EQ(date1 < date2, false);
  EXPECT_EQ(date1 > date2, false);
  EXPECT_EQ(date1 == date2, true);
}

TEST(NitrogenRefrigeratorTest, DateDayGreater)
{
  // arrange
  Date date1{2021, 5, 21, 15, 26};
  Date date2{2021, 5, 20, 15, 26};

  // assert
  EXPECT_EQ(date1 < date2, false);
  EXPECT_EQ(date1 > date2, true);
  EXPECT_EQ(date1 == date2, false);
}

TEST(NitrogenRefrigeratorTest, DateYearGreater)
{
  // arrange
  Date date1{2021, 5, 21, 15, 26};
  Date date2{2020, 5, 21, 15, 26};

  // assert
  EXPECT_EQ(date1 < date2, false);
  EXPECT_EQ(date1 > date2, true);
  EXPECT_EQ(date1 == date2, false);
}

TEST(NitrogenRefrigeratorTest, DateYearSmaller)
{
  // arrange
  Date date1{2019, 5, 21, 15, 26};
  Date date2{2020, 5, 21, 15, 26};

  // assert
  EXPECT_EQ(date1 < date2, true);
  EXPECT_EQ(date1 > date2, false);
  EXPECT_EQ(date1 == date2, false);
}

TEST(NitrogenRefrigeratorTest, DateMinuteGreaterHourSmaller)
{
  // arrange
  Date date1{2020, 5, 21, 16, 26};
  Date date2{2020, 5, 21, 15, 8};

  // assert
  EXPECT_EQ(date1 < date2, false);
  EXPECT_EQ(date1 > date2, true);
  EXPECT_EQ(date1 == date2, false);
}

// test class CellContainer ---------------------------------------------------

TEST(NitrogenRefrigeratorTest, CellContainerWithNoEntry)
{
  // arrange
  CellContainer cellContainer;

  // assert
  EXPECT_EQ(cellContainer.getNumberOfDatasets(), 0);
  EXPECT_EQ(cellContainer.getNumberOfCells(), 0);
}


TEST(NitrogenRefrigeratorTest, CellContainerWithOneEntry)
{
  // arrange
  CellContainer cellContainer;

  Dataset dataSet{
    Date{2021, 5, 21, 13, 53},
    12,
    "Christian"
  };

  // act
  cellContainer.addDataset(std::move(dataSet));

  // assert
  EXPECT_EQ(cellContainer.getNumberOfDatasets(), 1);
  EXPECT_EQ(cellContainer.getNumberOfCells(), 12);
}


TEST(NitrogenRefrigeratorTest, CellContainerWithThreeEntries)
{
  // arrange
  CellContainer cellContainer;

  Dataset dataSet1{
    Date{2021, 5, 21, 15, 26},
    12,
    "Christian"
  };

  Dataset dataSet2{
    Date{2021, 5, 21, 15, 26},
    20,
    "Sabine"
  };

  Dataset dataSet3{
    Date{2021, 5, 21, 15, 27},
    -8,
    "Jule"
  };

  // act
  cellContainer.addDataset(std::move(dataSet1));
  cellContainer.addDataset(std::move(dataSet2));
  cellContainer.addDataset(std::move(dataSet3));

  // assert
  EXPECT_EQ(cellContainer.getNumberOfDatasets(), 3);
  EXPECT_EQ(cellContainer.getNumberOfCells(), 24);
}


TEST(NitrogenRefrigeratorTest, CellContainerWithThreeEntriesAndNegativeCellNumber)
{
  // arrange
  CellContainer cellContainer;

  Dataset dataSet1{
    Date{2021, 5, 21, 15, 26},
    12,
    "Christian"
  };

  Dataset dataSet2{
    Date{2021, 5, 21, 15, 26},
    -20,
    "Sabine"
  };

  Dataset dataSet3{
    Date{2021, 5, 21, 15, 27},
    -8,
    "Jule"
  };

  // act
  cellContainer.addDataset(std::move(dataSet1));
  cellContainer.addDataset(std::move(dataSet2));
  cellContainer.addDataset(std::move(dataSet3));

  // assert
  EXPECT_EQ(cellContainer.getNumberOfDatasets(), 3);
  EXPECT_EQ(cellContainer.getNumberOfCells(), -16);
}


TEST(NitrogenRefrigeratorTest, GetDatasetByDate)
{
  // arrange
  CellContainer cellContainer;
  Date date{2021, 5, 21, 15, 26};

  Dataset dataSet1{
    date,
    12,
    "Christian"
  };

  Dataset dataSet2{
    date,
    -20,
    "Sabine"
  };

  Dataset dataSet3{
    Date{2021, 5, 21, 15, 27},
    -8,
    "Jule"
  };

  cellContainer.addDataset(std::move(dataSet1));
  cellContainer.addDataset(std::move(dataSet2));
  cellContainer.addDataset(std::move(dataSet3));

  // act
  auto dataSet = cellContainer.getDatasetByDate(date);

  // assert
  EXPECT_EQ(dataSet.size(), 2);
  EXPECT_EQ(dataSet[0].UserName == "Jule", false);
  EXPECT_EQ(dataSet[1].UserName == "Jule", false);
  EXPECT_EQ(dataSet[0].UserName == "Sabine" || dataSet[0].UserName == "Christian", true);
  EXPECT_EQ(dataSet[1].UserName == "Sabine" || dataSet[1].UserName == "Christian", true);
  EXPECT_EQ((dataSet[0].NumberOfCells + dataSet[1].NumberOfCells) == -8, true);
}


TEST(NitrogenRefrigeratorTest, GetDatasetByRemark)
{
  // arrange
  CellContainer cellContainer;
  Date date{2021, 5, 21, 15, 26};

  Dataset dataSet1{
    date,
    12,
    "Christian",
    "Blablub"
  };

  Dataset dataSet2{
    date,
    -20,
    "Sabine",
    "Bliblub"
  };

  Dataset dataSet3{
    Date{2021, 5, 21, 15, 27},
    -8,
    "Jule",
    "Blablub"
  };

  cellContainer.addDataset(std::move(dataSet1));
  cellContainer.addDataset(std::move(dataSet2));
  cellContainer.addDataset(std::move(dataSet3));

  // act
  auto dataSet = cellContainer.getDatasetByRemark("Blablub");

  // assert
  EXPECT_EQ(dataSet.size(), 2);
  EXPECT_EQ(dataSet[0].UserName == "Sabine", false);
  EXPECT_EQ(dataSet[1].UserName == "Sabine", false);
  EXPECT_EQ(dataSet[0].UserName == "Jule" || dataSet[0].UserName == "Christian", true);
  EXPECT_EQ(dataSet[1].UserName == "Jule" || dataSet[1].UserName == "Christian", true);
  EXPECT_EQ((dataSet[0].NumberOfCells + dataSet[1].NumberOfCells) == 4, true);
}


TEST(NitrogenRefrigeratorTest, GetDatasetByName)
{
  // arrange
  CellContainer cellContainer;
  Date date{2021, 5, 21, 15, 26};

  Dataset dataSet1{
    date,
    12,
    "Christian",
    "Blablub"
  };

  Dataset dataSet2{
    date,
    -20,
    "Sabine",
    "Bliblub"
  };

  Dataset dataSet3{
    Date{2021, 5, 21, 15, 27},
    -8,
    "Jule",
    "Blablub"
  };

  cellContainer.addDataset(std::move(dataSet1));
  cellContainer.addDataset(std::move(dataSet2));
  cellContainer.addDataset(std::move(dataSet3));

  // act
  auto dataSet = cellContainer.getDatasetByUserName("Sabine");

  // assert
  EXPECT_EQ(dataSet.size(), 1);
  EXPECT_EQ(dataSet[0].UserName == "Sabine", true);
  EXPECT_EQ(dataSet[0].DateOfEntry == date, true);
}

#endif // CELLCONTAINERTEST_H
