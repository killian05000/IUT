#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "GeometricObjects.hpp"

#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

class Circle : public GeometricObjects
{
  private:

  public:
    Circle(float ax, float ay, float r, int _nb);
    GLuint leVBO;
    int nb;

};

#endif
