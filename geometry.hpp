#pragma once

namespace Console_NS
{
  struct Coord
  {
    short x{0}, y{0};
    
    Coord() = default;
    Coord(short x, short y);
  };
  
  struct Rect
  {
    Coord tl, br;
    Rect() = default;
    Rect(const Coord& tl, const Coord& br);
    Rect(short tlx, short tly, short brx, short bry);
    
    int width() const;
    int height() const;
  };
}

