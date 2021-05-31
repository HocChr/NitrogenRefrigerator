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

  try {
    Date dateOfEntry = dateFromString(j["dateOfEntry"]);
    Date ageOfCells = dateFromString(j["ageOfCells"]);
    int numberOfCells = j["numberOfCells"];
    std::string userName = j["userName"];
    std::string remark = j["remark"];
    std::string celltype = j["cellType"];

    Vial vial(dateOfEntry, ageOfCells, numberOfCells, userName, remark, celltype);
  }
  catch (std::runtime_error& e)
  {
    throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: no valid Vial data"));
  }

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
  j["dimensionX"] = dimensionX;
  j["dimensionY"] = dimensionY;

  auto jsonObjects = json::array();
  for(unsigned i = 0; i < dimensionX; ++i)
  {
    for(unsigned j = 0; j < dimensionY; ++j)
    {
      jsonObjects.push_back({
                              dateToString(defaultVial.dateOfEntry()),
                              dateToString(defaultVial.ageOfCells()),
                              defaultVial.numberOfCells(),
                              defaultVial.userName(),
                              defaultVial.remark(),
                              defaultVial.cellType()});
    }
  }

  j["data"] = jsonObjects;

  std::ofstream o(filepath);
  o << std::setw(4) << j << std::endl;
}

