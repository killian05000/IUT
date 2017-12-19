#include <string>
#include "Image.hpp"

using namespace std;

//--------------------------------------GrayImage--------------------------------------//

GrayImage::GrayImage(uint16_t w, uint16_t h)
          : width(w), height(h), array(nullptr)
{ array = new uint8_t [width*height]; }

GrayImage::GrayImage(const GrayImage& o)
          : width(o.width), height(o.height), array(nullptr)
{
  array = new uint8_t [width*height];
  for(size_t t=0; t < size_t(width*height); t++)
    array[t] = o.array[t];
}

GrayImage::~GrayImage()
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

void GrayImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color) {
    for(size_t i= 0; i < w; ++i) {
        pixel(x+i,y)= color;
        pixel(x+i,y+h-1)= color;
    }
    for(uint16_t i= 1; i < h-1; ++i) {
        pixel(x,y+i)= color;
        pixel(x+w-1,y+i)= color;
    }
}

void GrayImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t color) {
    for(size_t i= 0; i < w; ++i) {
        for(size_t j= 0; j < h; ++j)
            pixel(i+x,j+y)= color;
    }
}

void GrayImage::writePGM(ostream& os)const
{
  os << "P5 \n";
  os << "#image sauvee par Killian Wolfger \n"
    << width << " " << height << "\n"
    << "#commentaire super utile par ce que voilà \n"
    << "255 \n";
  os.write((const char*)array, width*height);
}

GrayImage* GrayImage::readPGM(istream& is)
{
  string magic_number;
  is >> magic_number;
  if (magic_number != "P5")
  {
    throw runtime_error(" Erreur (func GrayImage::readPGM) : Ce n'est pas un PGM [magic numer != P5] !");
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
    throw runtime_error(" Erreur (func GrayImage::readPGM) : La precision maximal est depasse.");
  }
  GrayImage* picture = new GrayImage(width, height);
  is.read((char*)picture->array,width*height);
  return picture;

}

GrayImage* GrayImage::simpleScale(uint16_t w, uint16_t h) const
{
	GrayImage* img= new GrayImage(w,h);
	for (uint16_t yp=0; yp<h; ++yp)
		for(uint16_t xp=0; xp<w ; ++xp)
    {

			double x = double((xp*width)/w);
			double y = double((yp*height)/h);

			uint16_t xi = uint16_t(x);
			uint16_t yi = uint16_t(y);

			img -> pixel(xp,yp) = pixel(xi,yi);
		}
	return img;
}

GrayImage* GrayImage::biScale(uint16_t w, uint16_t h) const
{
	GrayImage* img= new GrayImage(w,h);
	for (uint16_t yp=0; yp<h; ++yp)
		for(uint16_t xp=0; xp<w ; ++xp){

			double x = double((xp*width)/w);
			double y = double((yp*height)/h);

			uint16_t xi = uint16_t(x);
			uint16_t yi = uint16_t(y);

			uint16_t x2 = (xi+1<width? xi+1:xi);
			uint16_t y2 = (yi+1<height? yi+1:yi);

			double lambda = x-xi;
			double mu = y-yi;

			img->pixel(xp,yp)=(1-lambda)*((1-mu)*pixel(xi,yi)+mu*pixel(xi,y2))+lambda*((1-mu)*pixel(x2,yi)+mu*pixel(x2,y2));
		}
	return img;
}

//----------------------------------------Color----------------------------------------//

Color::Color(): r(255), g(255), b(255)
{}

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b)
      : r(_r), g(_g), b(_b)
{}   // uint8_t naturellement entre 0 et 255;

Color::~Color()
{}

Color::operator*(double alpha, const Color& color)
{

}

Color::operator+(const Color& c1, const Color& c2)
{

}

//--------------------------------------ColorImage--------------------------------------//

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

void ColorImage::rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color) {
    for(size_t i= 0; i < w; ++i)
    {
        pixel(x+i,y)= color;
        pixel(x+i,y+h-1)= color;
    }
    for(uint16_t i= 1; i < h-1; ++i)
    {
        pixel(x,y+i)= color;
        pixel(x+w-1,y+i)= color;
    }
}

