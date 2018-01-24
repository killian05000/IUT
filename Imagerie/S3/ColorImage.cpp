#include <string>
#include "ColorImage.hpp"

ColorImage::ColorImage(uint16_t w, uint16_t h)
          : width(w), height(h), array(nullptr)
{ array = new Color [width*height]; }

ColorImage::ColorImage(const ColorImage& o)
          : width(o.width), height(o.height), array(nullptr)
{
  array = new Color [width*height];
  for(size_t t=0; t < size_t(width*height); t++)
    array[t] = o.array[t];
}

ColorImage::~ColorImage()
{ delete [] array; }

void skip_line(istream& is)
{
  char c;
  do
  {
    is.get(c);
  } while(c != '\n'); //Avance dans les caracteres jusqu'a que ce soit une fin de ligne
}

void skip_comments(istream& is)
{
  char c;
  is.get(c);
  while( c == '#') //S'il y à un # (début de commentaire)
  {
    skip_line(is); //On Avance dans les caractère jusqu'à \n
    is.get(c); // On prend le caractere suivant pour le tester
  }
  is.putback(c);
}

void ColorImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color) {
    for(size_t i= 0; i < w; ++i) {
        pixel(x+i,y)= color;
        pixel(x+i,y+h-1)= color;
    }
    for(uint16_t i= 1; i < h-1; ++i) {
        pixel(x,y+i)= color;
        pixel(x+w-1,y+i)= color;
    }
}

void ColorImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color) {
    for(size_t i= 0; i < w; ++i) {
        for(size_t j= 0; j < h; ++j)
            pixel(i+x,j+y)= color;
    }
}

void ColorImage::writePGM(ostream& os)const
{
  os << "P5 \n";
  os << "#image sauvee par Killian Wolfger \n"
    << width << " " << height << "\n"
    << "#commentaire super utile par ce que voilà \n"
    << "255 \n";
  os.write((const char*)array, width*height);
}

ColorImage* ColorImage::readPGM(istream& is)
{
  string magic_number;
  is >> magic_number;
  if (magic_number != "P5")
  {
    throw runtime_error("Erreur : Ce n'est pas un PGM !");
  }
  skip_line(is);
  skip_comments(is);
  uint16_t width, height;
  is >> width >> height;
  skip_line(is);
  skip_comments(is);
  unsigned short nu_grey;
  is >> nu_grey;
  if (nu_grey != 255)
  {
    throw runtime_error("Erreur : La nuance de gris ne vaut pas 255");
  }
  ColorImage* picture = new ColorImage(width, height);
  is.read((char*)picture->array,width*height);
  return picture;
}

void ColorImage::writePPM(ostream& os)const
{
  os << "P6\n";
  os << "#image sauvee par Killian Wolfger\n"
    << width << " " << height << "\n"
    << "#commentaire super utile par ce que voilà\n"
    << "255\n";
  os.write((const char *)array, width*height*3);
}

ColorImage *ColorImage::readPPM(istream & is)
{
    string line;
    getline(is,line);
    if (line != "P6")
        throw runtime_error ("L'image n'est pas une PPM." );
    skip_comments(is);
    uint16_t width,height;
    is >> width >> height;
    is.get();
    skip_comments(is);
    uint16_t maxpixel;
    is >> maxpixel;
    if(maxpixel != 255)
        throw runtime_error ("La precision maximal est depasse.");
    is.get();
    ColorImage * C_ing= new ColorImage(width,height);
    is.read((char*)C_ing->array, width* height *3);
    return C_ing;
}

void ColorImage::clear(Color color) {
    if(color <= 0 || color >= 255)
        throw runtime_error("La valeur de la couleur doit etre comprise entre 0 et 255.");
    for(int i= 0; i < width*height; ++i)
        array[i]= color;
}
