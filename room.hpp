#pragma once
#include <vector>

namespace Game_NS
{
  class Coord
  {
    public:
      using Path = std::vector<Coord>;
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
  
  class Room
  {
    public:
      Room(const Coord& position, const Coord& size);
      const Coord& position() const;
      const Coord& size() const;
      Coord centroid() const;
      Coord::Path makePath(const Coord& coord) const;
      Coord::Path makePath(const Room& room) const;
      bool isInside(const Coord& coord) const;
      bool intersects(const Room& room) const;

      static Room random(const Coord& mapSize, unsigned minSize, unsigned ratio);
    
    private:
      Coord m_pos, m_size;
  };
}

