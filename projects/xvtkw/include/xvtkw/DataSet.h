#pragma once
#include <vector>
#include <string>
#include <xvtkw/VtuType.h>
#include <stringconversion/Fundamentals.h>

namespace xvtkw {

  enum class DataSetAttribute
  {
    None, Scalars, Vectors, Normals, Tensors, TCoords
  };

  struct DataSet {
    DataSet() : type(VtuType::None), num_components(0),attribute(DataSetAttribute::None) {}
    DataSet(VtuType a_type, int a_num_componenets, DataSetAttribute attr)
      : type(a_type), num_components(a_num_componenets), attribute(attr) {}

    template <typename Iter> DataSet(VtuType a_type, int a_num_componenets, DataSetAttribute attr, Iter b, Iter e)
      : type(a_type), num_components(a_num_componenets), attribute(attr)
    {
      add_to_data(b, e);
    }

    template <typename Iter> void add_to_data(Iter b, Iter e) {
      for (auto iter = b; iter != e; ++iter) {
        data += stringconversion::to_string(*iter) + " ";
      }
    }

    template <typename T> void add_to_data(T t) {
      data += stringconversion::to_string(t) + " ";
    }
    template <typename T> void add_to_data(std::initializer_list<T> list) {
      this->add_to_data(std::begin(list), std::end(list));
    }

    VtuType type;
    int num_components;
    std::string data;
    DataSetAttribute attribute;
  };

}

namespace std {
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
}

