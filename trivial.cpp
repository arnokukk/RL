#include <iostream>

#include "trivial.hpp"


namespace Test_NS
{
  Trivial::Trivial(int value/*=0*/) : m_value(value) {}
  
  int& Trivial::value()
  {
    return this->m_value;
  }

  const int& Trivial::value() const
  {
    return this->m_value;
  }
  
  void Trivial::test()
  {
    std::cout << "Test value is " << this->value() << std::endl;
    this->value() = 42;
    std::cout << "And now value is " << this->value() << std::endl;
  }
  
  void Trivial::testStatic()
  {
    std::cout << "It's a static method:" << std::endl;
    Trivial t(42);
    std::cout << "Test value is " << t.value() << std::endl;
    t.value() = 0;
    std::cout << "And now value is " << t.value() << std::endl;
  }
}

