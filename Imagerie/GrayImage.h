#include <iostream>
using namespace std;

class GrayImage
{
  private:
    static const uint16_t width, height;
    uint8_t *array;

  public:
    GrayImage() = delete;
    GrayImage& operator=(const GrayImage& b) = delete;
    GrayImage(uint16_t w, uint16_t h);
    GrayImage(const GrayImage& orig);
    ~GrayImage();

    inline const  uint16_t& getWidth() const { return width; }
    inline const  uint16_t& getHeight() const { return height; }

    inline uint8_t& pixel(uint16_t x, uint16_t y) { return array[y*width+x]; }
    inline const uint8_t& pixel(uint16_t x, uint16_t y) const { return  array[y*width+x]; }

    static GrayImage readPGM(istream& is);
    void writePGM(ostream&)const;
    void skip_line(istream& is);
    void skip_comments(istream& is);
};
