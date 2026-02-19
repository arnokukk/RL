#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <iostream>

#include <windows.h>


namespace Console_NS
{
//  class Coord
//  {
//    public:
//      short x{0}, y{0};
//      
//      explicit Coord(const COORD& coord) noexcept : x(coord.X), y(coord.Y) {}
//      Coord(short x, short y) noexcept : x(x), y(y) {}
//  };
//  std::ostream& operator<<(std::ostream& out, const Coord& coord);
//
//  class Rectangle
//  {
//    public:
//      Coord topLeft, bottomRight;
//      
//      Rectangle(const Coord& tl, const Coord& br) noexcept;
//      explicit Rectangle(const SMALL_RECT& rect) noexcept;
//      
//      SMALL_RECT smallRect() const;
//      void foo();
//  };
//  std::ostream& operator<<(std::ostream& out, const Rectangle& rect);

  
//  class Console
//  {
//  public:
//    Console() noexcept;
//    
//    Coord getSize(CONSOLE_SCREEN_BUFFER_INFO* info = nullptr) const noexcept;
//    Coord getCursorPosition(CONSOLE_SCREEN_BUFFER_INFO* info = nullptr) const noexcept;
//    Coord getMaxWinSize(CONSOLE_SCREEN_BUFFER_INFO* info = nullptr) const noexcept;
//    Rectangle getWindowRect(CONSOLE_SCREEN_BUFFER_INFO* info = nullptr) const noexcept;
//    unsigned short getAttributes(CONSOLE_SCREEN_BUFFER_INFO* info = nullptr) const noexcept;
//    
//    void clearScreen(char fill = ' ');
//    
//    void resizeWindow(Rectangle& rect);
//    
//    friend std::ostream& operator<<(std::ostream& out, const Console& console);
//    
//  private:
//    HANDLE _console;
//    
//    CONSOLE_SCREEN_BUFFER_INFO getScreenInfo() const noexcept;
//    /* fields of CONSOLE_SCREEN_BUFFER_INFO struct:
//      COORD      dwSize;
//      COORD      dwCursorPosition;
//      WORD       wAttributes;
//      SMALL_RECT srWindow;
//      COORD      dwMaximumWindowSize;
//    */
//  };

} // Console_NS

#endif
