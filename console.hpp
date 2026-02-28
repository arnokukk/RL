#pragma once

#include <windows.h>
#include "geometry.hpp"
#include "colors.hpp"

#include <string>


namespace Console_NS
{
  struct ScreenBufferInfo
  {
    Coord size;
    Coord cursorPosition;
    unsigned short attributes{0};
    Rect window;
    Coord maxWinSize;
    
    ScreenBufferInfo() = default;
    ScreenBufferInfo(const CONSOLE_SCREEN_BUFFER_INFO& info);
    
    static ScreenBufferInfo get(HANDLE handle=nullptr);
  };
  
  class Console
  {
    public:
      Console();
      
      int getChar();
      void init(const std::string& title="rl test");
      bool setCusorPosition(short row, short column);
      bool put(char c, short row, short col, Color attr=Color::White);
      bool put(const std::string& s, short row, short col, Color attr=Color::White);
      bool putFitted(std::string s, short row, short col, Color attr=Color::White);

      ScreenBufferInfo getScreenBufferInfo() const;
      void clearScreen(char filler=' ');
      bool setTextAttribute(WORD attr);
      bool setWindowSize(int width, int height);
      bool maximizeWindow();
      bool fitBufferWindow();
    
    private:
      HANDLE m_console = NULL;
      HWND m_window = NULL;
      int m_lastChar = 0;
  };
}
