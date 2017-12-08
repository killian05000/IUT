#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

void addWord(string _content)
{
  if(_content n'est pas dans um)
    um.add(_content)
  else
    on incremente la valeur;
}

int main()
{
  unordered_map<string, size_t> um;
  string fileName="Jules_Verne_Voyage_au_centre_de_la_Terre.txt";
  ifstream file(fileName, ios::in);
  if(file)
  {
    string content;

    while(file.good())
    {
      file >> content;
      addWord(content);
    }

    file.close();
  }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
}
