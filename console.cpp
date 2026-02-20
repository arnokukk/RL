#include <windows.h>
#include "console.hpp"

#include "get_char.hpp"

#include <cstdio>
#include <stdexcept>


namespace
{
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
    this->m_lastChar = getCharacter();
    return this->m_lastChar;
  }
  
  bool Console::setWinSize(int width, int heigth)
  {
    if (this->m_window == NULL) return false;
    return ::SetWindowPos(m_window, NULL, 0, 0, width, heigth, SWP_NOZORDER);
  }
}
