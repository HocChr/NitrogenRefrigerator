#include "cellcontainer.h"

#include <algorithm>

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

// Class CellContainer --------------------------------------------------------

void CellContainer::addDataset(Dataset &&dataset)
{
  _dataSets.push_back(dataset);
}

bool CellContainer::deleteDataset(Dataset &&dataset)
{
  return false;
}

std::vector<Dataset> CellContainer::getDatasetByDate(const Date& date) const
{
  std::vector<Dataset> result;

  std::copy_if(_dataSets.begin(), _dataSets.end(), std::back_inserter(result), [&](Dataset v) {
      return v.DateOfEntry == date;
  });

  return result;
}

std::vector<Dataset> CellContainer::getDatasetByUserName(const std::string& userName) const
{
  std::vector<Dataset> result;

  std::copy_if(_dataSets.begin(), _dataSets.end(), std::back_inserter(result), [&](Dataset v) {
      return v.UserName == userName;
  });

  return result;
}

std::vector<Dataset> CellContainer::getDatasetByRemark(const std::string& remark) const
{
  std::vector<Dataset> result;

  std::copy_if(_dataSets.begin(), _dataSets.end(), std::back_inserter(result), [&](Dataset v) {
      return v.Remark == remark;
  });

  return result;
}

int CellContainer::getNumberOfDatasets() const
{
  return static_cast<int>(_dataSets.size());
}

int CellContainer::getNumberOfCells() const
{
  int numberOfCells = 0;

  for(const auto& cell : _dataSets)
  {
    numberOfCells += cell.NumberOfCells;
  }

  return numberOfCells;
}
