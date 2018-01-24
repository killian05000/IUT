#include <iostream>
#include <fstream>
#include "ColorImage.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream File("chat.ppm",ios::binary);
  ColorImage *img = ColorImage::readPPM(File);
  File.close();
  Color color1(70,255,0);
  Color color2(255,204,0);
  Color color3(255,0,0);

  img->fillRectangle(130,50,60,60, color1);
  ofstream File1("rect_cat.ppm",ios::binary);
  img->writePPM(File1);
  File1.close();

  img->rectangle(130,150,60,60, color2);
  img->rectangle(220,100,60,60, color3);
  //img->clear(color1);
  ofstream File2("color_cat.ppm",ios::binary);
  img->writePPM(File2);
  File2.close();
  delete img;

  return EXIT_SUCCESS;
}
