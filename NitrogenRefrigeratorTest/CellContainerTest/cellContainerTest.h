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

// - test Casette -------------------------------------------------------------

TEST(NitrogenRefrigeratorTest, CasetteNoDataSpecified)
{
  // arrange
  Casette refrigerator(10, 10);
  const Vial* vial;

  // act
  vial = refrigerator(5, 5);

  // assert
  EXPECT_EQ(vial == nullptr, true);
}

TEST(NitrogenRefrigeratorTest, CasetteOutOfRange)
{
  // arrange
  Casette refrigerator(10, 10);

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

TEST(NitrogenRefrigeratorTest, CasetteOutOfRangeNegative)
{
  // arrange
  Casette refrigerator(10, 10);

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

TEST(NitrogenRefrigeratorTest, CasetteAddData)
{
  // arrange
  Casette refrigerator(2, 3);
  Vial dataSet1{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 20, 12, 33},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };

  // act
  refrigerator.add(0, 1, std::make_unique<Vial>(dataSet1));
  refrigerator.add(1, 2, std::make_unique<Vial>(dataSet1));

  // assert
  EXPECT_EQ(refrigerator(0, 0) == nullptr, true);
  EXPECT_EQ(refrigerator(1, 0) == nullptr, true);
  EXPECT_EQ(*refrigerator(0, 1) == dataSet1, true);
  EXPECT_EQ(refrigerator(1, 1) == nullptr, true);
  EXPECT_EQ(refrigerator(0, 2) == nullptr, true);
  EXPECT_EQ(*refrigerator(1, 2) == dataSet1, true);
}

TEST(NitrogenRefrigeratorTest, CasetteGetDimensions)
{
  // arrange
  Casette refrigerator(2, 3);
  unsigned x, y;

  // act
  refrigerator.getDimensions(x, y);

  // assert
  EXPECT_EQ(x, 2);
  EXPECT_EQ(y, 3);
}

TEST(NitrogenRefrigeratorTest, CasetteGetOperatorEquals)
{
  // arrange
  Casette refrigerator(2, 3);
  Casette refrigerator2(2, 3);

  // act & assert
  EXPECT_EQ(refrigerator == refrigerator2, true);
}

TEST(NitrogenRefrigeratorTest, CasetteGetOperatorEqualsNotEqual)
{
  // arrange
  Casette refrigerator(2, 3);
  Casette refrigerator2(3, 2);

  // act & assert
  EXPECT_EQ(refrigerator == refrigerator2, false);
}

TEST(NitrogenRefrigeratorTest, CasetteGetOperatorEqualsNotEqualOfValue)
{
  // arrange
  Casette refrigerator(2, 3);
  Casette refrigerator2(3, 2);

  refrigerator.add(1, 1, std::make_unique<Vial>());

  // act & assert
  EXPECT_EQ(refrigerator == refrigerator2, false);
}

// - test CasetteStack --------------------------------------------------------

TEST(NitrogenRefrigeratorTest, CasetteStackInitWithNullptr)
{
  // arrange
  CasetteStack casetteStack("Test Stack");

  // assert
  EXPECT_EQ(casetteStack.size(), 0);
}


TEST(NitrogenRefrigeratorTest, CasetteStackInitValid)
{
  // arrange
  CasetteStack casetteStack("");
  casetteStack.insertCasette(std::make_unique<Casette>(2, 3), 0);
  unsigned x, y;

  // act
  const Casette* casette = casetteStack.getCasette(0);
  casette->getDimensions(x, y);

  // assert
  EXPECT_EQ(casetteStack.size(), 1);
  EXPECT_EQ(x, 2);
  EXPECT_EQ(y, 3);
}

TEST(NitrogenRefrigeratorTest, CasetteStackInsertCasettes)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));

  CasetteStack casetteStack("");

  unsigned dimX0, dimX1, dimX2, dimY0, dimY1, dimY2 = 0;

  // act
  casetteStack.insertCasettes(std::move(casettes));

  // assert
  casetteStack.getCasette(0)->getDimensions(dimX0, dimY0);
  casetteStack.getCasette(1)->getDimensions(dimX1, dimY1);
  casetteStack.getCasette(2)->getDimensions(dimX2, dimY2);

  EXPECT_EQ(casetteStack.size(), 3);
  EXPECT_EQ(dimX0, 2);
  EXPECT_EQ(dimY0, 3);
  EXPECT_EQ(dimX1, 3);
  EXPECT_EQ(dimY1, 3);
  EXPECT_EQ(dimX2, 6);
  EXPECT_EQ(dimY2, 7);
}

