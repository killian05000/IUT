///////////////////////////////////////////////////////////////////////////////
// IUT d'Aix-Marseille Université, site d'Arles
// Département Informatique
// 2ème année
// ----------------------------------------------------------------------------
// Auteur : 
// ----------------------------------------------------------------------------
// Classe définissant un terrain 3D.
///////////////////////////////////////////////////////////////////////////////

#ifndef TERRAIN_H
#define TERRAIN_H



#include <GL/glu.h>
#include "glut.h"
#include "vector3f.h"



typedef struct									// Définition d'un point du terrain
{
	GLfloat	s, t;								// Coordonnées de texture
	GLfloat nx, ny, nz;							// Coordonnées de la normale associée à ce point
	GLfloat	x, hauteur, z;						// Coordonnées du point
} Point_terrain;



class Terrain
{
public :
	Terrain();										// Constructeur
	~Terrain();										// Destructeur

	bool creation(	float dx, float dy, float dz,	// Création du terrain à partir d'une image
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
	float	dist_x, dist_z;							// Distance séparant 2 points selon x et z
	float   dist_y;									// Coefficient d'agrandissement vertical

	Point_terrain	*points_terrain;				// Tableau contenant les points du terrain

	GLfloat terrain_ambient [4];
	GLfloat terrain_diffuse [4];
	GLfloat terrain_specular [4];
	GLfloat terrain_shininess [1];
};



#endif
