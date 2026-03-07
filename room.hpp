#pragma once
#include <vector>

namespace Game_NS
{
  class Coord
  {
    public:
      Coord(unsigned row, unsigned col);
      unsigned row() const;
      unsigned col() const;
      
      unsigned dist(const Coord& coord) const;
      unsigned distRow(const Coord& coord) const;
      unsigned distCol(const Coord& coord) const;
      
      std::vector<Coord> makePath(const Coord& dst) const;
      
    private:
      void makePathH(unsigned col, std::vector<Coord>& path) const;
      void makePathV(unsigned row, std::vector<Coord>& path) const;
    private:
      unsigned m_row=0, m_col=0;
  };
}