TEST(NitrogenRefrigeratorTest, CasetteStackInsertCasette)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  unsigned dimX0, dimX1, dimX2, dimY0, dimY1, dimY2, dimX3, dimY3 = 0;

  // act
  casetteStack.insertCasette(std::make_unique<Casette>(1, 1), 1);

  // assert
  casetteStack.getCasette(0)->getDimensions(dimX0, dimY0);
  casetteStack.getCasette(1)->getDimensions(dimX3, dimY3);
  casetteStack.getCasette(2)->getDimensions(dimX1, dimY1);
  casetteStack.getCasette(3)->getDimensions(dimX2, dimY2);

  EXPECT_EQ(casetteStack.size(), 4);
  EXPECT_EQ(dimX0, 2);
  EXPECT_EQ(dimY0, 3);
  EXPECT_EQ(dimX3, 1);
  EXPECT_EQ(dimY3, 1);
  EXPECT_EQ(dimX1, 3);
  EXPECT_EQ(dimY1, 3);
  EXPECT_EQ(dimX2, 6);
  EXPECT_EQ(dimY2, 7);
}


TEST(NitrogenRefrigeratorTest, CasetteStackInsertCasetteIndexOutOfRange)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  unsigned dimX0, dimX1, dimX2, dimY0, dimY1, dimY2 = 0;

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   casetteStack.insertCasette(std::make_unique<Casette>(1, 1), 12);
                 }
                 catch( const std::out_of_range& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ("insertCasette: index out of range", e.what() );
                   throw;
                 }
               }, std::out_of_range );


  // assert
  casetteStack.getCasette(0)->getDimensions(dimX0, dimY0);
  casetteStack.getCasette(1)->getDimensions(dimX1, dimY1);
  casetteStack.getCasette(2)->getDimensions(dimX2, dimY2);

  EXPECT_EQ(casetteStack.size(), 3);
  EXPECT_EQ(dimX0, 2);
  EXPECT_EQ(dimY0, 3);
  EXPECT_EQ(dimX1, 3);
  EXPECT_EQ(dimY1, 3);
  EXPECT_EQ(dimX2, 6);
  EXPECT_EQ(dimY2, 7);
}


TEST(NitrogenRefrigeratorTest, CasetteStackInsertSomeNullptr)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  unsigned dimX, dimY=  0;

  // act
  casetteStack.insertCasette(std::make_unique<Casette>(6, 7), 2);
  casetteStack.insertCasette(nullptr, 5);

  // assert
  EXPECT_EQ(casetteStack.size(), 7);

  casetteStack.getCasette(0)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 2);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(1)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 3);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(2)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 6);
  EXPECT_EQ(dimY, 7);

  EXPECT_EQ(casetteStack.getCasette(3) == nullptr, true);

  casetteStack.getCasette(4)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 1);
  EXPECT_EQ(dimY, 1);

  EXPECT_EQ(casetteStack.getCasette(5) == nullptr, true);

  casetteStack.getCasette(6)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 2);
  EXPECT_EQ(dimY, 1);
}


TEST(NitrogenRefrigeratorTest, CasetteStackRemoveCasettesIndexOutOfRange)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  unsigned dimX, dimY=  0;

  // act
  casetteStack.removeCasette(6);

  // act & assert
  EXPECT_THROW({
                 try
                 {
                   casetteStack.removeCasette(6);
                 }
                 catch( const std::out_of_range& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ("removeCasette: index out of range", e.what() );
                   throw;
                 }
               }, std::out_of_range );

  // assert
  EXPECT_EQ(casetteStack.size(), 6);

  casetteStack.getCasette(0)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 2);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(1)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 3);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(2)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 6);
  EXPECT_EQ(dimY, 7);

  EXPECT_EQ(casetteStack.getCasette(3) == nullptr, true);

  casetteStack.getCasette(4)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 1);
  EXPECT_EQ(dimY, 1);
}

TEST(NitrogenRefrigeratorTest, CasetteStackRemoveCasettes)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  unsigned dimX, dimY=  0;

  // act
  casetteStack.removeCasette(4);
  casetteStack.removeCasette(4);

  // assert
  EXPECT_EQ(casetteStack.size(), 5);

  casetteStack.getCasette(0)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 2);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(1)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 3);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(2)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 6);
  EXPECT_EQ(dimY, 7);

  EXPECT_EQ(casetteStack.getCasette(3) == nullptr, true);

  casetteStack.getCasette(4)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 2);
  EXPECT_EQ(dimY, 1);
}

