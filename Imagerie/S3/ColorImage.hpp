#include <iostream>
#include "Color.hpp"
using namespace std;

class ColorImage
{
  private:
    uint16_t width, height;
    Color *array;

  public:
    ColorImage() = delete;
    ColorImage& operator=(const ColorImage& b) = delete;
    ColorImage(uint16_t w, uint16_t h);
    ColorImage(const ColorImage& orig);
    ~ColorImage();

    inline const  uint16_t& getWidth() const { return width; }
    inline const  uint16_t& getHeight() const { return height; }

    inline Color& pixel(uint16_t x, uint16_t y) { return array[y*width+x]; }
    inline const Color& pixel(uint16_t x, uint16_t y) const { return  array[y*width+x]; }

    void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);
  	void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);

    static ColorImage* readPGM(istream& is);
    void writePGM(ostream& os) const;
    static ColorImage *readPPM(std::istream & is);
    void writePPM(std::ostream &os) const;

    void clear(Color color);
};
