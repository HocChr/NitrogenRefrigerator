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

  NitrogenRefrigoratorKernel::Vial dataSet1{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 5, 20, 12, 33},
    12,
    "Christian",
    "Remark",
    "HumanCells"
  };
  NitrogenRefrigoratorKernel::Vial dataSet2{
    Date{2021, 5, 21, 8, 11},
    Date{2021, 5, 9, 12, 33},
    9,
    "Sabine",
    "TTT",
    "CatCells"
  };
  NitrogenRefrigoratorKernel::Vial dataSet3{
    Date{2021, 5, 21, 13, 53},
    Date{2021, 8, 20, 12, 2},
    24,
    "Jule",
    "H",
    "Rats"
  };

  auto casette1 = std::make_unique<NitrogenRefrigoratorKernel::Casette>(2, 3);
  casette1->add(0, 0, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet1));
  casette1->add(1, 0, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet2));
  casette1->add(1, 2, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet3));

  auto casette2 = std::make_unique<NitrogenRefrigoratorKernel::Casette>(4, 3);
  casette2->add(1, 0, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet1));
  casette2->add(2, 1, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet2));
  casette2->add(3, 2, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet3));

  std::vector<std::unique_ptr<NitrogenRefrigoratorKernel::Casette>> casettes;
  casettes.push_back(std::move(casette1));
  casettes.push_back(std::make_unique<NitrogenRefrigoratorKernel::Casette>(3, 3));
  casettes.push_back(std::make_unique<NitrogenRefrigoratorKernel::Casette>(6, 7));
  casettes.push_back(nullptr);
  casettes.push_back(std::move(casette2));
  casettes.push_back(nullptr);
  casettes.push_back(std::make_unique<NitrogenRefrigoratorKernel::Casette>(2, 1));

  NitrogenRefrigoratorKernel::CasetteStack casetteStack("My Rack");
  casetteStack.insertCasettes(std::move(casettes));

  auto casette3 = std::make_unique<NitrogenRefrigoratorKernel::Casette>(2, 3);
  casette3->add(0, 0, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet1));
  casette3->add(1, 0, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet2));
  casette3->add(1, 2, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet3));

  auto casette4 = std::make_unique<NitrogenRefrigoratorKernel::Casette>(4, 3);
  casette4->add(1, 0, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet1));
  casette4->add(2, 1, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet2));
  casette4->add(3, 2, std::make_unique<NitrogenRefrigoratorKernel::Vial>(dataSet3));

  std::vector<std::unique_ptr<Casette>> casettes2;
  casettes2.push_back(std::make_unique<NitrogenRefrigoratorKernel::Casette>(1, 3));
  casettes2.push_back(std::move(casette3));
  casettes2.push_back(nullptr);
  casettes2.push_back(std::make_unique<NitrogenRefrigoratorKernel::Casette>(8, 7));
  casettes2.push_back(nullptr);
  casettes2.push_back(nullptr);
  casettes2.push_back(std::move(casette4));

  NitrogenRefrigoratorKernel::CasetteStack casetteStack2("My Rack 2");
  casetteStack2.insertCasettes(std::move(casettes2));

  NitrogenRefrigoratorKernel::NitrogenRefrigorator refrigerator;
  refrigerator.appendRack(std::move(casetteStack));
  //refrigerator.appendRack(std::move(casetteStack2));

  // act
  storage.storeNitrogenRefrigerator("refrigeratorStackUnitTestDefault.json", refrigerator);
  NitrogenRefrigoratorKernel::NitrogenRefrigorator storedRefrigerator =
      storage.getStoredNitrogenRefrigerator("refrigeratorStackUnitTestDefault.json");

  // assert
  EXPECT_EQ(storedRefrigerator.size() == refrigerator.size(), true);

  for (unsigned i = 0; i < storedRefrigerator.size(); ++i)
  {
    EXPECT_EQ(storedRefrigerator.getRack(i) == refrigerator.getRack(i), true);
  }
}


#endif // JSONSTORAGETEST_H
