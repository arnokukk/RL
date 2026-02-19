#include "geometry.hpp"


namespace Console_NS
{
  Coord::Coord(short x, short y) : x(x), y(y) {}
  

  Rect::Rect(const Coord& tl, const Coord& br) : tl(tl), br(br) {}
  Rect::Rect(short tlx, short tly, short brx, short bry) : tl(tlx, tly), br(brx, bry) {}
  int Rect::width()  const {return this->br.x - this->tl.x;}
  int Rect::height() const {return this->br.y - this->tl.y;}
}

