#pragma once
#include <unordered_map>
#include <xvtkw/DataArray.h>


namespace xvtkw {

  struct Cells
  {
    DataArray connectivity;
    DataArray offsets;
    DataArray types;
  };

  struct Piece 
  {
    int nrPoints;
    DataArray points;
    std::unordered_map<std::string, DataArray> pointData;
    int nrCells;
    Cells cells;
    std::unordered_map<std::string, DataArray> cellData;
  };

}
