#include "test_room.hpp"

#include "room.hpp"
#include "map.hpp"
#include "room_placer.hpp"
#include "prints.hpp"
#include "console.hpp"

#include <iostream>
#include <chrono>

namespace Test_NS
{
  using namespace Game_NS;
  
  namespace
  {
    void displayPath(const Coord::Path& path)
    {
      if (path.empty())
      {
        std::cout << "Empty path" << std::endl;
        return;
      }
      std::cout << Debug_NS::toString(path.front());
      for (size_t i=1; i<path.size(); i++)
        std::cout << ", " << Debug_NS::toString(path.at(i));
      std::cout << std::endl;
    }
  }
  
  int testRoom()
  {
    const Coord mapSize(10, 10);
    std::cout << "Test rooms at 10x10 map" << std::endl;
    Room a = Room::random(mapSize, 3, 2);
    Room b = Room::random(mapSize, 3, 2);
    Debug_NS::print(a, "A ");
    Debug_NS::print(b, "B ");
    std::cout << (a.intersects(b) ? "A intersects B" : "No intersection") << std::endl;
    std::cout << "Path from A to B: ";
    displayPath(a.makePath(b));
    std::cout << "Path from A to B top left corner: ";
    displayPath(a.makePath(b.position()));
    return 0;
  }
  
  int testPlacer()
  {
    const unsigned rooms = 40;
    Console_NS::Console con;
    con.init("test map with rectangle rooms");
    const auto size = con.getScreenBufferInfo().size;
    const unsigned ROWS = size.y - 10, COLS = size.x - 1;
    using namespace std::chrono;
    const auto start = high_resolution_clock::now();
    auto map = RoomPlacer::createMap(Coord(ROWS, COLS), rooms, true);
    const auto generated = high_resolution_clock::now();
    map.display();
    const auto displayed = high_resolution_clock::now();
    std::cout << '\t' << Debug_NS::toString(map.size()) << " map with " << rooms << " rectangle rooms" << std::endl;
    const auto gen_ms = duration_cast<milliseconds>(generated - start).count();
    const auto dis_ms = duration_cast<milliseconds>(displayed - generated).count();
    std::cout << "\tgeneration time: " << gen_ms << "ms, display time: " << dis_ms << "ms" << std::endl;
    con.putFitted("Press any key...", -2, 8);
    con.getChar();
    return 0;
  }
}
