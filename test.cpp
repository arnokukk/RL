#include "test_geometry.hpp"
#include "test_console.hpp"
#include "test_game.hpp"
#include "prints.hpp"

#include <windows.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <string>
#include <stdexcept>

namespace Test_NS
{
  int test_all()
  {
    std::cout << "Run all tests" << std::endl;
    getch();
    return 0;
  }
  
  int test_single(const std::string& testName)
  {
    if (testName == "coord")
      return testCoord();
    else if (testName == "rectangle")
      return testRectangle();
    else if (testName == "geometry")
      return testGeometry();
    else if (testName == "con_size")
      return testSetConSize();
    else if (testName == "chars")
      return testChars();
    else if (testName == "put")
      return testPut();
    else if (testName == "char_table")
      return testCharTable();
    else if (testName == "fit")
      return testFitBuffer();
    else if (testName == "resize")
      return testWinResize();
    else if (testName == "window")
      return testWindow();
    else if (testName == "row")
      return testRow();
    else if (testName == "map")
      return testMap(30, 15);
    else if (testName == "game_coord")
      return testGameCoord();
    else if (testName == "path")
      return testPath();
    else
    {
      std::cout << "Run test" << testName << std::endl;
      getch();
    }
    return 0;
  }
  
  int test(int argc, char* argv[])
  {
    if (argc == 2)
    {
      return test_all();
    }
    else if (argc > 2)
    {
      int failedTests = 0;
      for (int i = 2; i < argc; i++)
      {
        failedTests += test_single(argv[i]);
      }
      std::cout << std::endl
       << "=============================================" << std::endl
       << "=== " << failedTests << " fails in tests. ===" << std::endl
       << "=============================================" << std::endl;
      return failedTests;
    }
    else
    {
      throw std::runtime_error("Inorrect call of Test_NS::test");
    }
  }
  
  int testInWindow(const char* name, const char* opt/*="/C"*/)
  {
    std::ostringstream stream;
    stream << "CMD " << opt << " .\\rl-test.exe test " << name;

    STARTUPINFOA sInfo;
    ::ZeroMemory(&sInfo, sizeof(sInfo));
    sInfo.cb = sizeof(sInfo);
    sInfo.lpTitle = (LPSTR)name;

    PROCESS_INFORMATION pInfo;
    ::ZeroMemory(&pInfo, sizeof(pInfo));
    
    if (!::CreateProcess(NULL, (LPSTR)stream.str().c_str(), NULL, NULL, FALSE,
                         CREATE_NEW_CONSOLE, NULL, NULL, &sInfo, &pInfo))
    {
      Debug_NS::reportFailed("CreateProcessA");
      return 1;
    }

    ::WaitForSingleObject(pInfo.hProcess, 0);
    ::CloseHandle(pInfo.hProcess);
    ::CloseHandle(pInfo.hThread);
    return 0;
  }
}
