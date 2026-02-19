namespace Test_NS
{
  class Trivial
  {
    public:
      Trivial(int value=0);
      int& value();
      const int& value() const;

      void test();
      static void testStatic();

    private:
      int m_value = 0;
  };
}

