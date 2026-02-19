#include <sstream>

#include "prints.hpp"
#include "geometry.hpp"
#include "console.hpp"

namespace Debug_NS
{
  std::string toString(const Console_NS::Coord& coord)
  {
    std::ostringstream o;
    o << coord.x << ',' << coord.y;
    return o.str();
  }

  std::string toString(const Console_NS::Rect& rect)
  {
    std::ostringstream o;
    o << '[' << toString(rect.tl) << ':' << toString(rect.br) << ']';
    return o.str();
  }
  
  std::string toString(const Console_NS::ScreenBufferInfo& info)
  {
    std::ostringstream o;
    auto flags = o.flags();
    o << "SBI: size=" << toString(info.size) << "; cp=" << toString(info.cursorPosition)
      << "; window=" << toString(info.window) << "; max win size=" << toString(info.maxWinSize)
      << "; attrs=0x" << std::hex << info.attributes;
    o.flags(flags);
    return o.str();
  }
}

