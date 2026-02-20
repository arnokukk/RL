#include "get_char.hpp"

#include <conio.h>

namespace Console_NS
{
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

  int _getKey0()
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

  int _getKey224()
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
  
  int getCharacter()
  {
    int key = _getch();
    if (_kbhit())
    {
      switch (key)
      {
        case 0:   return _getKey0();    // F1-F10 or NumPad arrows
        case 224: return _getKey224();  // arrows or F11-F12 or Ins-like
        default:  return 0;             // unknown
      }
    }
    else
    {
      return key;
    }
  }
}

