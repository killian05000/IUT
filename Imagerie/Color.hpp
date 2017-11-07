#include <iostream>
using namespace std;

class Color
{
  public:
    uint8_t r,g,b;

    inline Color(uint8_t _r=0, uint8_t _g=0, uint8_t _b=0)
          : r(_r), g(_g), b(_b)
          {}
    friend Color operator*(double alpha, const Color& color);
    friend Color operator+(const Color& c1, const Color& c2);
};
