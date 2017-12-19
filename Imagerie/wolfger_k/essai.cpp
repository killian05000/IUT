#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*
 Toutes vos définitions de classes doivent être regroupées dans l'unique
 fichier "Image.h". Son nom n'est pas modifiable sinon vous empêcherez la
 compilation de l'autre executable servant à la correction.
*/
#include "Image.hpp"

extern const char * const identifier;   // Ne pas modifier ces deux lignes ! Vos changements au sujet
extern const char * const informations; // de ceux deux constantes doivent être faits dans Image.cpp.


int main(int argc,char *argv[])
{
 cout << "Votre identifiant tel que declare dans Image.cpp : " << identifier << endl;
 cout << "Les informations que vous avez decide d'indiquer au correcteur : " << endl << informations << endl;
 try
  {
   /*
   Vous pouvez modifier l'intérieur de ce main() comme bon vous semble. Cette
   fonction ne sera pas utilisée lors de la correction.
   */

//--------------------------------------GrayImage--------------------------------------//

   ifstream File_pgm("chat.pgm",ios::binary);
   GrayImage *img = GrayImage::readPGM(File_pgm);
   File_pgm.close();

   img->rectangle(130,150,60,60,255);
   img->fillRectangle(130,50,60,60,255);
   ofstream File1("chat_rect.pgm", ios::binary);
   img->writePGM(File1);
   File1.close();

   GrayImage* simple_img = img->simpleScale(160,120);
   ofstream File2("chat_simple.pgm",ios::binary);
   simple_img->writePGM(File2);
   File2.close();

   GrayImage* bi_img = img->biScale(160,120);
   ofstream File3("chat_bi.pgm",ios::binary);
   bi_img->writePGM(File3);
   File3.close();

   delete img;
   delete simple_img;
   delete bi_img;

//--------------------------------------ColorImage--------------------------------------//

   ifstream File_ppm("chat.ppm",ios::binary);
   ColorImage *img2 = ColorImage::readPPM(File_ppm);
   File_ppm.close();
   Color color1(70,255,0);
   Color color2(255,204,0);
   Color color3(255,0,0);

   img2->fillRectangle(130,50,60,60, color1);
   ofstream File1ppm("rect_cat.ppm",ios::binary);
   img2->writePPM(File1ppm);
   File1ppm.close();

   img2->rectangle(130,150,60,60, color2);
   img2->rectangle(220,100,60,60, color3);
   //img->clear(color1);
   ofstream File2ppm("color_cat.ppm",ios::binary);
   img2->writePPM(File2ppm);
   File2ppm.close();
   delete img2;

  } // Trois types d'exceptions seront attrapés (les chaines C et C++ ainsi que
    // les std::exception et toutes ses dérivées). N'utilisez pas autre chose !
 catch(exception& e)
  { cerr<< "Exception :"<<e.what()<< endl; }
 catch(string& e)
  { cerr<< "Exception string :"<<e<< endl; }
 catch(const char * e)
  { cerr<< "Exception const char* :"<<e<< endl; }
 return 0;
}
