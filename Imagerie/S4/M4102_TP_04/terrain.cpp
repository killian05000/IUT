///////////////////////////////////////////////////////////////////////////////
// IUT d'Aix-Marseille Université, site d'Arles
// Département Informatique
// 2ème année
// ----------------------------------------------------------------------------
// Auteur : 
// ----------------------------------------------------------------------------
// Classe définissant un terrain 3D.
///////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "terrain.h"
#include "pgm.h"



///////////////////////////////////////////////////////////////////////////////
// Constructeur de la classe Terrain.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
//
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
Terrain::Terrain()
{
	points_terrain = NULL;
}



///////////////////////////////////////////////////////////////////////////////
// Destructeur de la classe Terrain.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
//
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
Terrain::~Terrain()
{



}



///////////////////////////////////////////////////////////////////////////////
// Affichage du terrain.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
//
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void Terrain::affiche()
{
	//    On étudie les points 4 par 4, en les utilisant pour tracer
	//    deux triangles comme suit :
	//
	//         0---3      1er  triangle : 0 -> 1 -> 3
	//	       |  /|      2ème triangle : 1 -> 2 -> 3
	//         | / |
	//         1/--2
	//



}



///////////////////////////////////////////////////////////////////////////////
// Création du terrain à partir d'une image.
//-----------------------------------------------------------------------------
// Paramètres :
//    cx, cy, cz     (in) : coefficients d'agrandissement selon les 3 axes.
//    image_hauteurs (in) : image au format pgm dont les niveaux de gris
//                          définissent les hauteurs d'un terrain.
//
// Retour :
//    true si le terrain a pu être crée (l'image a pu être chargée),
//    false sinon.
///////////////////////////////////////////////////////////////////////////////
bool Terrain::creation(	float dx, float dy, float dz, const char *image_hauteurs )
{
	// Tableau de byte servant à stocker les pixels en niveaux de gris de
	// l'image au format pgm "image_hauteurs".
	byte	*img;

	// Chargement d'une image en niveaux de gris. Chaque pixel correspondra
	// à un point du terrain.
	img = load_PGM( image_hauteurs, &nb_pt_x, &nb_pt_z );

	// Si l'image n'a pas pu être chargée, alors on quitte la fonction.
	if( img == false )
		return false;

	dist_x = dx;
	dist_y = dy;
	dist_z = dz;

	if( points_terrain )
		delete[] points_terrain;

	points_terrain = new Point_terrain[nb_pt_x * nb_pt_z];

	int x, z, num = 0;

	for( z=0; z<nb_pt_z; z++ )
	{
		for( x=0; x<nb_pt_x; x++ )
		{
			points_terrain[num].x = x * dist_x;
			points_terrain[num].z = z * dist_z;
			points_terrain[num].hauteur = img[num] * dist_y;

			num++; 
		}
	}

	delete[] img;

	terrain_ambient[0]=0.6f;  terrain_ambient[1]=0.6f;  terrain_ambient[2]=0.6f;  terrain_ambient[3]=1.0f;
	terrain_diffuse[0]=0.9f;  terrain_diffuse[1]=0.9f;  terrain_diffuse[2]=0.9f;  terrain_diffuse[3]=1.0f;
	terrain_specular[0]=0.0f; terrain_specular[1]=0.0f; terrain_specular[2]=0.0f; terrain_specular[3]=1.0f;
	terrain_shininess[0]=1.0f;

	return true;
}