void ColorImage::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Color color) {
    for(size_t i= 0; i < w; ++i)
    {
        for(size_t j= 0; j < h; ++j)
            pixel(i+x,j+y)= color;
    }
}

// void ColorImage::writePGM(ostream& os)const
// {
//   os << "P5 \n";
//   os << "#image sauvee par Killian Wolfger \n"
//     << width << " " << height << "\n"
//     << "#commentaire super utile par ce que voilà \n"
//     << "255 \n";
//   os.write((const char*)array, width*height);
// }

// ColorImage* ColorImage::readPGM(istream& is)
// {
//   string magic_number;
//   is >> magic_number;
//   if (magic_number != "P5")
//   {
//     throw runtime_error("Erreur (func ColorImage::readPGM) : Ce n'est pas un PGM [magic number != P5] !");
//   }
//   skip_line(is);
//   skip_comments(is);
//   uint16_t width, height;
//   is >> width >> height;
//   skip_line(is);
//   skip_comments(is);
//   unsigned short nu_grey;
//   is >> nu_grey;
//   if (nu_grey != 255)
//   {
//     throw runtime_error("Erreur (func ColorImage::readPGM) : La nuance de gris ne vaut pas 255");
//   }
//   ColorImage* picture = new ColorImage(width, height);
//   is.read((char*)picture->array,width*height);
//   return picture;
// }

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
        throw runtime_error (" Erreur (func ColorImage::readPPM) : L'image n'est pas une PPM [magic number != P6] !" );
    skip_comments(is);
    uint16_t width,height;
    is >> width >> height;
    is.get();
    skip_comments(is);
    uint16_t maxpixel;
    is >> maxpixel;
    if(maxpixel != 255)
        throw runtime_error (" Erreur (func ColorImage::PPM) : La precision maximal est depasse.");
    is.get();
    ColorImage * C_ing= new ColorImage(width,height);
    is.read((char*)C_ing->array, width* height *3);
    return C_ing;
}

void ColorImage::clear(Color color)
{
    if(color <= 0 || color >= 255)
        throw runtime_error(" Erreur (func ColorImage::clear) : La valeur de la couleur doit etre comprise entre 0 et 255.");
    for(int i= 0; i < width*height; ++i)
        array[i]= color;
}

ColorImage* ColorImage::simpleScale(uint16_t w, uint16_t h) const
{
	ColorImage* img= new ColorImage(w,h);
	for (uint16_t yp=0; yp<h; ++yp)
		for(uint16_t xp=0; xp<w ; ++xp)
    {

			double x = double((xp*width)/w);
			double y = double((yp*height)/h);

			uint16_t xi = uint16_t(x);
			uint16_t yi = uint16_t(y);

			img -> pixel(xp,yp) = pixel(xi,yi);
		}
	return img;
}

ColorImage* ColorImage::bilinearScale(uint16_t w, uint16_t h) const
{
	ColorImage* img= new ColorImage(w,h);
	for (uint16_t yp=0; yp<h; ++yp)
		for(uint16_t xp=0; xp<w ; ++xp){

			double x = double((xp*width)/w);
			double y = double((yp*height)/h);

			uint16_t xi = uint16_t(x);
			uint16_t yi = uint16_t(y);

			uint16_t x2 = (xi+1<width? xi+1:xi);
			uint16_t y2 = (yi+1<height? yi+1:yi);

			double lambda = x-xi;
			double mu = y-yi;

			img->pixel(xp,yp)=(1-lambda)*((1-mu)*pixel(xi,yi)+mu*pixel(xi,y2))+lambda*((1-mu)*pixel(x2,yi)+mu*pixel(x2,y2));
		}
	return img;
}

ColorImage* ColorImage::readTGA(istream& is)
{}

void ColorImage::writeTGA(ostream& os, bool b) const
{}
