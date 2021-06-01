#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include "cellcontainer.h"

class JsonStorage final : public NitrogenRefrigoratorKernel::IDataStorage
{
  std::string _storageFile = "NitrogenRefrigerator.json";

public:

  NitrogenRefrigoratorKernel::NitrogenRefrigerator getStoredNitrogenRefrigerator() const override;
  void storeNitrogenRefrigerator(NitrogenRefrigoratorKernel::NitrogenRefrigerator&) const override;

  // --- additional funtions not declared by the interface, for convinence ---
  NitrogenRefrigoratorKernel::NitrogenRefrigerator getStoredNitrogenRefrigerator(const std::string& filepath) const;
  void storeNitrogenRefrigerator(const std::string& filepath, NitrogenRefrigoratorKernel::NitrogenRefrigerator&) const;
};

#endif // JSONSTORAGE_H

