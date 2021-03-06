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

  Vial(const Vial&) = default;
  Vial& operator=(const Vial&) = default;

  const Date &dateOfEntry() const;
  const Date &ageOfCells() const;
  int numberOfCells() const;
  const std::string &userName() const;
  const std::string &remark() const;
  const std::string &cellType() const;
};

//- this is the Casette Class that carries the vials --------------------------

class Casette final
{
  std::vector<std::unique_ptr<Vial>> inner_;
  unsigned int dimx_, dimy_;

public:

  Casette() = delete;

  Casette (unsigned int dimx, unsigned int dimy);
  Casette (const Casette&) = delete;
  Casette& operator=(const Casette&) = delete;

  bool operator==(const Casette& other) const;

  // throws std::out_of_range when out of range
  const Vial* const operator()(unsigned int x, unsigned int y) const;

  // throws std::out_of_range when out of range
  void add(unsigned int x, unsigned int y, std::unique_ptr<Vial> vial);

  void getDimensions(unsigned& dimX, unsigned& dimY) const;
};

//- this is the casette stack that carries the casettes -----------------------

class CasetteStack final
{  
private:

  //std::unique_ptr<IDataStorage> _dataStorage;
  std::vector<std::unique_ptr<Casette>> _casetteStack;
  std::string _name = "";

public:

  CasetteStack() = delete;
  CasetteStack(std::string&& name);
  CasetteStack(const std::string& name);

  CasetteStack(const CasetteStack&) = delete;
  CasetteStack& operator=(const CasetteStack&) = delete;

  CasetteStack(CasetteStack&&) = default;
  CasetteStack& operator=(CasetteStack&&) = default;

  bool operator==(const CasetteStack& other) const;

  unsigned size() const;

  const std::string& name() const;

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

class NitrogenRefrigorator final
{
  std::vector<CasetteStack> _racks;

public:

  NitrogenRefrigorator() = default;
  NitrogenRefrigorator(const NitrogenRefrigorator& other) = delete;
  NitrogenRefrigorator(NitrogenRefrigorator&& other) = default;
  NitrogenRefrigorator& operator=(NitrogenRefrigorator&& other) = default;

  // return the number of racks
  unsigned size() const;

  // throw runtime_error exception when there is a stack-name equals the given stack-name
  void appendRack(CasetteStack&& rack);  

  // throws std::out_of_range when index > stack size
  // the index numeration starts with 0
  void insertRack(CasetteStack&& rack, unsigned index);

  // removes that rack with the given name
  // throws runtime_error exception when a rack with that name was not found
  void removeRack(std::string name);

  // throws runtime_error exception when a rack with that name was not found
  const CasetteStack& getRack(std::string name) const;
  const CasetteStack& getRack(unsigned index) const;
};

// - this defines the interface for the data storage --------------------------

class IDataStorage
{
public:
  // returns x- and y- dimensions
  virtual NitrogenRefrigorator getStoredNitrogenRefrigerator(const std::string& filepath) const = 0;
  virtual void storeNitrogenRefrigerator(const std::string& filepath,
                                         NitrogenRefrigoratorKernel::NitrogenRefrigorator&) const = 0;
};

// ----------------------------------------------------------------------------

class NitrogenRefrigoratorManager
{
public:
  enum class ErrorCode
  {
    NO_ERROR = 0,
    FILE_NOT_EXISTS,
    FILE_NOT_VALID
  };


  NitrogenRefrigoratorManager() = delete;
  NitrogenRefrigoratorManager(const NitrogenRefrigoratorManager&) = delete;

  NitrogenRefrigoratorManager(std::unique_ptr<IDataStorage> storage);

  const NitrogenRefrigorator& getNitrogenRefigerator();
  void saveNitrogenRefrigerator();

private:

  std::unique_ptr<IDataStorage> _dataStorage;
  NitrogenRefrigorator _refrigerator;
  std::vector<ErrorCode> _errorCode;

  const std::string _filePath = "NitrogenRefrigerator.json";
};

} // namespace NitrogenRefrigoratorKernel

#endif // CELLCONTAINER_H
