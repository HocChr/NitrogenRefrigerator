#ifndef CELLCONTAINER_H
#define CELLCONTAINER_H

#include <string>


class CellContainer
{
public:

  struct Date
  {
    unsigned short YEAR = 0;
    unsigned short MONTH = 0;
    unsigned short DAY = 0;
    unsigned short HOUR = 0;
    unsigned short MINUTE = 0;
  };

  struct Dataset
  {
    Date DATE;
    int NUMBER_OF_CELLS = 0;
    std::string REMARK = "";
  };

public:
  CellContainer();

  void addDataset(Dataset&& dataset);

  // delets a Dataset by a given Date. When not found, it returns false, true otherwise.
  bool deleteDataset(Dataset&& dataset);

  // return the Datset that corresponds to the given Date.
  // throws Exception when no corresponding Dataset was found
  Dataset getDataset(Date date);

  int getNumberOfDatasets() const;

  int getNumberOfCells() const;

private:
  int _numCells;
};

#endif // CELLCONTAINER_H
