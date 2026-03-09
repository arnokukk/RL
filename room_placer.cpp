#include "room_placer.hpp"
#include "map.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

#include <iostream>


namespace Game_NS
{
  RoomPlacer::RoomPlacer(const Coord& mapSize) : m_mapSize(mapSize)
  {
  }
  
  unsigned RoomPlacer::roomQty() const
  {
    return m_rooms.size();
  }
  
  unsigned RoomPlacer::connectedQty() const
  {
    return m_connected.size();
  }
  
  void RoomPlacer::createRoom(unsigned minSize, unsigned ratio)
  {
    try
    {
      m_rooms.push_back(Room::random(m_mapSize, minSize, ratio));
      const Room& created = m_rooms.back();
      m_connections[&created] = {};
    }
    catch (std::runtime_error&)
    {
      std::cerr << "RoomPlacer::createRoom FAILED!" << std::endl;
    }
  }
  
  void RoomPlacer::createRooms(unsigned quantity, unsigned minSize, unsigned ratio)
  {
    m_rooms.reserve(quantity);
    for (unsigned i=0; i<quantity; i++)
    {
      createRoom(minSize, ratio);
    }
  }
  
  void RoomPlacer::createPath(const Room& src, const Room& dst)
  {
    auto path = src.makePath(dst);
    if (!path.empty())
    {
      m_paths.push_back(src.makePath(dst));
    }
    m_connected.insert(&dst);
    m_connections[&src].insert(&dst);
    m_connections[&dst].insert(&src);
  }
  
  const Room* RoomPlacer::findClosestNotConnectedWith(const Room& src)
  {
    unsigned minDist = std::numeric_limits<unsigned>::max();
    const Room* closest = nullptr;
    for (const Room& dst: m_rooms)
    {
      if (&src == &dst  || m_connections[&src].count(&dst)) continue;
      unsigned dist = src.centroid().dist(dst.centroid());
      if (dist < minDist)
      {
        minDist = dist;
        closest = &dst;
      }
    }
    return closest;
  }

  const Room* RoomPlacer::findClosestNotConnected(const Room& src)
  {
    unsigned minDist = std::numeric_limits<unsigned>::max();
    const Room* closest = nullptr;
    for (const Room& dst: m_rooms)
    {
      if (&src == &dst || m_connected.count(&dst)) continue;
      unsigned dist = src.centroid().dist(dst.centroid());
      if (dist < minDist)
      {
        minDist = dist;
        closest = &dst;
      }
    }
    return closest;
  }

  void RoomPlacer::createPaths(unsigned perRoom)
  {
    if (m_rooms.empty())
      return;
    m_connected.insert(&m_rooms.front());

    const auto* src = &m_rooms.front();
    const auto* dst = src;
    while (dst != nullptr)
    {
      dst = this->findClosestNotConnected(*src);
      if (dst)
      {
        this->createPath(*src, *dst);
      }
    }

    for (unsigned i=1; i<perRoom; i++)
    {
      for (const Room& src: m_rooms)
      {
        if (m_connections[&src].size() >= perRoom) continue;
        const Room* dst = findClosestNotConnectedWith(src);
        if (dst)
          this->createPath(src, *dst);
      }
    }
  }
  
  namespace
  {
    void placeRoom(Map& map, const Room& room, bool visible=false)
    {
      for (unsigned row=room.position().row(); row < room.position().row() + room.size().row(); row++)
      {
        for (unsigned col=room.position().col(); col < room.position().col() + room.size().col(); col++)
        {
          map.place<Floor>(row, col, visible);
        }
      }
    }
    
    void placePath(Map& map, const Coord::Path& path, bool visible=false)
    {
      for (const Coord& coord: path)
      {
        map.place<Floor>(coord.row(), coord.col(), visible);
      }
    }
  }
  
  void RoomPlacer::placeRooms(Map& map, bool visible/*=false*/)
  {
    for (const Room& room: m_rooms)
    {
      placeRoom(map, room, visible);
    }
  }

  void RoomPlacer::placePaths(Map& map, bool visible/*=false*/)
  {
    for (const auto& path: m_paths)
    {
      placePath(map, path, visible);
    }
  }
  
  Map RoomPlacer::createMap(const Coord& size, unsigned rooms, bool visible/*=false*/,
                            unsigned minSize/*=3*/, unsigned paths/*=2*/, unsigned ratio/*=7*/)
  {
    Map map = Map::walls(size.col(), size.row(), visible);
    RoomPlacer placer(map.size());
    placer.createRooms(rooms, minSize, ratio);
    placer.placeRooms(map, visible);
    placer.createPaths(paths);
    placer.placePaths(map, visible);
    return map;
  }
}
