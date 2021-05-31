#include "jsonStorage.h"

#include "json.hpp"
#include <fstream> // std::ofstream
#include <iomanip> // std::setw

using namespace NitrogenRefrigoratorKernel;
using json = nlohmann::json;

NitrogenRefrigerator JsonStorage::getStoredNitrogenRefrigerator(const std::string &filepath) const
{
  NitrogenRefrigerator refrigerator(0, 0);

  std::ifstream i(filepath);
  json j;

  try
  {
      j = json::parse(i);
  }
  catch (json::parse_error& ex)
  {
    throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: no valid json Format"));
  }

  //j["dateOfEntry"] = defaultVial.dateOfEntry();
  //j["ageOfCells"] = defaultVial.ageOfCells();
  int numberOfCells = j["numberOfCells"];
  std::string remark = j["remark"];
  std::string celltype = j["cellType"];
  Vial vial;

  return refrigerator;
}

NitrogenRefrigerator JsonStorage::getStoredNitrogenRefrigerator() const
{
  NitrogenRefrigerator refrigerator(0, 0);

  return refrigerator;
}

void JsonStorage::createAndSafeDefaultData(const std::string &filepath, unsigned dimensionX, unsigned dimensionY) const
{
  Vial defaultVial;

  json j;

  //j["dateOfEntry"] = defaultVial.dateOfEntry();
  //j["ageOfCells"] = defaultVial.ageOfCells();
  j["numberOfCells"] = defaultVial.numberOfCells();
  j["remark"] = defaultVial.remark();
  j["cellType"] = defaultVial.cellType();

  std::ofstream o(filepath);
  o << std::setw(4) << j << std::endl;
}

