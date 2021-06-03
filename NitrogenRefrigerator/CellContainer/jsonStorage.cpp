#include "jsonStorage.h"

#include "json.hpp"
#include <fstream> // std::ofstream
#include <iomanip> // std::setw

using namespace NitrogenRefrigoratorKernel;
using json = nlohmann::json;


CasetteStack JsonStorage::getStoredNitrogenRefrigerator() const
{
  return getStoredNitrogenRefrigerator(_storageFile);
}

void JsonStorage::storeNitrogenRefrigerator(NitrogenRefrigoratorKernel::CasetteStack &r) const
{
  storeNitrogenRefrigerator(_storageFile, r);
}

CasetteStack JsonStorage::getStoredNitrogenRefrigerator(const std::string &filepath) const
{
  //std::ifstream i(filepath);
  //json j;
  //
  //try
  //{
  //  j = json::parse(i);
  //}
  //catch (json::parse_error& ex)
  //{
  //  throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: no valid json Format"));
  //}
  //
  //try
  //{
  //
  //  unsigned dimensionX = j["dimensionX"];
  //  unsigned dimensionY = j["dimensionY"];
  //  int dataSize = j["data"].size();
  //
  //  if(dataSize != dimensionX * dimensionY)
  //  {
  //    throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: dimension mismatch"));
  //  }
  //
  //  CasetteStack refrigerator;
  //
  //  for(const auto& item : j["data"])
  //  {
  //    Date dateOfEntry = dateFromString(item["dateOfEntry"]);
  //    Date ageOfCells = dateFromString(item["ageOfCells"]);
  //    int numberOfCells = item["numberOfCells"];
  //    std::string userName = item["userName"];
  //    std::string remark = item["remark"];
  //    std::string celltype = item["cellType"];
  //    unsigned posX = item["positionX"];
  //    unsigned posY = item["positionY"];
  //
  //    Vial vial(dateOfEntry, ageOfCells, numberOfCells, userName, remark, celltype);
  //    refrigerator(posX, posY) = vial;
  //  }
  //
  //  return refrigerator;
  //}
  //catch (std::runtime_error& e)
  //{
  //  throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: no valid Vial data"));
  //}
  return CasetteStack();
}

void JsonStorage::storeNitrogenRefrigerator(const std::string &filepath,
                                            NitrogenRefrigoratorKernel::CasetteStack& refrigerator) const
{  
  json j;
  unsigned dimX, dimY = 0;

  auto casetteStackJsonObjects = json::array();

  for(unsigned c = 0; c < refrigerator.size(); ++c)
  {
    if(refrigerator.getCasette(c) == nullptr)
    {
      casetteStackJsonObjects.push_back( { nullptr, 0, 0 } );
      continue;
    }

    Casette& casette = *refrigerator.getCasette(c);

    casette.getDimensions(dimX, dimY);

    auto casetteJsonObjects = json::array();
    for(unsigned i = 0; i < dimX; ++i)
    {
      for(unsigned j = 0; j < dimY; ++j)
      {
        casetteJsonObjects.push_back({
                                { "positionX", i },
                                { "positionY", j },
                                { "dateOfEntry", dateToString(casette(i, j).dateOfEntry()) },
                                { "ageOfCells", dateToString(casette(i, j).ageOfCells()) },
                                { "numberOfCells", casette(i, j).numberOfCells() },
                                { "userName", casette(i, j).userName() },
                                { "remark", casette(i, j).remark() },
                                { "cellType", casette(i, j).cellType() }
                              });
      }
    }

    casetteStackJsonObjects.push_back( { casetteJsonObjects, dimX, dimY } );
  }

  j["data"] = casetteStackJsonObjects;

  std::ofstream o(filepath);
  o << std::setw(4) << j << std::endl;
}

