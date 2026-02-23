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
    Console con;
    std::cout << "Test set win size:" << std::endl;
    print(con.getScreenBufferInfo(), "\tbefore: ");
    std::cout << "\tPress key to resize " << w << 'x' << h << "..." << std::endl;
    getch();
    if (!con.setWindowSize(w, h))
      std::cout << "\tResize FAIL!!!" << std::endl;
    Debug_NS::print(con.getScreenBufferInfo(), "\tafter:  ");
  }
  
  void testFitBuffer()
  {
    std::cout << "Test fit buffer window" << std::endl;
    std::cout << "\tPress any key to fit buffer window (remove scroll bars)..." << std::endl;
    Console con;
    print(con.getScreenBufferInfo(), "\tbefore: ");
    getch();
    if (!con.fitBufferWindow())
      std::cout << "\tFAIL!, error code is " << ::GetLastError();
    print(con.getScreenBufferInfo(), "\tafter : ");
  }
  
  void testPut()
  {
    Console con;
    con.maximizeWindow();
    con.fitBufferWindow();
    std::cout << "Test put char/string" << std::endl;
    std::cout << "\tput '@' of random color:";
    for (short row = 3; row <= 10; ++row)
    {
      for (short col=9; col <=30; ++col)
      {
        con.putChar('@', row, col, Color::Random);
      }
    }
    con.setCusorPosition(14, 0);
    std::cout << "\tput colored strings" << std::endl;
    con.putString("string: Black      ", 15, 10, Color::Black      ); std::cout << " - Black";
    con.putString("string: Blue       ", 16, 10, Color::Blue       ); std::cout << " - Blue";
    con.putString("string: Green      ", 17, 10, Color::Green      ); std::cout << " - Green";
    con.putString("string: Cyan       ", 18, 10, Color::Cyan       ); std::cout << " - Cyan";
    con.putString("string: Red        ", 19, 10, Color::Red        ); std::cout << " - Red";
    con.putString("string: DarkMagenta", 20, 10, Color::DarkMagenta); std::cout << " - DarkMagenta";
    con.putString("string: DarkYellow ", 21, 10, Color::DarkYellow ); std::cout << " - DarkYellow";
    con.putString("string: White      ", 22, 10, Color::White      ); std::cout << " - White";
    con.putString("string: Grey       ", 23, 10, Color::Grey       ); std::cout << " - Grey";
    con.putString("string: BrightGreen", 24, 10, Color::BrightGreen); std::cout << " - BrightGreen";
    con.putString("string: LightBlue  ", 25, 10, Color::LightBlue  ); std::cout << " - LightBlue";
    con.putString("string: OrangeRed  ", 26, 10, Color::OrangeRed  ); std::cout << " - OrangeRed";
    con.putString("string: Magenta    ", 27, 10, Color::Magenta    ); std::cout << " - Magenta";
    con.putString("string: Yellow     ", 28, 10, Color::Yellow     ); std::cout << " - Yellow";
    con.putString("string: BrightWhite", 29, 10, Color::BrightWhite); std::cout << " - BrightWhite";
    con.putString("string: Random     ", 30, 10, Color::Random     ); std::cout << " - Random";
    con.setCusorPosition(con.getScreenBufferInfo().size.y-5, 0);
    std::cout << "press any key...";
    getch();
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
