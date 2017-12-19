#include <iostream>
#include <fstream>
#include "ColorImage.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream File("chat.ppm",ios::binary);
  ColorImage *img= ColorImage::readPPM(File);
  File.close();
  Color poto(255,100,160);
  img->clear(poto);
  Color Cl(255,0,0);
  img->rectangle(10,10,10,100,Cl);
  //img->clear(Cl);
  ofstream F2("chatColorpoto.ppm",ios::binary);
  img->writePPM(F2);
  F2.close();
  delete img;

  return EXIT_SUCCESS;
}
