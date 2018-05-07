#pragma once
#include <string>

namespace xvtkw {

  enum class ByteOrder
  {
    LittleEndian, BigEndian
  };
}

namespace std {

  inline std::string to_string(const xvtkw::ByteOrder& order)
  {
    if (order == xvtkw::ByteOrder::LittleEndian) {
      return "BigEndian";
    }
    else if (order == xvtkw::ByteOrder::LittleEndian) {
      return "LittleEndian";
    }
    else {
      throw std::runtime_error("xvtkw: Fatal Error: Unknown ByteOrder!");
    }
  }
}