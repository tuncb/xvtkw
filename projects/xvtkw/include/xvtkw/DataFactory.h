#pragma once
#include <string>
#include <numeric>

namespace xvtkw {
  template <typename IterType> std::string MakeTextData(IterType beg, IterType end)
  {
    using std::to_string;

    auto space_fold = [](std::string a, auto b) { return std::move(a) + ' ' + to_string(b); };
    return std::accumulate(std::next(beg), end, to_string(*beg), space_fold);
  }
}