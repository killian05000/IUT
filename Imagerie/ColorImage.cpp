#include <string>
#include "ColorImage.hpp"
#include "Toolbox.cpp"

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

void ColorImage::writePGM(ostream& os)const
{
  os << "P5 \n";
  os << "#image sauvee par Killian Wolfger \n"
    << width << " " << height << "\n"
    << "#commentaire super utile par ce que voilà \n"
    << "255 \n";
  os.write((const char*)array, width*height);
}

void ColorImage::writePPM(ostream& os)const
{
  os << "P6 \n";
  os << "#image sauvee par Killian Wolfger \n"
    << width << " " << height << "\n"
    << "#commentaire super utile par ce que voilà \n"
    << "255 \n";
  os.write((const char*)array, width*height*3);
}

void ColorImage::skip_line(istream& is)
{
  char c;
  do
  {
    is.get(c);
  } while(c != '\n'); //Avance dans les caracteres jusqu'a que ce soit une fin de ligne
}

void ColorImage::skip_comments(istream& is)
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

ColorImage ColorImage::readPGM(istream& is)
{
  string magic_number;
  is >> magic_number;
  of (magic_number != "P5")
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

ColorImage* ColorImage::readPPM(std::istream &is)
{
  string magic_number;
  getline(is, magic_number);
  if(magic_number != "P6")
    throw runtime_error("L'image n'est pas une PPM");
  skip_comments(is);
  uint16_t _width, _height;
  is >> _width >> _height;
  is.get(); // saute le \n
  skip_comments(is);
  uint16_t maxpixel;
  is >> maxpixel;
  if (maxpixel != 255)
    throw runtime_error("La precision max est depasse");
  is.get();
}
