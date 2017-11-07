#include <string>
#include "GrayImage.hpp"

void GrayImage::writePGM(ostream&)const
{
  os << "P5 \n";
  os << "#image sauvee par Killian Wolfger \n"
    << width << " " << height << "\n"
    << "#commentaire super utile par ce que voilà \n"
    << "255 \n";
  os.write((const char*)array, width*height);
}

void GrayImage::skip_line(istream& is)
{
  char c;
  do
  {
    is.get(c);
  } while(c != '\n'); //Avance dans les caracteres jusqu'a que ce soit une fin de ligne
}

void GrayImage::skip_comments(istream& is)
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

GrayImage GrayImage::readPGM(istream& is)
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
  GrayImage* picture = new GrayImage(width, height);
  is.read((char*)picture->array,width*height);
  return picture;

}
