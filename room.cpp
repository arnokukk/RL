#include "room.hpp"

#include <cmath>

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
  
  std::vector<Coord> Coord::makePath(const Coord& dst)
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
}

