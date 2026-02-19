#include "console.hpp"


namespace Console_NS
{

  // class Console
//  Console::Console() noexcept
//  {
//    this->_console = GetStdHandle(STD_OUTPUT_HANDLE);
//  }
//  
//  CONSOLE_SCREEN_BUFFER_INFO Console::getScreenInfo() const noexcept
//  {
//    CONSOLE_SCREEN_BUFFER_INFO info;
//    GetConsoleScreenBufferInfo(this->_console, &info);
//    return info;
//  }
//  
//  Coord Console::getSize(CONSOLE_SCREEN_BUFFER_INFO* info /* = nullptr*/) const noexcept
//  {
//    return info ? Coord(info->dwSize) : Coord(this->getScreenInfo().dwSize);
//  }
//
//  Coord Console::getCursorPosition(CONSOLE_SCREEN_BUFFER_INFO* info /* = nullptr*/) const noexcept
//  {
//    return info ? Coord(info->dwCursorPosition) : Coord(this->getScreenInfo().dwCursorPosition);
//  }
//
//  Coord Console::getMaxWinSize(CONSOLE_SCREEN_BUFFER_INFO* info /* = nullptr*/) const noexcept
//  {
//    return info ? Coord(info->dwMaximumWindowSize) : Coord(this->getScreenInfo().dwMaximumWindowSize);
//  }
//  
//  Rectangle Console::getWindowRect(CONSOLE_SCREEN_BUFFER_INFO* info /* = nullptr*/) const noexcept
//  {
//    return info ? Rectangle(info->srWindow) : Rectangle(this->getScreenInfo().srWindow);
//  }
//  
//  unsigned short Console::getAttributes(CONSOLE_SCREEN_BUFFER_INFO* info /* = nullptr */) const noexcept
//  {
//    return info ? info->wAttributes : this->getScreenInfo().wAttributes;
//  }
//  
//  void Console::clearScreen(char fill /* = ' ' */)
//  {
//    COORD cp = {0, 0};
//    auto info = this->getScreenInfo();
//    DWORD written{0}, cells = info.dwSize.X * info.dwSize.Y;
//    FillConsoleOutputCharacter(this->_console, fill, cells, cp, &written);
//    FillConsoleOutputAttribute(this->_console, info.wAttributes, cells, cp, &written);
//    SetConsoleCursorPosition(this->_console, cp);
//  }
//  
//  std::ostream& operator<<(std::ostream& out, const Console& console)
//  {
//    auto info = console.getScreenInfo();
//    auto flags = out.flags();
//    out << "[Window = " << console.getWindowRect(&info) << "; "
//        << "Max size = " << console.getMaxWinSize(&info) << "; "
//        << "Size = " << console.getMaxWinSize(&info) << "; "
//        << "CP = " << console.getCursorPosition(&info) << "; "
//        << "Att = 0x" << std::hex << console.getAttributes(&info);
//        out.flags(flags);
//        out << "]";
//        return out;
//  }
} // Console_NS
