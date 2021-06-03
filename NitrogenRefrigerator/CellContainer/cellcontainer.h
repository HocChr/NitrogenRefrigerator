#ifndef CELLCONTAINER_H
#define CELLCONTAINER_H

#include <string>
#include <vector>
#include <memory>

namespace NitrogenRefrigoratorKernel {

// - defines a Datastructure that represents a date ---------------------------

struct Date
{
  unsigned short Year = 1900;
  unsigned short Month = 1;
  unsigned short Day = 1;
  unsigned short Hour = 0;
  unsigned short Minute = 0;

  bool operator< (const Date  &date) const;
  bool operator> (const Date  &date) const;
  bool operator== (const Date  &date) const;
};

// valid string format: yyyy-mm-ddThh:mm:ss
// max year: 2999, min year: 1900
std::string dateToString(Date date);
Date dateFromString(std::string dateAsString);

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

  const Date &dateOfEntry() const;
  const Date &ageOfCells() const;
  int numberOfCells() const;
  const std::string &userName() const;
  const std::string &remark() const;
  const std::string &cellType() const;
};

//- this is the Nitrogen Refrigerator Class -----------------------------------

class Casette final
{
  std::vector<Vial> inner_;
  unsigned int dimx_, dimy_;

public:

  Casette() = delete;

  Casette (unsigned int dimx, unsigned int dimy);

  bool operator==(const Casette& other) const;


  // throws std::out_of_range whe out of range
  Vial& operator()(unsigned int x, unsigned int y);

  void getDimensions(unsigned& dimX, unsigned& dimY) const;
};

//- this is the controller that manages the nitrogen refrigerator -------------

// - this defines the NitrogenRefrigeratorController itself

class CasetteStack final
{  
private:

  //std::unique_ptr<IDataStorage> _dataStorage;
  std::vector<std::unique_ptr<Casette>> _casetteStack;

public:

  bool operator==(const CasetteStack& other) const;

  unsigned size() const;

  void insertCasettes(std::vector<std::unique_ptr<Casette>>&& casettes);

  // throws std::out_of_range when index > stack size
  // the index numeration starts with 0
  void insertCasette(std::unique_ptr<Casette> casette, unsigned index);

  void pushBack(std::unique_ptr<Casette> casette);

  // throws std::out_of_range when index >= stack size
  void removeCasette(unsigned index);

  // throws std::out_of_range when index >= stack size
  Casette* getCasette(unsigned index) const;
};

// - this defines the interface for the data storage ------

class IDataStorage
{
public:
  // returns x- and y- dimensions
  virtual CasetteStack getStoredNitrogenRefrigerator() const = 0;
  virtual void storeNitrogenRefrigerator(CasetteStack&) const = 0;
};

} // namespace NitrogenRefrigoratorKernel

#endif // CELLCONTAINER_H
