#include <iostream>
#include <cstdint>
using namespace std;

const char *const identifier = "wolfger_k";
const char *const informations = "blablabla\n"
                                 "c'est vraiment ouf ce tp.\n";

//--------------------------------------GrayImage--------------------------------------//

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

//----------------------------------------Color----------------------------------------//

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

//--------------------------------------ColorImage--------------------------------------//

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

    ColorImage *simpleScale(uint16_t w, uint16_t h) const;
    ColorImage *bilinearScale(uint16_t w, uint16_t h) const;

    // static ColorImage *readPGM(istream& is);
    // void writePGM(ostream& os) const;
    static ColorImage* readPPM(istream & is);
    void writePPM(ostream &os) const;
    static ColorImage* readTGA(istream& is);
    void writeTGA(ostream& os, bool b) const;

    void clear(Color color);
};
