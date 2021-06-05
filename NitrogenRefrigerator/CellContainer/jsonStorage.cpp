#include "jsonStorage.h"

#include "json.hpp"
#include <fstream> // std::ofstream
#include <iomanip> // std::setw

using namespace NitrogenRefrigoratorKernel;
using json = nlohmann::json;


NitrogenRefrigorator JsonStorage::getStoredNitrogenRefrigerator() const
{
  return getStoredNitrogenRefrigerator(_storageFile);
}

void JsonStorage::storeNitrogenRefrigerator(NitrogenRefrigoratorKernel::NitrogenRefrigorator &r) const
{
  storeNitrogenRefrigerator(_storageFile, r);
}

NitrogenRefrigorator JsonStorage::getStoredNitrogenRefrigerator(const std::string &filepath) const
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
    NitrogenRefrigorator refrigerator;

    for(const auto& rack : j["data"])
    {
      unsigned index = rack[0];
      std::string name = rack[1];

      CasetteStack casetteStack(std::move(name));

      for(const auto& stackItem : rack[2])
      {
        unsigned dimX = stackItem[0];
        unsigned dimY = stackItem[1];

        auto& casette = stackItem[2];
        if (casette == nullptr)
        {
          casetteStack.pushBack(nullptr);
          continue;
        }

        auto c = std::make_unique<Casette>(dimX, dimY);
        for(const auto &item : casette)
        {
          unsigned posX = item["positionX"];
          unsigned posY = item["positionY"];
          if (item["isNull"] == true)
          {
            c->add(posX, posY, nullptr);
            continue;
          }

          Date dateOfEntry = dateFromString(item["dateOfEntry"]);
          Date ageOfCells = dateFromString(item["ageOfCells"]);
          int numberOfCells = item["numberOfCells"];
          std::string userName = item["userName"];
          std::string remark = item["remark"];
          std::string celltype = item["cellType"];

          auto vial = std::make_unique<Vial>(dateOfEntry, ageOfCells, numberOfCells, userName, remark, celltype);
          c->add(posX, posY, std::move(vial));
        }
        casetteStack.pushBack(std::move(c));
      }
      refrigerator.insertRack(std::move(casetteStack), index);
    }
    return refrigerator;
  }
  catch (std::runtime_error& e)
  {
    throw std::runtime_error(std::string("getStoredNitrogenRefrigerator: no valid data"));
  }
  return NitrogenRefrigorator();
}

void JsonStorage::storeNitrogenRefrigerator(const std::string &filepath,
                                            NitrogenRefrigoratorKernel::NitrogenRefrigorator& refrigerator) const
{  
  json j;
  unsigned dimX, dimY = 0;

  auto refrigeratorJsonObjects = json::array();

  for(unsigned index = 0; index < refrigerator.size(); ++index)
  {
    auto& rack = refrigerator.getRack(index);
    auto casetteStackJsonObjects = json::array();

    for(unsigned c = 0; c < rack.size(); ++c)
    {
      if(rack.getCasette(c) == nullptr)
      {
        casetteStackJsonObjects.push_back( { 0, 0, nullptr } );
        continue;
      }

      Casette& casette = *rack.getCasette(c);

      casette.getDimensions(dimX, dimY);

      auto casetteJsonObjects = json::array();
      for(unsigned i = 0; i < dimX; ++i)
      {
        for(unsigned j = 0; j < dimY; ++j)
        {
          if(casette(i, j) == nullptr)
          {
            casetteJsonObjects.push_back({
                                    { "positionX", i },
                                    { "positionY", j },
                                    { "isNull" , true }
                                  });
            continue;
          }
          casetteJsonObjects.push_back({
                                  { "positionX", i },
                                  { "positionY", j },
                                  { "isNull" , false },
                                  { "dateOfEntry", dateToString(casette(i, j)->dateOfEntry()) },
                                  { "ageOfCells", dateToString(casette(i, j)->ageOfCells()) },
                                  { "numberOfCells", casette(i, j)->numberOfCells() },
                                  { "userName", casette(i, j)->userName() },
                                  { "remark", casette(i, j)->remark() },
                                  { "cellType", casette(i, j)->cellType() }
                                });
        }
      }
      casetteStackJsonObjects.push_back( { dimX, dimY, casetteJsonObjects });
    }

    refrigeratorJsonObjects.push_back({ index, rack.name(), casetteStackJsonObjects });
  }

  j["data"] = refrigeratorJsonObjects;

  std::ofstream o(filepath);
  o << std::setw(4) << j << std::endl;
}

