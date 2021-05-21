#ifndef CELLCONTAINER_H
#define CELLCONTAINER_H

#include <string>
#include <vector>

namespace NitrogenRefrigoratorKernel {

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

struct Dataset
{
  Date DateOfEntry;
  int NumberOfCells = 0;
  std::string UserName = "";
  std::string Remark = "";
};


class CellContainer
{

public:

  void addDataset(Dataset&& dataset);

  // delets a Dataset by a given Date. When not found, it returns false, true otherwise.
  bool deleteDataset(Dataset&& dataset);

  // throws Exception when no corresponding Dataset was found
  std::vector<Dataset> getDatasetByDate(const Date& date) const;

  // throws Exception when no corresponding Dataset was found
  std::vector<Dataset> getDatasetByUserName(const std::string& userName) const;

  // throws Exception when no corresponding Dataset was found
  std::vector<Dataset> getDatasetByRemark(const std::string& remark) const;

  int getNumberOfDatasets() const;

  int getNumberOfCells() const;

private:
  std::vector<Dataset> _dataSets;
};

} // namespace NitrogenRefrigoratorKernel

#endif // CELLCONTAINER_H
