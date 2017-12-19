#include <iostream>
using namespace std;

class GrayImage
{
  private:
    uint16_t width, height;
    uint8_t *array;

  public:
    GrayImage() = delete;
    GrayImage& operator=(const GrayImage& b) = delete;
    GrayImage(uint16_t w, uint16_t h);
    GrayImage(const GrayImage& orig);
    ~GrayImage();

    void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
    void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
    
    inline const  uint16_t& getWidth() const { return width; }
    inline const  uint16_t& getHeight() const { return height; }

    inline uint8_t& pixel(uint16_t x, uint16_t y) { return array[y*width+x]; }
    inline const uint8_t& pixel(uint16_t x, uint16_t y) const { return  array[y*width+x]; }

    static GrayImage* readPGM(istream& is);
    void writePGM(ostream& os)const;

    GrayImage* simpleScale(uint16_t w, uint16_t h) const;
    GrayImage* biScale(uint16_t w, uint16_t h) const;
};
