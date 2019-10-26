#pragma once
#include <vector>
#include <string>
#include <xvtkw/VtuType.h>
#include <tcb/span.hpp>
#include <variant>

namespace xvtkw {

  enum class DataSetAttribute
  {
    None, Scalars, Vectors, Normals, Tensors, TCoords
  };

  inline std::string to_string(const xvtkw::DataSetAttribute& attr)
  {
    switch (attr)
    {
    case xvtkw::DataSetAttribute::None:
      return "";
    case xvtkw::DataSetAttribute::Scalars:
      return "Scalars";
    case xvtkw::DataSetAttribute::Vectors:
      return "Vectors";
    case xvtkw::DataSetAttribute::Normals:
      return "Normals";
    case xvtkw::DataSetAttribute::Tensors:
      return "Tensors";
    case xvtkw::DataSetAttribute::TCoords:
      return "TCoords";
    default:
      return "";
      break;
    }
  }
  
  struct DataSet {
    VtuType type;
    DataSetAttribute attribute;
    int num_components;
    std::variant<std::string, tcb::span<char>> data;
  };

  template <typename T> tcb::span<char> CreateBinaryWrapper(T* data, size_t size)
  {
    return { static_cast<char>(data), size };
  }

  template <typename Iter> std::string CreateText(Iter b, Iter e) 
  {
    return "";
  }

}
