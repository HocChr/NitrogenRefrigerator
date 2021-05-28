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

// this is the Nitrogen Refrigerator Class
class NitrogenRefrigerator
{
  std::vector<Vial> inner_;
  unsigned int dimx_, dimy_;

public:

  NitrogenRefrigerator() = delete;

  NitrogenRefrigerator (unsigned int dimx, unsigned int dimy);

  // throws std::out_of_range whe out of range
  Vial& operator()(unsigned int x, unsigned int y);

};

} // namespace NitrogenRefrigoratorKernel

#endif // CELLCONTAINER_H
