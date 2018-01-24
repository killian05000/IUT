#include <iostream>
#include <fstream>
#include "GrayImage.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream File("chat.pgm",ios::binary);
  GrayImage *img = GrayImage::readPGM(File);
  File.close();

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

  return EXIT_SUCCESS;
}
