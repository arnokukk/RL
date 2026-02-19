#include "test_console.hpp"

#include <conio.h>
#include <iostream>

#include "console.hpp"
//#include "geometry.hpp"
#include "prints.hpp"

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
  
  void testGetch()
  {
    Console con;
    std::cout << "Get char test:" << std::endl;
    std::cout << "\tpress any key..." << std::endl;
    auto got = con.getChar();
    std::cout << "\tkey " << got << " pressed (" << (char)got << ")" << std::endl;
  }
  
  void testWinResize(short w, short h)
  {
    Console con;
    std::cout << "Window resize test:" << std::endl;
    std::cout << "\tbefore: " << toString(con.getScreenBufferInfo()) << std::endl;
    std::cout << "\tPress any key to resize window..." << std::endl;
    getch();
    con.resizeWindow(Rect(0, 0, 100, 25));
    std::cout << "\tafter:  " << toString(con.getScreenBufferInfo()) << std::endl;
  }
  
  void test_setTopWinSize(short w, short h)
  {
    auto top = ::GetTopWindow(NULL);
    bool isNull = top == NULL;
    char title[256];
    GetWindowText(top, title, sizeof(title));
    std::cout << "Top win title is \"" << title << "\" " << isNull << std::endl;
    std::cout << "Press key to resize to " << w << 'x' << h << "..." << std::endl;
    getch();
    auto success = SetWindowPos(top, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
    if (!success)
      std::cout << "resize failed" << std::endl;
  }
  
  void testConsole()
  {
//    testClearScreen();
//    testConsoleScreenfufferInfo();
//    testManResize();
//    testGetch();
    testWinResize(3500, 1500);
  }
}
