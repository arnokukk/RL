#include "test.hpp"

#include "test_geometry.hpp"
#include "test_console.hpp"

#include <iostream>
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
    //return 0;
  }
}
