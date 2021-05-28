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

// test struct Dataset --------------------------------------------------------

TEST(NitrogenRefrigeratorTest, DatasetEqual)
{
  // arrange
  Vial dataSet1{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 21, 13, 53},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };

  Vial dataSet2{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 21, 13, 53},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };

  Vial dataSet3{
    Date{2021, 5, 21, 15, 26},
    Date{2021, 5, 21, 15, 26},
    20,
    "Sabine",
    "No Remark",
    "CanineCells"
  };

  // assert
  EXPECT_EQ(dataSet1 == dataSet1, true);
  EXPECT_EQ(dataSet2 == dataSet2, true);
  EXPECT_EQ(dataSet2 == dataSet1, true);
  EXPECT_EQ(dataSet3 == dataSet1, false);
  EXPECT_EQ(dataSet3 == dataSet2, false);
}

// - test Nitrogen Refrigerator -----------------------------------------------

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorNoDataSpecified)
{
  // arrange
  NitrogenRefrigerator refrigerator(10, 10);
  Vial vial, vialDefault;

  // act
  vial = refrigerator(5, 5);

  // assert
  EXPECT_EQ(vial == vialDefault, true);
}

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorOutOfRange)
{
  // arrange
  NitrogenRefrigerator refrigerator(10, 10);

  // act and assert
  EXPECT_THROW({
      try
      {
          refrigerator(10, 10);
      }
      catch( const std::out_of_range& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Matrix indices out of range", e.what() );
          throw;
      }
  }, std::out_of_range );
}

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorOutOfRangeNegative)
{
  // arrange
  NitrogenRefrigerator refrigerator(10, 10);

  // act and assert
  EXPECT_THROW({
      try
      {
          refrigerator(-5, -5);
      }
      catch( const std::out_of_range& e )
      {
          // and this tests that it has the correct message
          EXPECT_STREQ( "Matrix indices out of range", e.what() );
          throw;
      }
  }, std::out_of_range );
}

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorAddData)
{
  // arrange
  NitrogenRefrigerator refrigerator(2, 3);
  Vial dataSet1{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 20, 12, 33},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };
  Vial dataSetDefault;

  // act
  refrigerator(0, 1) = dataSet1;
  refrigerator(1, 2) = dataSet1;

  // assert
  EXPECT_EQ(refrigerator(0, 0) == dataSetDefault, true);
  EXPECT_EQ(refrigerator(1, 0) == dataSetDefault, true);
  EXPECT_EQ(refrigerator(0, 1) == dataSet1, true);
  EXPECT_EQ(refrigerator(1, 1) == dataSetDefault, true);
  EXPECT_EQ(refrigerator(0, 2) == dataSetDefault, true);
  EXPECT_EQ(refrigerator(1, 2) == dataSet1, true);
}

// - test Nitrogen Refrigerator Controller ------------------------------------

class DataStorageTest : public IDataStorage
{
private:
  std::vector<Vial> _vials;
  unsigned _dimX, _dimY;
public:

  DataStorageTest(unsigned dimX, unsigned dimY, std::vector<Vial>&& vials) : _dimX(dimX), _dimY(dimY), _vials(vials)
  {}

  std::vector<Vial> getStoredVials() const override
  {
    return _vials;
  }

  void saveVials(std::vector<Vial>) const override{};

  std::pair<unsigned int, unsigned int> getRefrigeratorDimensions() const override
  {
    std::pair<unsigned, unsigned> out(_dimX, _dimY);
    return out;
  };
};

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorController2x2)
{
  // arrange
  // arrange
  Vial dataSet1{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 21, 13, 53},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };

  Vial dataSet2{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 21, 13, 53},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };

  Vial dataSet3{
    Date{2021, 5, 21, 15, 26},
    Date{2021, 5, 21, 15, 26},
    20,
    "Sabine",
    "No Remark",
    "CanineCells"
  };

  Vial dataSet4{
    Date{2021, 5, 21, 22, 45},
    Date{2020, 5, 14, 10, 12},
    20,
    "Jule",
    "I Like Cells",
    "FishCells"
  };

  std::vector<Vial> vials {dataSet1, dataSet2, dataSet3, dataSet4};
  std::unique_ptr<IDataStorage> storage = std::make_unique<DataStorageTest>(2, 2, std::move(vials));

  // act
  NitrogenRefrigeratorController controller(std::move(storage));
  auto errors = controller.getErrors();
  auto cellsWithMultipleVials = controller.getCellsWithMultipleVials();

  // assert
  EXPECT_EQ(errors.size(), 0);
  EXPECT_EQ(cellsWithMultipleVials.size(), 0);
}

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorController2x2DimensionSmallerNumberVials)
{
  // arrange
  // arrange
  Vial dataSet1{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 21, 13, 53},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };

  Vial dataSet2{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 21, 13, 53},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };

  Vial dataSet3{
    Date{2021, 5, 21, 15, 26},
    Date{2021, 5, 21, 15, 26},
    20,
    "Sabine",
    "No Remark",
    "CanineCells"
  };

  Vial dataSet4{
    Date{2021, 5, 21, 22, 45},
    Date{2020, 5, 14, 10, 12},
    20,
    "Jule",
    "I Like Cells",
    "FishCells"
  };

  std::vector<Vial> vials {dataSet1, dataSet2, dataSet3, dataSet4};
  std::unique_ptr<IDataStorage> storage = std::make_unique<DataStorageTest>(1, 2, std::move(vials));

  // act
  NitrogenRefrigeratorController controller(std::move(storage));
  auto errors = controller.getErrors();
  auto cellsWithMultipleVials = controller.getCellsWithMultipleVials();

  // assert
  EXPECT_EQ(errors.size(), 1);
  EXPECT_EQ(errors.at(0), NitrogenRefrigeratorErrorTypes::NUMBER_CELLS_DONT_EQUAL_DIMENSIONS);
  EXPECT_EQ(cellsWithMultipleVials.size(), 0);
}


#endif // CELLCONTAINERTEST_H
