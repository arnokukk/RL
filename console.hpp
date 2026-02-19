#pragma once

#include <windows.h>
#include "geometry.hpp"


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
      
      ScreenBufferInfo getScreenBufferInfo() const;
      void clearScreen(char filler=' ');
      int getChar();
      bool           setWinSize(int width, int height);
      void resizeWindow(const Rect& rectangle);
    
    private:
      HANDLE m_console = NULL;
      HWND m_window = NULL;
      int m_lastChar = 0;
      
      static const char* TITLE;
  };
}
