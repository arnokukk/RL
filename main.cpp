#include "test_console.hpp"
#include "console.hpp"
#include "prints.hpp"

#include <iostream>
#include <conio.h>

namespace
{
  void testSetWinSize(int w, int h)
  {
    Console_NS::Console con;
    std::cout << "Test set win size:" << std::endl;
    Debug_NS::print(con.getScreenBufferInfo(), "\tbefore: ");
    std::cout << "\tPress key to resize " << w << 'x' << h << "..." << std::endl;
    getch();
    if (!con.setWinSize(w, h))
      std::cout << "\tFAIL!!!" << std::endl;
    Debug_NS::print(con.getScreenBufferInfo(), "\tafter:  ");
  }
}

int main()
{
  testSetWinSize(1920, 1080);
  return 0;
}
