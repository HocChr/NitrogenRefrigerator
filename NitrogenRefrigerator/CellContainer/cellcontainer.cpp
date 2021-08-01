#include "cellcontainer.h"

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <assert.h>

using namespace NitrogenRefrigoratorKernel;

// helper functions -----------------------------------------------------------


// struct date ----------------------------------------------------------------

bool Date::operator<(const Date &date) const
{
  if(Year < date.Year) return true;
  if(Year > date.Year) return false;

  if(Month < date.Month) return true;
  if(Month > date.Month) return false;

  if(Day < date.Day) return true;
  if(Day > date.Day) return false;

  if(Hour < date.Hour) return true;
  if(Hour > date.Hour) return false;

  if(Minute < date.Minute) return true;
  if(Minute > date.Minute) return false;

  return false;
}

bool Date::operator>(const Date &date) const
{
  return !(*this < date || *this == date);
}

bool Date::operator==(const Date &date) const
{
  return Year == date.Year &&
      Month == date.Month &&
      Day == date.Day &&
      Hour == date.Hour &&
      Minute == date.Minute;
}

std::string NitrogenRefrigoratorKernel::dateToString(Date date)
{
  std::string out;

  out += std::to_string(date.Year); out += "-";
  out += std::to_string(date.Month ); out += "-";
  out += std::to_string(date.Day   ); out += "T";
  out += std::to_string(date.Hour  ); out += ":";
  out += std::to_string(date.Minute); out += ":00";

  return out;
}

Date NitrogenRefrigoratorKernel::dateFromString(std::string dateAsString)
{
  unsigned short year, month, day, hour, minute = 0;

  std::string delimiter = "-";
  size_t pos = 0;
  std::string token;

  try{

    pos = dateAsString.find(delimiter);
    if (pos != std::string::npos)
    {
      token = dateAsString.substr(0, pos);
      year = std::stoul(token);
      if(year < 1900 || year >= 3000){
        throw std::runtime_error(std::string("dateFromString: invalid date format"));
      }
      dateAsString.erase(0, pos + delimiter.length());
    }
    else{
      throw std::runtime_error(std::string("dateFromString: invalid date format"));
    }

    pos = dateAsString.find(delimiter);
    if (pos != std::string::npos)
    {
      token = dateAsString.substr(0, pos);
      month = std::stoul(token);
      if(month < 1 || month > 12){
        throw std::runtime_error(std::string("dateFromString: invalid date format"));
      }
      dateAsString.erase(0, pos + delimiter.length());
    }
    else{
      throw std::runtime_error(std::string("dateFromString: invalid date format"));
    }

    delimiter="T";
    pos = dateAsString.find(delimiter);
    if (pos != std::string::npos)
    {
      token = dateAsString.substr(0, pos);
      day = std::stoul(token);
      if(day < 1 || day > 31){
        throw std::runtime_error(std::string("dateFromString: invalid date format"));
      }
      dateAsString.erase(0, pos + delimiter.length());
    }
    else{
      throw std::runtime_error(std::string("dateFromString: invalid date format"));
    }

    delimiter=":";
    pos = dateAsString.find(delimiter);
    if (pos != std::string::npos)
    {
      token = dateAsString.substr(0, pos);
      hour = std::stoul(token);
      if(hour < 0 || hour > 24){
        throw std::runtime_error(std::string("dateFromString: invalid date format"));
      }
      dateAsString.erase(0, pos + delimiter.length());
    }
    else{
      throw std::runtime_error(std::string("dateFromString: invalid date format"));
    }

    pos = dateAsString.find(delimiter);
    if (pos != std::string::npos)
    {
      token = dateAsString.substr(0, pos);
      minute = std::stoul(token);
      if(minute < 0 || minute > 59){
        throw std::runtime_error(std::string("dateFromString: invalid date format"));
      }
      dateAsString.erase(0, pos + delimiter.length());
    }
    else{
      throw std::runtime_error(std::string("dateFromString: invalid date format"));
    }

  }
  catch(...)
  {
    throw std::runtime_error(std::string("dateFromString: invalid date format"));
  }

  Date date{year, month, day, hour, minute};
  return date;
}

// struct Dataset -------------------------------------------------------------

const Date &Vial::dateOfEntry() const
{
  return _dateOfEntry;
}

const Date &Vial::ageOfCells() const
{
  return _ageOfCells;
}

int Vial::numberOfCells() const
{
  return _numberOfCells;
}

const std::string &Vial::userName() const
{
  return _userName;
}

const std::string &Vial::remark() const
{
  return _remark;
}

const std::string &Vial::cellType() const
{
  return _cellType;
}

bool Vial::operator==(const Vial &date) const
{
  return (_dateOfEntry == date._dateOfEntry) &&
      (_ageOfCells == date._ageOfCells) &&
      (_numberOfCells == date._numberOfCells) &&
      (_remark == date._remark) &&
      (_userName == date._userName) &&
      (_cellType == date._cellType);
}

Vial::Vial(Date dateOfEntry,
           Date ageOfCells,
           int numberOfCells,
           std::string userName,
           std::string remark,
           std::string cellType):
  _dateOfEntry(dateOfEntry),
  _ageOfCells(ageOfCells),
  _numberOfCells(numberOfCells),
  _userName(userName),
  _remark(remark),
  _cellType(cellType)
{

}

// Class CellContainer --------------------------------------------------------

Casette::Casette(unsigned int dimx, unsigned int dimy)
  : dimx_ (dimx), dimy_ (dimy)
{
  inner_.resize (dimx_*dimy_);
}

