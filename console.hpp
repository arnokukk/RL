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
      bool setCusorPosition(short row, short column);
      bool setTextAttribute(WORD attr);
      bool putChar(char c, short row, short col, Color attr);
      bool putString(const std::string& s, short row, short col, Color attr);

      ScreenBufferInfo getScreenBufferInfo() const;
      void clearScreen(char filler=' ');
      bool setWindowSize(int width, int height);
      bool maximizeWindow();
      bool fitBufferWindow();
    
    private:
      HANDLE m_console = NULL;
      HWND m_window = NULL;
      int m_lastChar = 0;
      
      static const char* TITLE;
  };
}
