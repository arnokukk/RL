#pragma once
#include "room.hpp"

#include <string>

namespace Game_NS
{
  struct HP
  {
    static const int DEFAULT = 5;
    HP(int _max=0);
    int max, cur = 0;
  };
  
  class Hero
  {
    public:
      Hero() = default;
      bool isAlive() const;
      
      unsigned lightRadius() const;

    private:
      std::string m_name;
      HP m_hp;
      Coord m_coord{0, 0};
  };
}