bool Casette::operator==(const Casette &other) const
{
  if(dimx_ != other.dimx_ || dimy_ != other.dimy_){
    return false;
  }

  for(unsigned i = 0; i < dimx_; ++i)
  {
    for(unsigned j = 0; j < dimy_; ++j)
    {
      auto * thisVial = this->operator()(i, j);
      auto * otherVial = other.operator()(i, j);

      if( thisVial == nullptr || otherVial == nullptr)
      {
        if(!(thisVial == otherVial))
        {
          return false;
        }
        continue;
      }

      if (!(*thisVial == *otherVial))
      {
        return false;
      }
    }
  }

  return true;
}

const Vial* const Casette::operator()(unsigned int x, unsigned int y) const
{
  if (x >= dimx_ || y>= dimy_)
    throw std::out_of_range("Matrix indices out of range"); // ouch
  return inner_[dimx_*y + x].get();
}

void Casette::add(unsigned int x, unsigned int y, std::unique_ptr<Vial> vial)
{
  if (x >= dimx_ || y>= dimy_)
    throw std::out_of_range("Matrix indices out of range"); // ouch
  inner_[dimx_*y + x] = std::move(vial);
}

void Casette::getDimensions(unsigned &dimX, unsigned &dimY) const
{
  dimX = dimx_;
  dimY = dimy_;
}

// Class NitrogenRefrigeratorController ----------------------------------------

void CasetteStack::insertCasettes(std::vector<std::unique_ptr<Casette>>&& casettes)
{
  _casetteStack = std::move(casettes); // move the casettes
}

CasetteStack::CasetteStack(std::string &&name) : _name(name)
{
}

CasetteStack::CasetteStack(const std::string &name) : _name(name)
{
}

bool CasetteStack::operator==(const CasetteStack &other) const
{
  bool ok = equal(begin(_casetteStack), end(_casetteStack),
                  begin(other._casetteStack), end(other._casetteStack),
                  []
                  (const std::unique_ptr<Casette>& lhs, const std::unique_ptr<Casette>& rhs)
  {
    if(lhs == nullptr && rhs == nullptr)
      return true;
    else if (lhs == nullptr || rhs == nullptr)
      return false;
    return *lhs.get() == *rhs.get();
  });
  ok = ok ? _name == other.name() : false;
  return ok;
}

unsigned CasetteStack::size() const
{
  return _casetteStack.size();
}

const std::string &CasetteStack::name() const
{
  return _name;
}

void CasetteStack::insertCasette(std::unique_ptr<Casette> casette, unsigned index)
{
  if(index > _casetteStack.size())
    throw std::out_of_range("insertCasette: index out of range");
  _casetteStack.insert(_casetteStack.begin() + index, std::move(casette));
}

void CasetteStack::pushBack(std::unique_ptr<Casette> casette)
{
  _casetteStack.push_back(std::move(casette));
}

void CasetteStack::removeCasette(unsigned index)
{
  if(index >= _casetteStack.size())
    throw std::out_of_range("removeCasette: index out of range");
  _casetteStack.erase(_casetteStack.begin() + index);
}

Casette* CasetteStack::getCasette(unsigned index) const
{
  if(index >= _casetteStack.size())
    throw std::out_of_range("getCasette: index out of range"); // ouch
  return _casetteStack.at(index).get();
}

//- Nitrogen Refrigerator -----------------------------------------------------

unsigned NitrogenRefrigorator::size() const
{
  return _racks.size();
}

void NitrogenRefrigorator::appendRack(CasetteStack &&rack)
{
  auto it = std::find_if(_racks.begin(), _racks.end(),
                         [&rack]
                         (const CasetteStack& stack) { return stack.name() == rack.name(); });
  if (it != _racks.end())
  {
    throw std::runtime_error("there is a stack with that name yet!");
  }

  _racks.push_back(std::move(rack));
}

void NitrogenRefrigorator::insertRack(CasetteStack &&rack, unsigned index)
{
  if(index > _racks.size())
    throw std::out_of_range("insertRack: index out of range");
  _racks.insert(_racks.begin() + index, std::move(rack));
}

void NitrogenRefrigorator::removeRack(std::string name)
{
  const auto it = std::find_if(_racks.begin(), _racks.end(),
                         [&name]
                         (const CasetteStack& stack) { return stack.name() == name; });
  if (it == _racks.end())
  {
    throw std::runtime_error("there is no stack with that name!");
  }
  _racks.erase(it);
}

const CasetteStack &NitrogenRefrigorator::getRack(std::string name) const
{
  auto it = std::find_if(_racks.begin(), _racks.end(),
                         [&name]
                         (const CasetteStack& stack) { return stack.name() == name; });
  if (it == _racks.end())
  {
    throw std::runtime_error("there is no stack with that name!");
  }

  return *it;
}

const CasetteStack &NitrogenRefrigorator::getRack(unsigned index) const
{
  if (index > size())
  {
    throw std::out_of_range("getRack(): index out of range!");
  }
  return _racks.at(index);
}

// ----------------------------------------------------------------------------

static bool checkFileExists(const std::string& filepath)
{
  std::ifstream f(filepath.c_str());
  return f.good();
}

NitrogenRefrigoratorManager::NitrogenRefrigoratorManager(std::unique_ptr<IDataStorage> storage)
{
  _dataStorage = std::move(storage);

  try
  {
    _refrigerator = std::move(_dataStorage->getStoredNitrogenRefrigerator(_filePath));
  }
  catch (...)
  {
    if(!checkFileExists(_filePath))
    {
      _errorCode.push_back(ErrorCode::FILE_NOT_EXISTS);
      _dataStorage->storeNitrogenRefrigerator(_filePath, _refrigerator);
    }
    else
    {
      assert(false);
    }
  }
}
