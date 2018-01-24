#include <iostream>
#include <cstdint>
using namespace std;

const char *const identifier = "wolfger_k";
const char *const informations = "\n"
                                 "Bonjour / bonsoir\n"
                                 "Malgrès de longues heures passé dessus hier soir et les jours précédents je n'ai pas réussi à implémenter l'intégralité des fonctions demandés, mais j'ai quand même celles de bases. (certaines fonctions comme TGA et anaglyphe sont non fonctionelles et sont juste la pour la compilation)\n\n"
                                 "En tout cas bon courage et bonne chance pour les corrections, bonne journée\n";



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

    // dessine le contour et remplis un rectangle, utilisé pour des test (voir compression)
    void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);
    void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color);

    //permet d'obtenir la largeur et la hauteur, paramètres important pour d'aures calculs (scale)
    inline const  uint16_t& getWidth() const { return width; }
    inline const  uint16_t& getHeight() const { return height; }

    inline uint8_t& pixel(uint16_t x, uint16_t y) { return array[y*width+x]; }
    inline const uint8_t& pixel(uint16_t x, uint16_t y) const { return  array[y*width+x]; }

    static GrayImage* readPGM(istream& is); // permet de lire une image de type PGM
    void writePGM(ostream& os)const; // permet de faire une copie et de créer une nouvelle instance PGM

    GrayImage* simpleScale(uint16_t w, uint16_t h) const; // format de compression
    GrayImage* biScale(uint16_t w, uint16_t h) const; // format de compression censé plus efficace (problème sur la formule = même résultat)
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

    //permet d'obtenir la largeur et la hauteur, paramètres important pour d'aures calculs (scale)
    inline const  uint16_t& getWidth() const { return width; }
    inline const  uint16_t& getHeight() const { return height; }

    inline Color& pixel(uint16_t x, uint16_t y) { return array[y*width+x]; }
    inline const Color& pixel(uint16_t x, uint16_t y) const { return  array[y*width+x]; }

    void rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);
  	void fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color);

    static ColorImage* readPGM(istream& is);
    void writePGM(ostream& os) const;
    static ColorImage *readPPM(istream & is); //permet de lire une image au format PPM
    void writePPM(ostream &os) const; //fais une copie et créer une nouvelle image au format PPM

    ColorImage* simpleScale(uint16_t w, uint16_t h) const; // format de compression
    ColorImage* bilinearScale(uint16_t w, uint16_t h) const; // format de compression censé plus efficace (problème sur la formule = même résultat)

    static ColorImage* readTGA(istream& is);
    void writeTGA(ostream &os, bool b) const;

    static ColorImage* readMaison2(istream& is);
    ColorImage* anaglyphe() const;

    void clear(Color color); // attribue à tous les pixels une couleur unique
};
