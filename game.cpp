#include "game.hpp"

#include "console.hpp"

#include <sstream>


namespace Game_NS
{
  int run(const std::string& saved/*=""*/)
  {
    Console_NS::Console console;
    console.init("RUN game");
    if (saved.empty())
    {
      console.put("Start new game...", 1, 0);
    }
    else
    {
      std::ostringstream stream;
      stream << "Load saved game \"" << saved << "\"...";
      console.put(stream.str(), 1, 0);
    }

    console.put("Press any key...", 5, 0, Console_NS::Color::Green);
    console.getChar();
    return 0;
  }
}