TEST(NitrogenRefrigeratorTest, CasetteStackGetCasetteIndexOutOfRange)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  unsigned dimX, dimY=  0;

  // act
  casetteStack.removeCasette(4);
  casetteStack.removeCasette(4);

  // assert
  EXPECT_EQ(casetteStack.size(), 5);

  casetteStack.getCasette(0)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 2);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(1)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 3);
  EXPECT_EQ(dimY, 3);

  casetteStack.getCasette(2)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 6);
  EXPECT_EQ(dimY, 7);

  EXPECT_EQ(casetteStack.getCasette(3) == nullptr, true);

  casetteStack.getCasette(4)->getDimensions(dimX, dimY);
  EXPECT_EQ(dimX, 2);
  EXPECT_EQ(dimY, 1);


  // act & assert
  EXPECT_THROW({
                 try
                 {
                   casetteStack.getCasette(6);
                 }
                 catch( const std::out_of_range& e )
                 {
                   // and this tests that it has the correct message
                   EXPECT_STREQ("getCasette: index out of range", e.what() );
                   throw;
                 }
               }, std::out_of_range );
}

TEST(NitrogenRefrigeratorTest, CasetteStackOperatorEquals)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  std::vector<std::unique_ptr<Casette>> casettes2;
  casettes2.push_back(std::make_unique<Casette>(2, 3));
  casettes2.push_back(std::make_unique<Casette>(3, 3));
  casettes2.push_back(std::make_unique<Casette>(6, 7));
  casettes2.push_back(nullptr);
  casettes2.push_back(std::make_unique<Casette>(1, 1));
  casettes2.push_back(nullptr);
  casettes2.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack2("");
  casetteStack2.insertCasettes(std::move(casettes2));


  // act & assert
  EXPECT_EQ(casetteStack == casetteStack2, true);
}

TEST(NitrogenRefrigeratorTest, CasetteStackOperatorEqualsNotEqual)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  std::vector<std::unique_ptr<Casette>> casettes2;
  casettes2.push_back(std::make_unique<Casette>(2, 3));
  casettes2.push_back(std::make_unique<Casette>(3, 3));
  casettes2.push_back(nullptr);
  casettes2.push_back(std::make_unique<Casette>(1, 1));
  casettes2.push_back(nullptr);
  casettes2.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack2("");
  casetteStack2.insertCasettes(std::move(casettes2));

  // act & assert
  EXPECT_EQ(casetteStack == casetteStack2, false);
}

TEST(NitrogenRefrigeratorTest, CasetteStackName)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("Bli bla Blub");
  casetteStack.insertCasettes(std::move(casettes));

  // act & assert
  EXPECT_EQ(casetteStack.name() == "Bli bla Blub", true);
}

// - test Nitrogen Refrigerator -----------------------------------------------

TEST(NitrogenRefrigeratorTest, NitroRefrigeratorConstruction)
{
  // arrange & act
  NitrogenRefrigorator refrigerator;

  // assert
  EXPECT_EQ(refrigerator.size(), 0);
}

TEST(NitrogenRefrigeratorTest, NitroRefrigeratorAppend)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("");
  casetteStack.insertCasettes(std::move(casettes));

  NitrogenRefrigorator refrigerator;

  // act
  refrigerator.appendRack(std::move(casetteStack));

  // assert
  EXPECT_EQ(refrigerator.size(), 1);
}

TEST(NitrogenRefrigeratorTest, NitroRefrigeratorGetRack)
{
  // arrange
  std::vector<std::unique_ptr<Casette>> casettes;
  casettes.push_back(std::make_unique<Casette>(2, 3));
  casettes.push_back(std::make_unique<Casette>(3, 3));
  casettes.push_back(std::make_unique<Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(1, 1));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack("My Rack");
  casetteStack.insertCasettes(std::move(casettes));

  std::vector<std::unique_ptr<Casette>> casettes2;
  casettes2.push_back(std::make_unique<Casette>(2, 3));
  casettes2.push_back(std::make_unique<Casette>(3, 3));
  casettes2.push_back(std::make_unique<Casette>(6, 7));
  casettes2.push_back(nullptr);
  casettes2.push_back(std::make_unique<Casette>(1, 1));
  casettes2.push_back(nullptr);
  casettes2.push_back(std::make_unique<Casette>(2, 1));

  CasetteStack casetteStack2("My Rack");
  casetteStack2.insertCasettes(std::move(casettes2));

  NitrogenRefrigorator refrigerator;
  refrigerator.appendRack(std::move(casetteStack));

  // act
  auto & rack = refrigerator.getRack("My Rack");

  // assert
  EXPECT_EQ(rack == casetteStack2, true);
}



//class DataStorageMock : public IDataStorage
//{
//private:
//  Casette _refrigerator(0 ,0 );
//  unsigned _dimX, _dimY;
//public:
//
//  DataStorageMock(CasetteStack&& refrigerator) //:  _refrigerator(refrigerator)
//  {}
//
//  Casette getStoredNitrogenRefrigerator() const override
//  {
//    return _refrigerator;
//  }
//
//  void storeNitrogenRefrigerator(CasetteStack&) const override{};
//};

#endif // CELLCONTAINERTEST_H
