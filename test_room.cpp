#include "test_room.hpp"

#include "room.hpp"
#include "map.hpp"
#include "room_placer.hpp"
#include "prints.hpp"
#include "console.hpp"

#include <iostream>

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
    Console_NS::Console con;
    con.init("test map with rectangle rooms");
    auto size = con.getScreenBufferInfo().size;
    const unsigned ROWS = size.y - 10, COLS = size.x - 1;
    const unsigned ROOMS = 25, MIN_SIZE = 5, RATIO = 6;//, PATHS = 2;
    Map map = Map::walls(COLS, ROWS, true);
    RoomPlacer placer(map.size());
    placer.createRooms(ROOMS, MIN_SIZE, RATIO);
    //placer.createPaths(PATHS);
    placer.placeRooms(map, true);
    //placer.placePaths(map, true);
    map.display();
    std::cout << '\t' << Debug_NS::toString(map.size()) << " map with " << placer.roomQty() << " rectangle rooms" <<
      std::endl << '\t' << placer.connectedQty() << " rooms connected of " << placer.roomQty() << std::endl;
    con.putFitted("Press any key...", -2, 8);
    con.getChar();
    con.clearScreen();
    {
      unsigned rooms = 30;
      auto map = RoomPlacer::createMap(Coord(ROWS, COLS), rooms, true);
      map.display();
      std::cout << '\t' << Debug_NS::toString(map.size()) << " map with " << rooms << " rectangle rooms" << std::endl;
      con.putFitted("Press any key...", -2, 8);
      con.getChar();
    }
    return 0;
  }
}
