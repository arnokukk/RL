#include "room.hpp"

#include <cmath>
#include <chrono>
#include <random>
#include <stdexcept>

namespace Game_NS
{
  Coord::Coord(unsigned row, unsigned col) : m_row(row), m_col(col)
  {
  }
  
  unsigned Coord::row() const
  {
    return m_row;
  }

  unsigned Coord::col() const
  {
    return m_col;
  }

  unsigned Coord::distRow(const Coord& coord) const
  {
    return static_cast<unsigned>(std::abs((float)m_row - coord.m_row));
  }

  unsigned Coord::distCol(const Coord& coord) const
  {
    return static_cast<unsigned>(std::abs((float)m_col - coord.m_col));
  }

  unsigned Coord::dist(const Coord& coord) const
  {
    float x = (float)m_col - (float)coord.m_col, y = (float)m_row - (float)coord.m_row;
    return static_cast<unsigned>(std::round(std::sqrt(x * x + y * y)));
  }
  
  void Coord::makePathH(unsigned col, std::vector<Coord>& path) const
  {
    int step = col > m_col ? +1 : -1;
    for (unsigned c=m_col; c!=col;)
    {
      c += step;
      path.push_back(Coord(m_row, c));
    }
  }

  void Coord::makePathV(unsigned row, std::vector<Coord>& path) const
  {
    int step = row > m_row ? +1 : -1;
    for (unsigned r=m_row; r!=row;)
    {
      r += step;
      path.push_back(Coord(r, m_col));
    }
  }
  
  std::vector<Coord> Coord::makePath(const Coord& dst) const
  {
    unsigned v_dist = this->distRow(dst), h_dist = this->distCol(dst);
    std::vector<Coord> path;
    path.reserve(h_dist + v_dist + 1);
    path.push_back(*this);
    if (h_dist > v_dist)
    {
      unsigned a = (this->col() + dst.col()) / 2;
      this->makePathH(a, path);
      path.back().makePathV(dst.row(), path);
      path.back().makePathH(dst.col(), path);
    }
    else
    {
      unsigned a = (this->row() + dst.row()) / 2;
      this->makePathV(a, path);
      path.back().makePathH(dst.col(), path);
      path.back().makePathV(dst.row(), path);
    }
    return path;
  }
  
  // class Room
  Room::Room(const Coord& position, const Coord& size)
    : m_pos(position), m_size(size)
  {
  }
  
  const Coord& Room::position() const
  {
    return m_pos;
  }
  
  const Coord& Room::size() const
  {
    return m_size;
  }
  
  Coord Room::centroid() const
  {
    unsigned row = m_pos.row() + m_size.row() / 2, col = m_pos.col() + m_size.col() / 2;
    return Coord(row, col);
  }
  
  Coord::Path Room::makePath(const Coord& coord) const
  {
    if (this->isInside(coord)) return Coord::Path();
    return this->centroid().makePath(coord);
  }

  Coord::Path Room::makePath(const Room& room) const
  {
    if (this->intersects(room)) return Coord::Path();
    return this->centroid().makePath(room.centroid());
  }
  
  bool Room::isInside(const Coord& coord) const
  {
    bool _col = coord.col() >= m_pos.col() && coord.col() < m_pos.col() + m_size.col();
    bool _row = coord.row() >= m_pos.row() && coord.row() < m_pos.row() + m_size.row();
    return _col && _row;
  }
  
  bool Room::intersects(const Room& room) const
  {
    unsigned tTop = m_pos.row(), oTop = room.m_pos.row();
    unsigned tBot = m_pos.row() + m_size.row(), oBot = room.m_pos.row() + room.m_size.row();
    if (tTop >= oBot || oTop >= tBot) return false;
    unsigned tLeft = m_pos.col(), oLeft = room.m_pos.col();
    unsigned tRight = m_pos.col() + m_size.col(), oRight = room.m_pos.col() + room.m_size.col();
    if (tLeft >= oRight || oLeft >= tRight) return false;
    return true;
  }
  
  Room Room::random(const Coord& mapSize, unsigned minSize, unsigned ratio)
  {
    static const unsigned MIN_POS = 1;
    static std::mt19937 gen((unsigned)std::chrono::system_clock::now().time_since_epoch().count());

    const unsigned MAX_ROWS = mapSize.row() / ratio;
    const unsigned MAX_COLS = mapSize.col() / ratio;
    if (MAX_ROWS <= minSize || MAX_COLS <= minSize)
      throw std::runtime_error("Too small map to place room");
    
    std::uniform_int_distribution<unsigned> dSizeR(minSize, MAX_ROWS);
    std::uniform_int_distribution<unsigned> dSizeC(minSize, MAX_COLS);
    Coord size(dSizeR(gen), dSizeC(gen));
    
    const unsigned MAX_POS_ROW = mapSize.row() - size.row() - 1;
    const unsigned MAX_POS_COL = mapSize.col() - size.col() - 1;
    if (MAX_POS_ROW <= MIN_POS || MAX_POS_COL <= MIN_POS)
      throw std::runtime_error("Too small map to place room");

    std::uniform_int_distribution<unsigned> dPosR(MIN_POS, MAX_POS_ROW);
    std::uniform_int_distribution<unsigned> dPosC(MIN_POS, MAX_POS_COL);
    Coord pos(dPosR(gen), dPosC(gen));

    return Room(pos, size);
  }
}

