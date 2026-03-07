#pragma once

#include <iostream>
#include <string>

#include "console_fwd.hpp"


namespace Debug_NS
{
  std::string toString(const Console_NS::Coord& coord);
  std::string toString(const Console_NS::Rect& rect);
  std::string toString(const Console_NS::ScreenBufferInfo& info);

  template<typename T>
  void print(const T& value, const char* prefix="")
  {
    std::cout << prefix << toString(value) << std::endl;
  }
  
  void reportFailed(const char* name, std::ostream& out=std::cerr);
}
