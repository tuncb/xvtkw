#pragma once
#include <string>
#include <optional>
#include <variant>
#include <tcb/span.hpp>

namespace xvtkw {

  enum class DataType {
    Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float32, Float64
  };

  //todo -otunc add to_string(DataType) function

  enum class DataFormat {
    Ascii, Binary, Appended
  };

  //todo -otunc add to_string(DataFormat) function
  
  struct DataArray
  {
    std::string name;
    DataType type;
    DataFormat format;
    int numberOfComponenets;
    std::variant<std::string, tcb::span<char>> data;
    std::optional<int> offset;
  };

  enum class Encoding {
    Raw, Base64
  };

  //todo -otunc add to_string(Encoding) function
  
  struct AppendedData
  {
    Encoding encoding;
    //todo -otunc add data identifier
  };

}