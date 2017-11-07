#include "Toolbox.hpp"

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

//struct Data
//{
//    int_16t a;
//    double b;
//    char c[4];
//    char *str;
//};
