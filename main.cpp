#include "game.hpp"
#include "main_fwd.hpp"

#include <string>

int main(int argc, char* argv[])
{
  const std::string TEST = "test";
  
  if (argc == 1)
  {
    return Game_NS::run();
  }
  else if (TEST == argv[1])
  {
    return Test_NS::test(argc, argv);
  }
  else
  {
    return Game_NS::run(argv[1]);
  }
}
