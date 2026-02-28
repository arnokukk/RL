#include "test_console.hpp"

#include "console.hpp"
#include "prints.hpp"

#include <conio.h>
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>


namespace Test_NS
{
  using namespace Debug_NS;
  using namespace Console_NS;
  
  namespace
  {
    void pressKeyToContinue(Console& console, const std::string& label = "Press key to continue...")
    {
      std::cout << std::endl << label << std::endl;
      console.getChar();
    }
  }
  
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
  
  int testWinResize(int w/*=1920*/, int h/*=1080*/)
  {
    Console con;
    std::cout << "Test set win size:" << std::endl;
    print(con.getScreenBufferInfo(), "\tbefore: ");
    std::cout << "\tPress key to resize " << w << 'x' << h << "..." << std::endl;
    con.getChar();
    if (!con.setWindowSize(w, h))
    {
      std::cout << "\tResize FAIL!!!" << std::endl;
      return 1;
    }
    Debug_NS::print(con.getScreenBufferInfo(), "\tafter:  ");
    pressKeyToContinue(con);
    return 0;
  }
  
  int testFitBuffer()
  {
    Console con;
    print(con.getScreenBufferInfo(), "\tbefore: ");
    std::cout << "\tPress any key to fit buffer window (remove scroll bars)..." << std::endl;
    con.getChar();
    if (!con.fitBufferWindow())
    {
      std::cout << "\tFAIL!, error code is " << ::GetLastError();
      return 1;
    }
    print(con.getScreenBufferInfo(), "\tafter : ");
    pressKeyToContinue(con);
    return 0;
  }
  
  int testPut()
  {
    Console con;
    con.init("TEST put");
    std::cout << "\tput '@' of random color:";
    for (short row = 3; row <= 10; ++row)
    {
      for (short col=9; col <=30; ++col)
      {
        con.put('@', row, col, Color::Random);
      }
    }
    con.setCusorPosition(14, 0);
    std::cout << "\tcolored strings:" << std::endl;
    con.put("string: Black      ", 15, 10, Color::Black      ); std::cout << " - Black";
    con.put("string: Blue       ", 16, 10, Color::Blue       ); std::cout << " - Blue";
    con.put("string: Green      ", 17, 10, Color::Green      ); std::cout << " - Green";
    con.put("string: Cyan       ", 18, 10, Color::Cyan       ); std::cout << " - Cyan";
    con.put("string: Red        ", 19, 10, Color::Red        ); std::cout << " - Red";
    con.put("string: DarkMagenta", 20, 10, Color::DarkMagenta); std::cout << " - DarkMagenta";
    con.put("string: DarkYellow ", 21, 10, Color::DarkYellow ); std::cout << " - DarkYellow";
    con.put("string: White      ", 22, 10, Color::White      ); std::cout << " - White";
    con.put("string: Grey       ", 23, 10, Color::Grey       ); std::cout << " - Grey";
    con.put("string: BrightGreen", 24, 10, Color::BrightGreen); std::cout << " - BrightGreen";
    con.put("string: LightBlue  ", 25, 10, Color::LightBlue  ); std::cout << " - LightBlue";
    con.put("string: OrangeRed  ", 26, 10, Color::OrangeRed  ); std::cout << " - OrangeRed";
    con.put("string: Magenta    ", 27, 10, Color::Magenta    ); std::cout << " - Magenta";
    con.put("string: Yellow     ", 28, 10, Color::Yellow     ); std::cout << " - Yellow";
    con.put("string: BrightWhite", 29, 10, Color::BrightWhite); std::cout << " - BrightWhite";
    con.put("string: Random     ", 30, 10, Color::Random     ); std::cout << " - Random";

    con.putFitted("press any key...", -5, 0);
    con.getChar();
    return 0;
  }
  
  std::vector<std::string> getCharTable(int columns)
  {
    std::vector<std::string> result;
    auto ch2str = [](char c) {
      char buff[25];
      std::sprintf(buff, "%04d: '%c'", static_cast<int>(c), c);
      return std::string(buff);
    };
    int col = 1;
    std::ostringstream stream;
    for (char c = std::numeric_limits<char>::min(); c <= std::numeric_limits<char>::max(); ++c)
    {
      if ((7 <= c && c <= 10) || c == 13 || c == 0) continue;
      stream << ch2str(c) << "    ";
      col++;
      if (col >= columns)
      {
        result.push_back(stream.str());
        stream.str("");
        stream.clear();
        col = 1;
      }
      if (c == std::numeric_limits<char>::max())
      {
        result.push_back(stream.str());
        break;
      }
    }
    return result;
  }
  
  int testChars()
  {
    Console con;
    con.init("TEST chars");
    auto info = con.getScreenBufferInfo();
    con.put(Debug_NS::toString(info), 0, 5);
    std::string s(con.getScreenBufferInfo().size.x + 1, '=');
    const std::string r(" this is a very long string ");
    s.replace(10, r.size(), r);
    if (!con.putFitted(s, 2, 3, Color::BrightWhite)) return 1;
    if (!con.putFitted("right aligned", 3, -15, Color::BrightWhite)) return 1;
    if (con.putFitted("no output", 1000, 0)) return 1;
    if (con.putFitted("no output", -1000, 0)) return 1;
    if (con.putFitted("no output", 0, 1000)) return 1;
    if (con.putFitted("no output", 0, -1000)) return 1;
    con.put("Char table (skipped chars: 0, 7-10, 13):\n", 10, 8);
    for (const auto& s: getCharTable(16))
      if (!s.empty()) std::cout << s << std::endl;
    con.putFitted("press any key...", -2, 0, Color::Red);
    con.getChar();
    return 0;
  }
  
  int testCharTable()
  {
    auto strings = getCharTable(12);
    for (const auto& str: strings)
    {
      if (str.empty()) continue;
      std::cout << str << std::endl;
    }
    return 0;
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
