#include "test_console.hpp"

#include "console.hpp"
#include "prints.hpp"

#include <conio.h>
#include <iostream>


namespace Test_NS
{
  using namespace Debug_NS;
  using namespace Console_NS;
  
  void testConsoleScreenfufferInfo()
  {
    std::cout << "ScreenBufferInfo test:" << std::endl;
    std::cout << "\tdefault: " << toString(ScreenBufferInfo()) << std::endl;
    std::cout << "\tcurrent: " << toString(ScreenBufferInfo::get()) << std::endl;
  }
  
  void testManResize()
  {
    std::cout << "Manual window resize test:" << std::endl;
    std::cout << "\tbefore: " << toString(ScreenBufferInfo::get()) << std::endl;
    std::cout << "\tResize console window and press any key..." << std::endl;
    getch();
    std::cout << "\tafter:  " << toString(ScreenBufferInfo::get()) << std::endl;
  }
  
  void testClearScreen()
  {
    Console con;
    std::cout << "Clear screen test:" << std::endl;
    std::cout << "Press any key, and screen will be filled by '#'..." << std::endl;
    getch();
    con.clearScreen('#');
    std::cout << "Press any key, and screen will be cleared..." << std::endl;
    getch();
    con.clearScreen();
  }
  
  void testGetch(int count/*=1*/)
  {
    Console con;
    for (int i=0; i<count; i++)
    {
      std::cout << "Get char test:" << std::endl;
      std::cout << "\tpress any key..." << std::endl;
      auto got = con.getChar();
      std::cout << "\tkey " << got << " pressed (" << (char)got << ")" << std::endl;
    }
  }
  
  void testWinResize(int w/*=1920*/, int h/*=1080*/)
  {
    Console_NS::Console con;
    std::cout << "Test set win size:" << std::endl;
    Debug_NS::print(con.getScreenBufferInfo(), "\tbefore: ");
    std::cout << "\tPress key to resize " << w << 'x' << h << "..." << std::endl;
    getch();
    if (!con.setWinSize(w, h))
      std::cout << "\tResize FAIL!!!" << std::endl;
    Debug_NS::print(con.getScreenBufferInfo(), "\tafter:  ");
    std::cout << "\tPress key to maximize window..." << std::endl;
    getch();
    if (!con.maximizeWin())
      std::cout << "\tMaximize FAIL!!!" << std::endl;
    Debug_NS::print(con.getScreenBufferInfo(), "\tmax:    ");
  }
  
  void testConsole()
  {
    testClearScreen();
    testConsoleScreenfufferInfo();
    testManResize();
    testGetch();
    testWinResize();
  }
}
