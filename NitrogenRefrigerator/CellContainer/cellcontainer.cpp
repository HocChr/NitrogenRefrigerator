#include "cellcontainer.h"

#include <algorithm>
#include <stdexcept>

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

// struct Dataset -------------------------------------------------------------

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
  _dateOfEntry{dateOfEntry},
  _ageOfCells{ageOfCells},
  _numberOfCells{numberOfCells},
  _userName{userName},
  _remark{remark},
  _cellType{cellType}
{

}

// Class CellContainer --------------------------------------------------------

NitrogenRefrigerator::NitrogenRefrigerator(unsigned int dimx, unsigned int dimy)
  : dimx_ (dimx), dimy_ (dimy)
{
  inner_.resize (dimx_*dimy_);
}

Vial& NitrogenRefrigerator::operator()(unsigned int x, unsigned int y)
{
  if (x >= dimx_ || y>= dimy_)
    throw std::out_of_range("Matrix indices out of range"); // ouch
  return inner_[dimx_*y + x];
}

// Class NitrogenRefrigeratorController ----------------------------------------


bool NitrogenRefrigeratorController::check(const IDataStorage* dataStorage)
{
  return true;
}

NitrogenRefrigeratorController::NitrogenRefrigeratorController(std::unique_ptr<IDataStorage> dataStorage):
  _dataStorage(std::move(dataStorage))
{
  if(check(_dataStorage.get()))
  {
    _nitrogenRefrigerator = std::make_unique<NitrogenRefrigerator>(
          _dataStorage->getRefrigeratorDimensions().first,
          _dataStorage->getRefrigeratorDimensions().second);
  }
  else{
    _nitrogenRefrigerator = std::make_unique<NitrogenRefrigerator>(0, 0);
  }
}

std::vector<NitrogenRefrigeratorErrorTypes> NitrogenRefrigeratorController::getErrors()
{
  return _errors;
}

std::vector<std::pair<int, int> > NitrogenRefrigeratorController::getCellsWithMultipleVials()
{
  std::vector<std::pair<int, int>> out;

  return out;
}
