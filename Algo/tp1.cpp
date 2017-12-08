#include <iostream>
#include <ifstream>
#include <unordered_map>
using namespace std;

int main()
{
  string fileName="Jules_Verne_Voyage_au_centre_de_la_Terre.txt";
  ifstream fichier(fileName, ios::in);
  if(fichier)
  {

  }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl
}
