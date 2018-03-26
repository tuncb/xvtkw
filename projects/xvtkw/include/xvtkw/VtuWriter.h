#pragma once

#include <string>

#include "xvtkw.h"

namespace xvtkw {

void write_vtu(const xvtkw::vtk_structure& vtk, const std::string& filename);

}