#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include "cellcontainer.h"

class JsonStorage final : public NitrogenRefrigoratorKernel::IDataStorage
{
  std::string _storageFile = "NitrogenRefrigerator.json";

public:

  NitrogenRefrigoratorKernel::CasetteStack getStoredNitrogenRefrigerator() const override;
  void storeNitrogenRefrigerator(NitrogenRefrigoratorKernel::CasetteStack&) const override;

  // --- additional functions not declared by the interface, for convinence ---
  NitrogenRefrigoratorKernel::CasetteStack getStoredNitrogenRefrigerator(const std::string& filepath) const;
  void storeNitrogenRefrigerator(const std::string& filepath, NitrogenRefrigoratorKernel::NitrogenRefrigorator&) const;
};

#endif // JSONSTORAGE_H

