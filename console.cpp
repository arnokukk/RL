#include <windows.h>
#include "console.hpp"

#include <conio.h>
#include <cstdio>
#include <stdexcept>


namespace
{
  int _arrowKey(int key)
  {
    switch (key)
    {
      case 71: // right-up (Home)
        return 2007;
      case 72: // up
        return 2008;
      case 73: // right-up (pgUp)
        return 2009;
      case 75: // left
        return 2004;
      case 77: // right
        return 2006;
      case 79: // left-down (End)
        return 2001;
      case 80: // down
        return 2002;
      case 81: // right-down (PgDn)
        return 2003;
      case 82: // Ins (NumPad 0)
        return 2010;
      case 83: // Del (NumPad ,)
        return 2011;
      default:
        return 0;
    }
  }
  
  int _getKey_0()
  {
    auto key = _getch();
    switch (key)
    {
      case 59:  // from F1
      case 60:
      case 61:
      case 62:
      case 63:
      case 64:
      case 65:
      case 66:
      case 67:
      case 68:  // to F10
        return 1000 + key - 58;
      case 71: // arrows, Ins, Del
      case 72:
      case 73:
      case 75:
      case 77:
      case 79:
      case 80:
      case 81:
      case 82:
      case 83:
        return _arrowKey(key);
      default:
        return 0;
    }
  }
  
  int _getKey_224()
  {
    auto key = _getch();
    switch (key)
    {
      case 71: // arrows, Ins, Del
      case 72:
      case 73:
      case 75:
      case 77:
      case 79:
      case 80:
      case 81:
      case 82:
      case 83:
        return _arrowKey(key);
      case 133: // F11
      case 134: // F12
        return 1000 + key - 122;
      default:
        return 0;
    }
  }
}

namespace
{
  SMALL_RECT winSmallRect(const Console_NS::Rect& rect)
  {
    SMALL_RECT sr{rect.tl.x, rect.tl.y, rect.br.x, rect.br.y};
    return sr;
  }
  
  HWND _getConsoleHWND()
  {
    const int SIZE = 1024;
    char tempTitle[SIZE];
    std::sprintf(tempTitle, "%lu/%lu", ::GetTickCount(), ::GetCurrentProcessId());
    ::SetConsoleTitle(tempTitle);
    ::Sleep(40);
    return ::FindWindow(NULL, tempTitle);
  }
}

namespace Console_NS
{
  ScreenBufferInfo::ScreenBufferInfo(const CONSOLE_SCREEN_BUFFER_INFO& info)
    : size(info.dwSize.X, info.dwSize.Y)
    , cursorPosition(info.dwCursorPosition.X, info.dwCursorPosition.Y)
    , attributes(info.wAttributes)
    , window(info.srWindow.Left, info.srWindow.Top, info.srWindow.Right, info.srWindow.Bottom)
    , maxWinSize(info.dwMaximumWindowSize.X, info.dwMaximumWindowSize.Y)
  {
  }
  
  ScreenBufferInfo ScreenBufferInfo::get(HANDLE handle/*=nullptr*/)
  {
    if (!handle)
      handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    return ScreenBufferInfo(info);
  }
  
  const char* Console::TITLE = "RL test";
  
  Console::Console() : m_console(GetStdHandle(STD_OUTPUT_HANDLE)), m_window(_getConsoleHWND())
  {
    ::SetConsoleTitle(this->TITLE);
    if (m_window == NULL)
    {
      throw std::runtime_error("FAIL!! m_window is NULL");
    }
  }

  ScreenBufferInfo Console::getScreenBufferInfo() const
  {
    return ScreenBufferInfo::get(m_console);
  }
  
  void Console::clearScreen(char filler/*=' '*/)
  {
    COORD tl = {0, 0};
    const auto info = this->getScreenBufferInfo();
    DWORD written = 0, cells = info.size.x * info.size.y;
    FillConsoleOutputCharacter(this->m_console, filler, cells, tl, &written);
    FillConsoleOutputAttribute(this->m_console, info.attributes, cells, tl, &written);
    SetConsoleCursorPosition(this->m_console, tl);
  }

  int Console::getChar()
  {
    int key = _getch();
    this->m_lastChar = 0;
    if (_kbhit())
    {
      switch (key)
      {
        case 0:  // F1-F10 key or NumPad arrows
          this->m_lastChar = _getKey_0();
          break;
        case 224:  // arrow or F11-F12 key
          this->m_lastChar = _getKey_224();
          break;
        default:  // unknown key
          break;
      }
    }
    else
    {
      this->m_lastChar = key;
    }
    return this->m_lastChar;
  }
  
  bool Console::setWinSize(int width, int heigth)
  {
    if (this->m_window == NULL) return false;
    return ::SetWindowPos(m_window, NULL, 0, 0, width, heigth, SWP_NOZORDER);
  }
  
  void Console::resizeWindow(const Rect& rect)
  {
    auto sr = winSmallRect(rect);
    SetConsoleWindowInfo(this->m_console, true, &sr);
  }
}
