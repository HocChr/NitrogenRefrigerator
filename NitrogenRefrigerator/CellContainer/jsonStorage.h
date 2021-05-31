#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include "cellcontainer.h"

class JsonStorage final : public NitrogenRefrigoratorKernel::IDataStorage
{
public:

  NitrogenRefrigoratorKernel::NitrogenRefrigerator getStoredNitrogenRefrigerator(const std::string& filepath) const;

  NitrogenRefrigoratorKernel::NitrogenRefrigerator getStoredNitrogenRefrigerator() const override;

  void createAndSafeDefaultData(const std::string& filepath, unsigned dimensionX, unsigned dimensionY) const;

  void storeNitrogenRefrigerator(const NitrogenRefrigoratorKernel::NitrogenRefrigerator&) const override{};
};

#endif // JSONSTORAGE_H

