#include "Circle.hpp"
using namespace std;

Circle::Circle(float ax, float ay, float r, int _nb)
      : nb(_nb)
{
  float vertices[nb*3];
  float pas=0;
  for(int i=0; i<nb*3; i+=3)
  {
    vertices[i]= ax + r*cos(pas);
    vertices[i+1]= ay + r*sin(pas);
    vertices[i+2]= 0;

    pas+=2*3.1415926/nb;
    cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << endl;
  }


  glGenBuffers(1, &this->leVBO); //génération d'une référence de buffer object
  glBindBuffer(GL_ARRAY_BUFFER, this->leVBO); //liaison du buffer avec un type tableau de données
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*nb*3, vertices, GL_STATIC_DRAW); //création et initialisation du container de données (3 sommets -> 9 float)
}
