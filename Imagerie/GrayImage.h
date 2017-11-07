#include <iostream>
using namespace std;

class GrayImage
{
  private:
    int height;
    int width;

  public:
    void writePGM(ostream&)const;
    static GrayImage readPGM(istream& is);
    void skip_line(istream& is);
    void skip_comments(istream& is);
};
