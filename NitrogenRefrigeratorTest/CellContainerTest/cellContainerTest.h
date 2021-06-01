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

TEST(NitrogenRefrigeratorTest, DateFromString)
{
  // arrange
  const std::string d = "2021-05-30T18:55:00";

  // act
  const Date date = dateFromString(d);

  // assert
  EXPECT_EQ(date.Year, 2021);
  EXPECT_EQ(date.Month, 5);
  EXPECT_EQ(date.Day, 30);
  EXPECT_EQ(date.Hour, 18);
  EXPECT_EQ(date.Minute, 55);
}

TEST(NitrogenRefrigeratorTest, DateFromStringCatchInvalidYearFormat)
{
  // arrange
  const std::string d = "21-05-30T18:55:00";

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   const Date date = dateFromString(d);
                 }
                 catch( const std::runtime_error& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ( "dateFromString: invalid date format", e.what() );
                   throw;
                 }
               }, std::runtime_error );
}

TEST(NitrogenRefrigeratorTest, DateFromStringCatchInvalidYearFormat2)
{
  // arrange
  const std::string d = "3021-05-30T18:55:00";

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   const Date date = dateFromString(d);
                 }
                 catch( const std::runtime_error& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ( "dateFromString: invalid date format", e.what() );
                   throw;
                 }
               }, std::runtime_error );
}

TEST(NitrogenRefrigeratorTest, DateFromStringCatchInvalidDelimiter)
{
  // arrange
  const std::string d = "2021-05:30T18:55:00";

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   const Date date = dateFromString(d);
                 }
                 catch( const std::runtime_error& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ( "dateFromString: invalid date format", e.what() );
                   throw;
                 }
               }, std::runtime_error );
}

TEST(NitrogenRefrigeratorTest, DateFromStringCatchInvalidDelimiter2)
{
  // arrange
  const std::string d = "2021-05-30T18:55";

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   const Date date = dateFromString(d);
                 }
                 catch( const std::runtime_error& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ( "dateFromString: invalid date format", e.what() );
                   throw;
                 }
               }, std::runtime_error );
}

TEST(NitrogenRefrigeratorTest, DateFromStringCatchInvalidDelimiter3)
{
  // arrange
  const std::string d = "2021-05-30T18::55:00";

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   const Date date = dateFromString(d);
                 }
                 catch( const std::runtime_error& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ( "dateFromString: invalid date format", e.what() );
                   throw;
                 }
               }, std::runtime_error );
}

TEST(NitrogenRefrigeratorTest, DateFromStringInvalidYearSmall)
{
  // arrange
  const std::string d = "1799-05-30T18:55:00";

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   const Date date = dateFromString(d);
                 }
                 catch( const std::runtime_error& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ( "dateFromString: invalid date format", e.what() );
                   throw;
                 }
               }, std::runtime_error );
}

TEST(NitrogenRefrigeratorTest, DateFromStringInvalidYearHigh)
{
  // arrange
  const std::string d = "3000-05-30T18:55:00";

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   const Date date = dateFromString(d);
                 }
                 catch( const std::runtime_error& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ( "dateFromString: invalid date format", e.what() );
                   throw;
                 }
               }, std::runtime_error );
}

TEST(NitrogenRefrigeratorTest, DateToString)
{
  // arrange
  Date date{2021, 5, 30, 18, 55};

  // act
  std::string d = dateToString(date);

  // assert
  EXPECT_EQ(d == "2021-5-30T18:55:00", true);
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

TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorGetDimensions)
{
  // arrange
  NitrogenRefrigerator refrigerator(2, 3);
  unsigned x, y;

  // act
  refrigerator.getDimensions(x, y);

  // assert
  EXPECT_EQ(x, 2);
  EXPECT_EQ(y, 3);
}

// - test Nitrogen Refrigerator Controller ------------------------------------

class DataStorageMock : public IDataStorage
{
private:
  NitrogenRefrigerator _refrigerator;
  unsigned _dimX, _dimY;
public:

  DataStorageMock(NitrogenRefrigerator&& refrigerator) :  _refrigerator(refrigerator)
  {}

  NitrogenRefrigerator getStoredNitrogenRefrigerator() const override
  {
    return _refrigerator;
  }

  void storeNitrogenRefrigerator(NitrogenRefrigerator&) const override{};
};


TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorControllerInitWithNullptr)
{
  // arrange
  NitrogenRefrigeratorController controller(nullptr);
  unsigned x, y;

  // act
  const NitrogenRefrigerator& refrigerator = controller.getNitrogenRefrigerator();
  refrigerator.getDimensions(x, y);

  // assert
  EXPECT_EQ(x, 0);
  EXPECT_EQ(y, 0);
}


TEST(NitrogenRefrigeratorTest, NitrogenRefrigeratorControllerInitValid)
{
  // arrange
  NitrogenRefrigerator r(2, 3);
  std::unique_ptr<IDataStorage> storage = std::make_unique<DataStorageMock>(std::move(r));
  NitrogenRefrigeratorController controller(std::move(storage));
  unsigned x, y;

  // act
  const NitrogenRefrigerator& refrigerator = controller.getNitrogenRefrigerator();
  refrigerator.getDimensions(x, y);

  // assert
  EXPECT_EQ(x, 2);
  EXPECT_EQ(y, 3);
}

#endif // CELLCONTAINERTEST_H
