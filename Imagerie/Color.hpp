#include <iostream>
#include <cstdint>
using namespace std;

class Color
{
  private:
    uint8_t r,g,b;

  public:

    Color();
    Color(uint8_t _r, uint8_t _v, uint8_t _b);
    ~Color();

    friend std::ostream& operator<<(std::ostream& os, const Color &c)
    {
        os << c.r << " " << c.g << " " << c.b;
        return os;
    }
    friend bool operator<=(const Color& couleur, const int& valeur)
    {
        return couleur.r <= valeur && couleur.g <= valeur && couleur.b <= valeur;
    }
    friend bool operator>=(const Color& couleur, const int& valeur) {
        return !(couleur<=valeur);
    }

    friend Color operator*(double alpha, const Color& color);
    friend Color operator+(const Color& c1, const Color& c2);
};
