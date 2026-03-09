#pragma once
#include <memory>

namespace Game_NS
{
  class Coord;
  
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
      Cell::ptr& get(unsigned col);
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
    
    Coord size() const;
    void display();
    CellsRow::ptr& get(unsigned row);
    Cell::ptr& get(unsigned row, unsigned col);
    const CellsRow& operator[](int index) const;

    template <typename T, typename std::enable_if<std::is_base_of<Cell, T>::value>::type* = nullptr>
    void place(unsigned row, unsigned col, bool visible=false)
    {
      get(row, col).reset(new T(visible));
    }

    static Map empty(size_t width, size_t height, bool visible=false);
    static Map walls(size_t width, size_t height, bool visible=false);
    static Map random(size_t width, size_t height, bool visible=false, int oneWallof=3);

  private:
    Map(size_t width, size_t height);
    size_t m_width=0, m_height=0;
    CellsRow::ptr* rows;
  };
}

