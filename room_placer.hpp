#pragma once
#include "room.hpp"

#include <vector>
#include <map>
#include <set>

namespace Game_NS
{
  class Map;
  
  class RoomPlacer
  {
    public:
      RoomPlacer(const Coord& mapSize);
      unsigned roomQty() const;
      unsigned connectedQty() const;
      
      static Map createMap(const Coord& size, unsigned rooms, bool visible=false,
                           unsigned minSize=3, unsigned paths=2, unsigned ratio=7);
      
      void createRooms(unsigned quantity, unsigned minSize, unsigned ratio);
      void createPaths(unsigned perRoom);
      void closeConnectivity();
      
      void placeRooms(Map& map, bool visible=false);
      void placePaths(Map& map, bool visible=false);
      
    private:
      void createRoom(unsigned minSize, unsigned ratio);
      void createPath(const Room& src, const Room& dst);
      const Room* findClosestNotConnectedWith(const Room& room);
      const Room* findClosestNotConnected(const Room& room);
//      bool connected(const Room& room);
//      void updateConnectivity(unsigned count=1);
//      void updateConnectivity(const Room& room);
    private:
      Coord m_mapSize;
      std::vector<Room> m_rooms;
      std::vector<Coord::Path> m_paths;
      std::map<const Room*, std::set<const Room*>> m_connections;
      std::set<const Room*> m_connected;
  };
}
