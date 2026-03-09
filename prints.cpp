#include <sstream>

#include "prints.hpp"
#include "geometry.hpp"
#include "console.hpp"
#include "room.hpp"

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
  
  std::string toString(const Game_NS::Coord& coord)
  {
    std::ostringstream o;
    o << coord.row() << 'x' << coord.col();
    return o.str();
  }


  std::string toString(const Game_NS::Room& room)
  {
    std::ostringstream o;
    o << "Room: P" << toString(room.position()) << " S" << toString(room.size());
    return o.str();
  }

  
  void reportFailed(const char* name, std::ostream& out/*=std::cerr*/)
  {
    out << name << " FAILED: " << ::GetLastError() << std::endl;
  }
}

