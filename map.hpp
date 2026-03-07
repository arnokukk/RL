#pragma once
#include <memory>

namespace Game_NS
{
  class Cell
  {
    public:
      using ptr = std::unique_ptr<Cell>;
      Cell(bool visible);
      virtual char ch() const = 0;
      virtual ~Cell() = default;
    protected:
      bool m_visible = false;
  };
  
  class Floor : public Cell
  {
    public:
      Floor(bool visible=false);
      char ch() const override;
  };
  

  class Wall : public Cell
  {
    public:
      Wall(bool visible = false);
      char ch() const override;
  };
  
  class CellsRow
  {
    friend class Map;
    public:
      using ptr = std::unique_ptr<CellsRow>;
      CellsRow(const CellsRow&) = delete;
      CellsRow(CellsRow&&) = default;
      ~CellsRow();
      
      std::string str() const;
      size_t width() const;
      Cell::ptr& get(int index);
      const Cell& operator[](int index) const;
      static CellsRow::ptr border(size_t width, bool visible=true); // all 3 next can crash with width < 2
      static CellsRow::ptr empty(size_t width, bool visible=true);
      static CellsRow::ptr random(size_t width, bool visible=true, int oneWallOf=3); // do not place wall at row ends

    private:
      size_t m_width;
      Cell::ptr* cells;
      CellsRow(size_t width);
  };
  
  class Map
  {
  public:
    using ptr = std::unique_ptr<Map>;
    Map(const Map&) = delete;
    Map(Map&&) = default;
    ~Map();
    void display();
    CellsRow::ptr& get(int index);
    const CellsRow& operator[](int index) const;

    static Map empty(size_t width, size_t height, bool visible=false);
    static Map walls(size_t width, size_t height, bool visible=false);
    static Map random(size_t width, size_t height, bool visible=false, int oneWallof=3);

  private:
    Map(size_t width, size_t height);
    size_t m_width=0, m_height=0;
    CellsRow::ptr* rows;
  };
  
//  struct Coord
//  {
//    size_t row=0, col=0;
//    Coord(size_t row, size_t column);
//    int dist(const Coord& coord);
//    int distR(const Coord& coord);
//    int distC(const Coord& coord);
//  };
//
//  class Room
//  {
//    public:
//      static const Coord MIN_SIZE;
//      Room(int top, int left, int width, int height);
//      int centroid() const;
//    private:
//      Coord tl, size;
//  };
}

