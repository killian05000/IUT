///////////////////////////////////////////////////////////////////////////////
// IUT d'Aix-Marseille Universit�, site d'Arles
// D�partement Informatique
// 2�me ann�e
// ----------------------------------------------------------------------------
// Auteur :
// ----------------------------------------------------------------------------
// Classe d�finissant un terrain 3D.
///////////////////////////////////////////////////////////////////////////////

#ifndef TERRAIN_H
#define TERRAIN_H



#include <GL/glu.h>
#include <GL/glut.h>
#include "vector3f.h"



typedef struct									// D�finition d'un point du terrain
{
	GLfloat	s, t;								// Coordonn�es de texture
	GLfloat nx, ny, nz;							// Coordonn�es de la normale associ�e � ce point
	GLfloat	x, hauteur, z;						// Coordonn�es du point
} Point_terrain;

class Terrain
{
public :
	Terrain();										// Constructeur
	~Terrain();										// Destructeur

	bool creation(	float dx, float dy, float dz,	// Cr�ation du terrain � partir d'une image
					const char *image_hauteurs );

	void affiche();									// Affichage du terrain

	float centre_x()
	{
		return nb_pt_x*dist_x*0.5f;
	}

	float centre_z()
	{
		return nb_pt_z*dist_z*0.5f;
	}

private:

	int		nb_pt_x, nb_pt_z;						// Nombre de points en x et en z
	float	dist_x, dist_z;							// Distance s�parant 2 points selon x et z
	float   dist_y;									// Coefficient d'agrandissement vertical

	Point_terrain	*points_terrain;				// Tableau contenant les points du terrain

	GLfloat terrain_ambient [4];
	GLfloat terrain_diffuse [4];
	GLfloat terrain_specular [4];
	GLfloat terrain_shininess [1];
};



#endif
