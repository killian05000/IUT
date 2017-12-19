#include <iostream>
#include "Color.hpp"

using namespace std;

Color::Color(): r(255), g(255), b(255)
{}

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b)
      : r(_r), g(_g), b(_b)
{}   // uint8_t naturellement entre 0 et 255;

Color::~Color()
{}
