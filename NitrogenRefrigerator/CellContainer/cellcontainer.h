#ifndef CELLCONTAINER_H
#define CELLCONTAINER_H

#include <string>
#include <vector>
#include <memory>

namespace NitrogenRefrigoratorKernel {

// - defines a Datastructure that represents a date ---------------------------

struct Date
{
  unsigned short Year = 0;
  unsigned short Month = 0;
  unsigned short Day = 0;
  unsigned short Hour = 0;
  unsigned short Minute = 0;

  bool operator< (const Date  &date) const;
  bool operator> (const Date  &date) const;
  bool operator== (const Date  &date) const;
};

// - defines the vial ---------------------------------------------------------

class Vial final
{
  Date _dateOfEntry;
  Date _ageOfCells;
  int _numberOfCells = 0;
  std::string _userName = "";
  std::string _remark = "";
  std::string _cellType = "";

public:

  bool operator== (const Vial &dataSet) const;

  Vial() = default;

  Vial(Date dateOfEntry,
       Date ageOfCells,
       int numberOfCells,
       std::string userName,
       std::string remark,
       std::string cellType);
};

//- this is the Nitrogen Refrigerator Class -----------------------------------

class NitrogenRefrigerator final
{
  std::vector<Vial> inner_;
  unsigned int dimx_, dimy_;

public:

  NitrogenRefrigerator() = delete;

  NitrogenRefrigerator (unsigned int dimx, unsigned int dimy);

  // throws std::out_of_range whe out of range
  Vial& operator()(unsigned int x, unsigned int y);
};

//- this is the controller that manages the nitrogen refrigerator -------------

// - this defines the interface for the data strorage -----

class IDataStorage
{
public:
  virtual std::vector<Vial> getStoredVials() const = 0;
  virtual void saveVials(std::vector<Vial>) const = 0;
};

// - this defines the NitrogenRefrigeratorController itself

class NitrogenRefrigeratorController final
{

public:

  NitrogenRefrigeratorController(std::unique_ptr<IDataStorage> dataStorage);

  // todo: implement the controller

private:

  std::unique_ptr<IDataStorage> _dataStorage;
};

} // namespace NitrogenRefrigoratorKernel

#endif // CELLCONTAINER_H
