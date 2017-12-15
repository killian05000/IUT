#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

unordered_map<string, size_t> mymap;
//unordered_map<string, size_t>::const_iterator got = mymap.find(_content);

void addWord(string _content)
{
  // if (ca y est)
  //   j'itere le compteur de ce mot
  // else
  //   j'ajoute le mot
}

int main()
{
  //unordered_map<string, size_t> mymap;
  string fileName="Jules_Verne_Voyage_au_centre_de_la_Terre.txt";
  ifstream file(fileName, ios::in);
  if(file)
  {
    string content;

    while(file.good())
    {
      file >> content;
      cout << content << endl;
      addWord(content);
    }

    file.close();
  }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
}
