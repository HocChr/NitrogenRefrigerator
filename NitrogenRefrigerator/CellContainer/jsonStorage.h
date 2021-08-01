#ifndef JSONSTORAGE_H
#define JSONSTORAGE_H

#include "cellcontainer.h"

class JsonStorage final : public NitrogenRefrigoratorKernel::IDataStorage
{
public:

  // --- throws std::runtime_error if file not exits or if the format not valid
  NitrogenRefrigoratorKernel::NitrogenRefrigorator
  getStoredNitrogenRefrigerator(const std::string& filepath) const override;

  void
  storeNitrogenRefrigerator(const std::string& filepath,
                            NitrogenRefrigoratorKernel::NitrogenRefrigorator&) const override;
};

#endif // JSONSTORAGE_H

