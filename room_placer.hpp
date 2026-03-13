#pragma once
#include "room.hpp"
#include "map.hpp"

#include <vector>
#include <map>
#include <set>

namespace Game_NS
{
  struct MapR
  {
    MapR(const Coord& size, bool visible=false);
    MapR(const MapR&) = delete;
    MapR(MapR&&) = default;
    Map map;
    std::vector<Room> rooms;
  };
  
  class RoomPlacer
  {
    public:
      RoomPlacer(const Coord& mapSize);
     
      static MapR createMap(const Coord& size, unsigned rooms, bool visible=false,
                            unsigned minSize=3, unsigned paths=2, unsigned ratio=7);
      const std::vector<Room>& rooms() const;
      
      void createRooms(unsigned quantity, unsigned minSize, unsigned ratio);
      void createPaths(unsigned perRoom);
      
      void placeRooms(Map& map, bool visible=false);
      void placePaths(Map& map, bool visible=false);
      
    private:
      void createRoom(unsigned minSize, unsigned ratio);
      void createPath(const Room& src, const Room& dst);
      const Room* findClosestNotConnectedWith(const Room& room);
      const Room* findClosestNotConnected(const Room& room);
    private:
      Coord m_mapSize;
      std::vector<Room> m_rooms;
      std::vector<Coord::Path> m_paths;
      std::map<const Room*, std::set<const Room*>> m_connections;
      std::set<const Room*> m_connected;
  };
}
