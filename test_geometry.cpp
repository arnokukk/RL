#include <iostream>

#include "test_geometry.hpp"
#include "prints.hpp"
#include "geometry.hpp"
#include "console.hpp"

namespace Test_NS
{
  using namespace Debug_NS;
  using namespace Console_NS;
  
  int testCoord()
  {
    std::cout << "Coord test:" << std::endl;
    std::cout << "\tdefault: " << toString(Coord()) << std:: endl;
    std::cout << "\tcustom (42,69): " << toString(Coord(42, 69)) << std::endl;
    return 0;
  }

  int testRectangle()
  {
    std::cout << "Rectangle test:" << std::endl;
    std::cout << "\tdefault: " << toString(Rect()) << std:: endl;
    std::cout << "\tby Coord: " << toString(Rect(Coord(1, 1), Coord(5, 5))) << std::endl;
    std::cout << "\tby x, y: " << toString(Rect(1, 1, 5, 5)) << std::endl;
    Rect rect(1, 1, 5, 6);
    std::cout << "\tsize of Rect " << toString(rect) << " is " << rect.width() << 'x' << rect.height() << std::endl;
    return 0;
  }

  int testGeometry()
  {
    int result = 0;
    result += testCoord();
    result += testRectangle();
    return result;
  }
}

