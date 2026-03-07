#include <windows.h>
#include "console.hpp"

#include "get_char.hpp"

#include <cstdio>
#include <stdexcept>
#include <iostream>
#include <random>
#include <chrono>
#include <sstream>


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
  
  WORD toWord(Console_NS::Color color)
  {
    static std::mt19937 engine(std::chrono::system_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<unsigned short> distr(0X01, 0X0F);
    if (color == Console_NS::Color::Random)
    {
      return distr(engine);
    }
    return static_cast<WORD>(color);
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
  
  Console::Console() : m_console(::GetStdHandle(STD_OUTPUT_HANDLE)), m_window(_getConsoleHWND())
  {
    if (m_console == NULL)
      throw std::runtime_error("FAIL!! m_console is NULL");
    if (m_window == NULL)
      throw std::runtime_error("FAIL!! m_window is NULL");
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
  
  bool Console::setWindowSize(int width, int heigth)
  {
    if (this->m_window == NULL) return false;
    return ::SetWindowPos(m_window, NULL, 0, 0, width, heigth, SWP_NOZORDER);
  }
  
  bool Console::setConsoleSize(short width, short height)
  {
    std::ostringstream s;
    s << "mode " << width << ", " << height;
    return !::system(s.str().c_str());
  }
  
  bool Console::maximizeWindow()
  {
    return ::ShowWindow(m_window, SW_MAXIMIZE);
  }
  
  bool Console::fitBufferWindow()
  {
    auto info = this->getScreenBufferInfo();
    short w = 1 + info.window.br.x - info.window.tl.x, h = 1 + info.window.br.y - info.window.tl.y;
    COORD size{w, h};
    return ::SetConsoleScreenBufferSize(m_console, size);
  }
  
  bool Console::setCusorPosition(short row, short column)
  {
    COORD coord{column, row};
    return ::SetConsoleCursorPosition(m_console, coord);
  }
  
  bool Console::setTextAttribute(WORD attr)
  {
    return ::SetConsoleTextAttribute(m_console, attr);
  }
  
  bool Console::put(char c, short row, short col, Color color/*=Color::white*/)
  {
    if (!setCusorPosition(row, col)) return false;
    std::cout << c;
    COORD coord{col, row};
    DWORD written{0};
    return ::FillConsoleOutputAttribute(m_console, toWord(color), 1, coord, &written);
  }

  bool Console::put(const std::string& s, short row, short col, Color color/*=Color::white*/)
  {
    if (!setCusorPosition(row, col)) return false;
    std::cout << s;
    COORD coord{col, row};
    DWORD written{0};
    return ::FillConsoleOutputAttribute(m_console, toWord(color), s.size(), coord, &written);
  }
  
  bool Console::putFitted(std::string s, short row, short col, Color attr/*=Color::White*/)
  {
    const auto size = this->getScreenBufferInfo().size;
    if (col < 0) col += size.x;
    if (row < 0) row += size.y;
    if (!this->setCusorPosition(row, col)) return false;
    size_t fitted = static_cast<size_t>(size.x - col); // now it's greater than zero
    if (s.size() > fitted) s.resize(fitted);
    std::cout << s;
    COORD coord{col, row};
    DWORD written{0};
    return ::FillConsoleOutputAttribute(m_console, toWord(attr), s.size(), coord, &written);
  }
  
  void Console::init(const std::string& title)
  {
    if (!maximizeWindow())
      throw std::runtime_error("Console::maximizeWindow failed");
    if (!fitBufferWindow())
      throw std::runtime_error("Console::fitBufferWindow failed");
    ::SetConsoleTitle(title.c_str());
    clearScreen();
  }
}
