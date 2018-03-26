#pragma once
#include <string>

namespace xvtkw {

  enum class VtuType {
    Int32, Float32, Float64, UInt8, None
  };

  template <typename T> inline VtuType type_to_vtk_type() 	  { static_assert(false, "xvtkw: unknown type calling type_to_vtk_type"); }
  template <> inline VtuType type_to_vtk_type<int>() 		  	  { return VtuType::Int32; }
  template <> inline VtuType type_to_vtk_type<float>() 		  { return VtuType::Float32; }
  template <> inline VtuType type_to_vtk_type<double>() 		  { return VtuType::Float64; }
  template <> inline VtuType type_to_vtk_type<unsigned char>()  { return VtuType::UInt8; }
}

namespace std {

  string to_string(::xvtkw::VtuType type)
  {
    switch (type)
    {
    case ::xvtkw::VtuType::Int32:
      return "Int32";
      break;
    case ::xvtkw::VtuType::Float32:
      return "Float32";
      break;
    case ::xvtkw::VtuType::Float64:
      return "Float64";
      break;
    case ::xvtkw::VtuType::UInt8:
      return "UInt8";
      break;
    default:
      throw runtime_error("xvtkw fatal error: Unknown VtuType or None Type in function to_string");
      break;
    }
  }
}
