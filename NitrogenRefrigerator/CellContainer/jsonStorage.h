#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include "cellcontainer.h"

class JsonStorage final : public NitrogenRefrigoratorKernel::IDataStorage
{
  std::string _storageFile = "NitrogenRefrigerator.json";

public:

  NitrogenRefrigoratorKernel::Casette getStoredNitrogenRefrigerator() const override;
  void storeNitrogenRefrigerator(NitrogenRefrigoratorKernel::Casette&) const override;

  // --- additional funtions not declared by the interface, for convinence ---
  NitrogenRefrigoratorKernel::Casette getStoredNitrogenRefrigerator(const std::string& filepath) const;
  void storeNitrogenRefrigerator(const std::string& filepath, NitrogenRefrigoratorKernel::Casette&) const;
};

#endif // JSONSTORAGE_H

