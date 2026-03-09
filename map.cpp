#include "map.hpp"
#include "room.hpp"

#include <random>
#include <chrono>
#include <iostream>

namespace Game_NS
{
  Cell::Cell(bool visible) : m_visible(visible) {}
  
  Floor::Floor(bool visible/*=false*/) : Cell(visible) {}
  char Floor::ch() const
  {
    return m_visible ? '.' : ' ';
  }

  Wall::Wall(bool visible/*=false*/) : Cell(visible) {}
  char Wall::ch() const
  {
    return m_visible ? '#' : ' ';
  }
  
  CellsRow::CellsRow(size_t width) : m_width(width)
  {
    cells = new Cell::ptr[width];
  }
  
  CellsRow::~CellsRow()
  {
    delete[] cells;
  }
  
  std::string CellsRow::str() const
  {
    std::string ret;
    ret.reserve(m_width);
    for (size_t i=0; i<m_width; i++)
      ret.push_back(cells[i]->ch());
    return ret;
  }
  
  size_t CellsRow::width() const { return m_width; }
  
  Cell::ptr& CellsRow::get(unsigned col)
  {
    return cells[col];
  }
  
  const Cell& CellsRow::operator[](int index) const
  {
    return *cells[index];
  }
  
  CellsRow::ptr CellsRow::border(size_t width, bool visible/*=true*/)
  {
    CellsRow::ptr row(new CellsRow(width));
    for (size_t i=0; i<width; i++)
      row->cells[i].reset(new Wall(visible));
    return row;
  }

  CellsRow::ptr CellsRow::empty(size_t width, bool visible/*=true*/)
  {
    CellsRow::ptr row(new CellsRow(width));
    for (size_t i=1; i<width-1; i++)
      row->cells[i].reset(new Floor(visible));
    row->cells[0].reset(new Wall(visible));
    row->cells[width-1].reset(new Wall(visible));
    return row;
  }
  
  CellsRow::ptr CellsRow::random(size_t width, bool visible/*=true*/, int oneWallOf/*=3*/)
  {
    CellsRow::ptr row(new CellsRow(width));
    std::mt19937 gen((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dstr(1, oneWallOf);
    for (size_t i=0; i<width; ++i)
    {
      if (1 == dstr(gen))
        row->cells[i].reset(new Wall(visible));
      else
        row->cells[i].reset(new Floor(visible));
    }
    return row;
  }
  
  Map::Map(size_t width, size_t height) : m_width(width), m_height(height)
  {
    rows = new CellsRow::ptr[height];
  }
  
  Map::~Map()
  {
    delete[] rows;
  }
  
  Coord Map::size() const
  {
    return Coord(m_height, m_width);
  }
  
  CellsRow::ptr& Map::get(unsigned row)
  {
    return rows[row];
  }
  
  Cell::ptr& Map::get(unsigned row, unsigned col)
  {
    return get(row)->get(col);
  }
  
  const CellsRow& Map::operator[](int index) const
  {
    return *rows[index];
  }
  
  Map Map::empty(size_t width, size_t height, bool visible/*=false*/)
  {
    Map map(width, height);
    map.rows[0] = std::move(CellsRow::border(width, visible));
    for (size_t i=1; i < height-1; i++)
    {
      map.rows[i] = std::move(CellsRow::empty(width, visible));
    }
    map.rows[height-1] = std::move(CellsRow::border(width, visible));
    return map;
  }

  Map Map::random(size_t width, size_t height, bool visible/*=false*/, int oneWallOf/*=3*/)
  {
    Map map(width, height);
    map.rows[0] = std::move(CellsRow::border(width, visible));
    map.rows[height-1] = std::move(CellsRow::border(width, visible));

    std::mt19937 gen((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dstr(1, oneWallOf);
    for (size_t i=1; i < height-1; i++)
    {
      map.rows[i].reset(new CellsRow(width));
      for (size_t j=0; j<width; j++)
      {
        if (0 == j || width-1 == j || 1 == dstr(gen))
          map.rows[i]->cells[j].reset(new Wall(visible));
        else
          map.rows[i]->cells[j].reset(new Floor(visible));
      }
    }
    return map;
  }
  
  Map Map::walls(size_t width, size_t height, bool visible/*=false*/)
  {
    Map map(width, height);
    for (size_t i=0; i<height; i++)
    {
      map.rows[i] = std::move(CellsRow::border(width, visible));
    }
    return map;
  }

  void Map::display()
  {
    for (size_t c=0; c<m_height; c++)
      std::cout << rows[c]->str() << std::endl;
  }
  
}
