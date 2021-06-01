#include "jsonStorage.h"

#include "json.hpp"
#include <fstream> // std::ofstream
#include <iomanip> // std::setw

using namespace NitrogenRefrigoratorKernel;
using json = nlohmann::json;


Casette JsonStorage::getStoredNitrogenRefrigerator() const
{
  return getStoredNitrogenRefrigerator(_storageFile);
}

void JsonStorage::storeNitrogenRefrigerator(NitrogenRefrigoratorKernel::Casette &r) const
{
  storeNitrogenRefrigerator(_storageFile, r);
}

Casette JsonStorage::getStoredNitrogenRefrigerator(const std::string &filepath) const
{
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

  try
  {

    unsigned dimensionX = j["dimensionX"];
    unsigned dimensionY = j["dimensionY"];
    int dataSize = j["data"].size();

    if(dataSize != dimensionX * dimensionY)
    {
      throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: dimension mismatch"));
    }

    Casette refrigerator(dimensionX, dimensionY);

    for(const auto& item : j["data"])
    {
      Date dateOfEntry = dateFromString(item["dateOfEntry"]);
      Date ageOfCells = dateFromString(item["ageOfCells"]);
      int numberOfCells = item["numberOfCells"];
      std::string userName = item["userName"];
      std::string remark = item["remark"];
      std::string celltype = item["cellType"];
      unsigned posX = item["positionX"];
      unsigned posY = item["positionY"];

      Vial vial(dateOfEntry, ageOfCells, numberOfCells, userName, remark, celltype);
      refrigerator(posX, posY) = vial;
    }

    return refrigerator;
  }
  catch (std::runtime_error& e)
  {
    throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: no valid Vial data"));
  }
  return Casette(0, 0);
}

void JsonStorage::storeNitrogenRefrigerator(const std::string &filepath,
                                            NitrogenRefrigoratorKernel::Casette& refrigerator) const
{  
  json j;
  unsigned dimX, dimY = 0;

  refrigerator.getDimensions(dimX, dimY);
  j["dimensionX"] = dimX;
  j["dimensionY"] = dimY;

  auto jsonObjects = json::array();
  for(unsigned i = 0; i < dimX; ++i)
  {
    for(unsigned j = 0; j < dimY; ++j)
    {
      jsonObjects.push_back({
                              { "positionX", i },
                              { "positionY", j },
                              { "dateOfEntry", dateToString(refrigerator(i, j).dateOfEntry()) },
                              { "ageOfCells", dateToString(refrigerator(i, j).ageOfCells()) },
                              { "numberOfCells", refrigerator(i, j).numberOfCells() },
                              { "userName", refrigerator(i, j).userName() },
                              { "remark", refrigerator(i, j).remark() },
                              { "cellType", refrigerator(i, j).cellType() }
                            });
    }
  }

  j["data"] = jsonObjects;

  std::ofstream o(filepath);
  o << std::setw(4) << j << std::endl;
}

