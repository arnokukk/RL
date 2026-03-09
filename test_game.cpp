#include "test_game.hpp"
#include "main_fwd.hpp"
#include "map.hpp"
#include "room.hpp"

#include <iostream>
#include <chrono>
#include <random>
#include <conio.h>

namespace Test_NS
{
  using namespace Game_NS;
  
  int testWindow()
  {
    return testInWindow("chars", "/C");
  }
  
  int testRow()
  {
    {
      auto row = Game_NS::CellsRow::border(45, true);
      std::cout << "Border row (top/bottom) of size " << row->width() << std::endl;
      std::cout << row->str() << std::endl << std::endl;
    }
    {
      auto row = Game_NS::CellsRow::empty(40, true);
      std::cout << "Empty row (floor everywhere) of size " << row->width() << std::endl;
      std::cout << row->str() << std::endl << std::endl;
    }
    {
      auto row = Game_NS::CellsRow::random(50, true);
      std::cout << "Random row (one wall of 3 cells) of size " << row->width() << std::endl;
      std::cout << row->str() << std::endl << std::endl;
    }
    return 0;
  }
  
  int testMap(size_t w, size_t h)
  {
    using namespace std::chrono;
    {
      std::cout << "Empty map " << w << "x" << h << ":" << std::endl;
      const auto start = high_resolution_clock::now();
      Map map = Map::empty(w, h, true);
      const auto generated = high_resolution_clock::now();
//      map.display();
      const auto displayed = high_resolution_clock::now();
      const auto gen_time = duration_cast<milliseconds>(generated - start);
      const auto dis_time = duration_cast<milliseconds>(displayed - generated);
      std::cout << "Generation time: " << gen_time.count() << "ms; ";
      std::cout << "Display time: " << dis_time.count() << "ms" << std::endl;
    }
    std::cout << "Press key to continue..." << std::endl;
    getch();
    {
      std::cout << "Walls everywhere map " << w << "x" << h << ":" << std::endl;
      const auto start = high_resolution_clock::now();
      Map map = Map::walls(w, h, true);
      const auto generated = high_resolution_clock::now();
      map.place<Floor>(2, 2, true);
      map.place<Floor>(2, 3, true);
      map.place<Floor>(3, 2, true);
      map.place<Wall>(2, 2, true);
      map.display();
      const auto displayed = high_resolution_clock::now();
      const auto gen_time = duration_cast<milliseconds>(generated - start);
      const auto dis_time = duration_cast<milliseconds>(displayed - generated);
      std::cout << "Generation time: " << gen_time.count() << "ms; ";
      std::cout << "Display time: " << dis_time.count() << "ms" << std::endl;
    }
    std::cout << "Press key to continue..." << std::endl;
    getch();
    {
      std::cout << "Random map " << w << "x" << h << ":" << std::endl;
      const auto start = high_resolution_clock::now();
      Map map = Map::random(w, h, true, 4);
      const auto generated = high_resolution_clock::now();
//      map.display();
      const auto displayed = high_resolution_clock::now();
      const auto gen_time = duration_cast<milliseconds>(generated - start);
      const auto dis_time = duration_cast<milliseconds>(displayed - generated);
      std::cout << "Generation time: " << gen_time.count() << "ms; ";
      std::cout << "Display time: " << dis_time.count() << "ms" << std::endl;
    }
    return 0;
  }

  namespace
  {
    void testDist(const Coord& a, const Coord& b)
    {
      std::cout << "a: " << a.row() << "x" << a.col() << ", b: " << b.row() << "x" << b.col() << std::endl;
      std::cout << "a-b (row): " << a.distRow(b) << " == " << b.distRow(a) << ",\t";
      std::cout << "a-b (col): " << a.distCol(b) << " == " << b.distCol(a) << std::endl;
      std::cout << "a-b: " << a.dist(b) << " == " << b.dist(a) << ";\t\t";
      std::cout << "a-a: " << a.dist(a) << " == " << b.dist(b) << " == 0" << std::endl << std::endl;
    }
    
    Coord randomCoord()
    {
      static const unsigned MIN = 2, MAX = 50;
      static std::mt19937 gen((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
      static std::uniform_int_distribution<unsigned> dstr(MIN, MAX);
      return Coord(dstr(gen), dstr(gen));
    }
    
    std::ostream& operator<<(std::ostream& out, const Coord& p)
    {
      out << p.row() << 'x' << p.col();
      return out;
    }
  }

  int testGameCoord()
  {
    testDist(Coord(2,6), Coord(5, 2));
    for (int i=1; i<8; i++)
    {
      testDist(randomCoord(), randomCoord());
    }
    return 0;
  }
  
  int testPath()
  {
    for (int i =0; i<5; i++)
    {
    Coord x = randomCoord(), y = randomCoord();
    auto path = x.makePath(y);
    std::cout << x << std::endl;
    for (const auto& c: path)
      std::cout << c << ", ";
    std::cout << std::endl << y << std::endl << std::endl;
    }
    return 0;
  }
}

