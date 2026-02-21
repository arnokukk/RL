#include "test_console.hpp"

#include <windows.h>
#include <iostream>
#include <conio.h>


namespace
{
}

int main()
{
  // Test_NS::testGetch(10);
  Test_NS::testWinResize(1920, 1080);
  Test_NS::testFitBuffer();
  return 0;
}
