///////////////////////////////////////////////////////////////////////////////
// IUT d'Aix-Marseille Université, site d'Arles
// Département Informatique
// 2ème année
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Rendu réaliste
// Auteur : Sébastien Thon
// ----------------------------------------------------------------------------
// Base du TP 1
// Base d'un programme permettant d'afficher une scène composée d'un sol, de
// maisons et d'arbres. On placera des sources de lumière, on spécifiera les
// matériaux des différents objets et on utilisera un effet de brouillard.
// ----------------------------------------------------------------------------
// Compilation sous Windows :
//   g++ -Wall maison.cpp -o maison.exe -lfreeglut -lglu32 -lopengl32
// Compilation sous Linux :
//   g++ -Wall maison.cpp -o maison.exe -lglut -lGLU -lGL
///////////////////////////////////////////////////////////////////////////////

#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <list>
#include "stb_image.h"
#include "vector3f.h"

using namespace std;

#define WIDTH   800										// Largeur de la fenêtre OpenGL
#define HEIGHT  600										// Hauteur de la fenêtre OpenGl

#define KEY_ESC 27										// Code ASCII de la touche Echap

float	xpos = 0, zpos = -50;							// Position de la caméra
int		angle_x = 45, angle_y = 45;						// Orientation de la caméra
int		mouse_x = 0, mouse_y = 0;						// Position de la souris

//*****************************************************************
//* A FAIRE :
//* Déclarer des tableaux contenant les caractéristiques (Ambient,
//* diffus, spéculaire) pour différents matériaux :
//*    - sol
//*    - mur de maison
//*    - toit de maison
//*    - tronc d'arbre
//*    - feuillage d'arbre
//*
//* Par exemple, pour le matériau de sol:
//*   GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};	// On utilise des valeurs faibles pour Ambient (sombre, car à l'ombre)
//*   GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};	// On utilise des valeurs plus élevées pour Diffuse (partie éclairée)
//*   GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};	// Plus ces valeurs seront élevées, et plus le matériau sera luisant
//*   GLfloat MatShininess_sol[1]={5.0f};					// Plus cette valeurs era élevée (max=128) et plus le reflet sera petit
//*****************************************************************



///////////////////////////////////////////////////////////////////////////////
// Intitialisation de certains paramètres d'OpenGL.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////// TEXTURE //////////////////////////////////

class Texture
{
	private:
		GLuint id;
		int width, height;
		stbi_uc *img;

	public:
		bool charger(string file_name);
		void define();
		void define_filter(GLint mod_min, GLint mod_mag);
		void define_looping(GLint mode_axe_s, GLint mode_axe_t);
		void define_mixting(GLint mode);
		void set_default();
};

bool Texture::charger(string file_name)
{
	glGenTextures(1, &id); // definit l'id pour la texture

	set_default();

	int comp;
	img = stbi_load(file_name.c_str(), &width, &height, &comp, 0); // On charge l'image

	if (img!=NULL)
	{
		GLenum format;
		switch (comp)
		{
			case 3:
				format = GL_RGB;
				break;

			case 4:
				format = GL_RGBA;
				break;
			return false;
		}

		glBindTexture(GL_TEXTURE_2D, id); // fixe l'indice de la texture courante
		glTexImage2D(GL_TEXTURE_2D, 0, comp, width, height, 0, format, GL_UNSIGNED_BYTE, img);

		delete [] img;
		return true;
	}
	return false;
}

void Texture::define()
{ 
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::define_filter(GLint mod_min, GLint mod_mag)
{
	define();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mod_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mod_mag);
}

void Texture::define_looping(GLint mode_axe_s, GLint mode_axe_t)
{
	define();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode_axe_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode_axe_s);
}

void Texture::define_mixting(GLint mode)
{
	define();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode);
}

void Texture::set_default()
{
	define();
	define_filter(GL_LINEAR, GL_LINEAR); // GL_LINEAR ou GL_NEAREST
	define_looping(GL_REPEAT, GL_REPEAT); // GL_REPEAT ou GL_CLIMB
	define_mixting(GL_MODULATE); // GL_DECAL ou GL_MODULATE (permet l'illumination)
}

Texture texture_test;
Texture texture_facade;
Texture texture_mur;
Texture texture_sol;
Texture texture_toit;
Texture texture_fumee;

//////////////////////////////// END_TEXTURE ////////////////////////////////


/////////////////////////////////// PUFF ////////////////////////////////////

class Puff
{
	private:
		GLfloat size;
		GLfloat xpos, ypos, zpos;	
		GLfloat speed_x, speed_y, speed_z;

	public:
		GLfloat life_time, life_time_max;

		inline Puff(GLfloat s, GLfloat x, GLfloat y, GLfloat z, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat lt, GLfloat ltm)
				: size(s), xpos(x), ypos(y), zpos(z), speed_x(sx), speed_y(sy), speed_z(sz), life_time(lt), life_time_max(ltm) {}

		// inline Puff(GLfloat s, GLfloat x, GLfloat y, GLfloat z, GLfloat lt)
		// 		: size(s), xpos(x), ypos(y), zpos(z), speed_x(1), speed_y(1), speed_z(1), life_time(lt) {}

		void play(GLfloat time);
		void display();
};

void Puff::play(GLfloat time)
{
	xpos += time*speed_x;
	ypos += time*speed_y;
	zpos += time*speed_z;
	life_time -= time;
	size+=time*0.5;
}

void Puff::display()
{
	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);

 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 	glEnable(GL_BLEND);

 	glColor4f(0.337, 0.337, 0.337, life_time/life_time_max);

	// glNormal3f(0,0,1);
	// glBegin(GL_QUADS);
	// 	glTexCoord2f(0.0f,0.0f);
	// 	glVertex3d(-4, 5, 5);
	// 	glTexCoord2f(0.0f,1.0f);
	// 	glVertex3d(-4, 0, 5);
	// 	glTexCoord2f(1.0f,1.0f);
	// 	glVertex3d( 4, 0, 5);
	// 	glTexCoord2f(1.0f,0.0f);
	// 	glVertex3d( 4, 5, 5);
	// glEnd();

	// On récupère le positionnement de la camera
	float matrice [16];
	glGetFloatv( GL_MODELVIEW_MATRIX, matrice );
	Vector3f Haut, Droite;
	Droite.x = matrice[0] * (size / 2.0f);
	Droite.y = matrice[4] * (size / 2.0f);
	Droite.z = matrice[8] * (size / 2.0f);
	Haut.x = matrice[1] * (size / 2.0f);
	Haut.y = matrice[5] * (size / 2.0f);
	Haut.z = matrice[9] * (size / 2.0f);
	Vector3f A, B, C, D;

	// On calcule la position des 4 sommets du quadrilatère
	A.x = xpos + Haut.x - Droite.x;
	A.y = ypos + Haut.y - Droite.y;
	A.z = zpos + Haut.z - Droite.z;
	B.x = xpos + Haut.x + Droite.x;
	B.y = ypos + Haut.y + Droite.y;
	B.z = zpos + Haut.z + Droite.z;
	C.x = xpos - Haut.x + Droite.x;
	C.y = ypos - Haut.y + Droite.y;
	C.z = zpos - Haut.z + Droite.z;
	D.x = xpos - Haut.x - Droite.x;
	D.y = ypos - Haut.y - Droite.y;
	D.z = zpos - Haut.z - Droite.z;

	// Affichage du billboard
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(D.x,D.y,D.z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(C.x,C.y,C.z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(B.x,B.y,B.z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(A.x,A.y,A.z);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}

///////////////////////////////// END_PUFF //////////////////////////////////

////////////////////////////////// STEAM ////////////////////////////////////

class Steam
{
	private:
		GLfloat xpos, ypos, zpos;
		list<Puff> puffs_list;
		GLfloat emission_interval;
		GLfloat time_spend;
		Texture* texture;	

	public:
		inline Steam(GLfloat x, GLfloat y, GLfloat z, GLfloat ei, Texture *texture) // passez &texture_fumee
			: xpos(x), ypos(y), zpos(z), emission_interval(ei), texture(texture) {}

		void play(GLfloat time);
		void display();
};

void Steam::play(GLfloat time)
{
	time_spend += time;
	if (time_spend > emission_interval)
	{
		time_spend = 0;
		puffs_list.push_back(Puff(3,xpos,ypos,zpos, 0, 1, 1, 10, 10));		
	}

	list<Puff>::iterator i;
	i = puffs_list.begin();
	while(i != puffs_list.end())
	{
		if ( i->life_time <= 0)
			i = puffs_list.erase(i);
		else
			i++;
	}

	for(auto& i : puffs_list)
	{
		i.play(time);
	}
}

void Steam::display()
{
	list<Puff>::iterator i;
	i = puffs_list.begin();
 
	glDepthMask(GL_FALSE);
	texture->define();

	// for(i = puffs_list.begin(); i != puffs_list.end(); i++)
	// {
	// 	i->display();
	// }	
		
	for(auto& i : puffs_list)
	{
		i.display();
	}
	


	glDepthMask(GL_TRUE);

	// Autre méthode avec un for auto& :
		
	// for(auto& i : puffs_list)
	// {
	// 	i.display();
	// }
}

///////////////////////////////// END_STEAM /////////////////////////////////

////////////////////////////////// TOOLBOX //////////////////////////////////

void setColor(int r, int g, int b)
{
	GLfloat MatAmbient[4] = {r/255.f, g/255.f, b/255.f, 1.0f};
	GLfloat MatDiffuse[4] = {MatAmbient[0]/2.f, MatAmbient[1]/2.f, MatAmbient[2]/2.f, 1.0f};
	GLfloat MatSpecular[4] = {0.2f,0.2f, 0.2f, 1.0f};
	GLfloat MatShininess[] = { 5.0F };

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess);
}

//////////////////////////////// END_TOOLBOX ////////////////////////////////


float dir[4] = {2, 5, 2, 1};

void affiche_lumiere()
{
	setColor(255,255,255);
	glPushMatrix();
	glTranslatef(dir[0], dir[1], dir[2]);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();
}

GLvoid initGL()
{

	texture_facade.charger("textures/facade.png");
	texture_mur.charger("textures/mur.png");
	texture_sol.charger("textures/sol.png");
	texture_test.charger("textures/test.png");
	texture_toit.charger("textures/toit.png");
	texture_fumee.charger("textures/fumee.tga");



	glClearColor(0, 0, 0, 1);							// Couleur servant à effacer la fenêtre (noir)
    glShadeModel(GL_SMOOTH);							// Modèle d'ombrage : lissage de Gouraud
	//glEnable(GL_CULL_FACE);								// Ne traite pas les faces cachées
	glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
	glDepthFunc(GL_LEQUAL);								// Mode de fonctionnement du Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)


	//*****************************************************************
	//* A FAIRE :
	//*
	//* 1. Créer la source de lumière 0 (GL_LIGHT0) en tant que source de
	//*    lumière directionnelle, en précisant :
	//*      - sa position
	//*      - sa couleur ambiante
	//*      - sa couleur diffuse
	//*      - sa couleur spéculaire
	//*
	//* 2. Activer la source de lumière 0.
	//*
	//* 3. Activer l'éclairage général
	//*****************************************************************


	//sol ???
	// GLfloat Light0Amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	// GLfloat Light0Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f}; 
	// GLfloat Light0Spec[4]= {1.0f, 1.0f, 1.0f, 1.0f};  
	// GLfloat Light0Pos[4] = {5.0f, 20.0f, 10.0f, 1.0f};


	// glLightfv(GL_LIGHT0, GL_ AMBIENT, Light0Amb);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Dif);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, Light0Spec); 
	// glLightfv(GL_LIGHT0, GL_POSITION, Light0Pos);
	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);

	// glDisable(GL_LIGHT0);



	GLfloat Light0Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat Light0Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // intensité de l'eclairage
	GLfloat Light0Spec[4]= {0.2, 0.2, 0.2, 1.0f};  

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light0Spec); 
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}



///////////////////////////////////////////////////////////////////////////////
// Affiche le sol de la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_sol()
{
	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matériau
	//* crée pour le sol (utiliser glMaterialfv() pour les paramètres
	//* ambiant, diffus, speculaire du matériau du sol).
	//*****************************************************************

	glEnable(GL_TEXTURE_2D);
	texture_sol.define();

	glBegin(GL_QUADS);									// Affichage d'un quadrilatère
		glTexCoord2f(0.0f, 0.0f);
		glVertex3d(-20, 0, -20);
		glTexCoord2f(0.0f, 10.0f);
		glVertex3d(-20, 0,  20);
		glTexCoord2f(10.0f, 10.0f);
		glVertex3d( 20, 0,  20);
		glTexCoord2f(10.0f, 0.0f);
		glVertex3d( 20, 0, -20);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}



///////////////////////////////////////////////////////////////////////////////
// Affiche une maison.
//-----------------------------------------------------------------------------
// Paramètres :
//    xp,yp,zp (in) : position de la maison.
//    yr       (in) : angle de rotation (en degrés) de la maison p/r à l'axe y.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////


void affiche_maison( float xp, float yp, float zp, float yr )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne la maison avec une translation
	glRotatef(yr, 0,1,0);								// et une rotation

	glNormal3f(0,1,0);

	//*****************************************************************
	//* A FAIRE :
	//* Associer une normale à chacun des polygones suivants. Pour cela
	//* faire appel à glNormal3f() avant chacun des "glBegin(GL_QUADS)"
	//* et des "glBegin(GL_TRIANGLES)".
	//*****************************************************************

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matériau
	//* crée pour les murs (utiliser glMaterialfv() pour les paramètres
	//* ambiant, diffus, speculaire du matériau du mur).
	//*****************************************************************
 

	// Mur de face
	glEnable(GL_TEXTURE_2D);
 	texture_mur.define();

	glNormal3f(0,0,1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3d(-4, 5, 5);
		glTexCoord2f(0.0f,1.0f);
		glVertex3d(-4, 0, 5);
		glTexCoord2f(1.0f,1.0f);
		glVertex3d( 4, 0, 5);
		glTexCoord2f(1.0f,0.0f);
		glVertex3d( 4, 5, 5);
	glEnd();

	//cheminée
	glPushMatrix();
	glTranslatef(0,10, -2);
	glNormal3f(10,0,5);
	glBegin(GL_QUADS);
	 
	glVertex3d(1,1,1);
	glVertex3d(-1,1,1);
	glVertex3d(-1,1,-1);
	glVertex3d(1,1,-1);
	 
	glVertex3d(1,-1,1);
	glVertex3d(1,1,1);
	glVertex3d(1,1,-1);
	glVertex3d(1,-1,-1);
	 
	glVertex3d(1,-1,1);
	glVertex3d(-1,-1,1);
	glVertex3d(-1,-1,-1);
	glVertex3d(1,-1,-1);
	 
	glVertex3d(-1,-1,1);
	glVertex3d(-1,1,1);
	glVertex3d(-1,1,-1);
	glVertex3d(-1,-1,-1);
	 
	glVertex3d(1,-1,1);
	glVertex3d(1,1,1);
	glVertex3d(-1,1,1);
	glVertex3d(-1,-1,1);
	 
	glVertex3d(1,-1,-1);
	glVertex3d(1,1,-1);
	glVertex3d(-1,1,-1);
	glVertex3d(-1,-1,-1);
	 
	glEnd();
	glPopMatrix();

	// Mur arrière
	glNormal3f(0,0,-1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3d( 4, 5, -5);
		glTexCoord2f(0.0f,1.0f);
		glVertex3d( 4, 0, -5);
		glTexCoord2f(1.0f,1.0f);
		glVertex3d(-4, 0, -5);
		glTexCoord2f(1.0f,0.0f);
		glVertex3d(-4, 5, -5);
	glEnd();

	// Mur droit
	glNormal3f(1,0,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3d(4, 5,  5);
		glTexCoord2f(0.0f,1.0f);
		glVertex3d(4, 0,  5);
		glTexCoord2f(2.0f,1.0f);
		glVertex3d(4, 0, -5);
		glTexCoord2f(2.0f,0.0f);
		glVertex3d(4, 5, -5);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Mur gauche

	glEnable(GL_TEXTURE_2D);
	texture_facade.define();

	glNormal3f(-1,0,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3d(-4, 5, -5);
		glTexCoord2f(0.0f,1.0f);
		glVertex3d(-4, 0, -5);
		glTexCoord2f(1.0f,1.0f);
		glVertex3d(-4, 0,  5);
		glTexCoord2f(1.0f,0.0f);
		glVertex3d(-4, 5,  5);
	glEnd();

	glDisable(GL_TEXTURE_2D);


	// Triangle avant
	glEnable(GL_TEXTURE_2D);
	texture_mur.define();

	glNormal3f(0,0,1);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f,0.1f);
		glVertex3d( 0, 9, 5);
		glTexCoord2f(0.0f,1.0f);
		glVertex3d(-4, 5, 5);
		glTexCoord2f(1.0f,1.0f);
		glVertex3d( 4, 5, 5);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Triangle arrière
	glEnable(GL_TEXTURE_2D);
	texture_mur.define();

	glNormal3f(0,0,-1);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.5f,0.1f);
		glVertex3d( 0, 9, -5);
		glTexCoord2f(0.0f,1.0f);
		glVertex3d( 4, 5, -5);
		glTexCoord2f(1.0f,1.0f);
		glVertex3d(-4, 5, -5);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	texture_toit.define();

	// Toit versant droit
	glNormal3f(0.707,0.707,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3d(0, 9,  5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3d(4, 5,  5);
		glTexCoord2f(2.0f, 1.0f);
		glVertex3d(4, 5, -5);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3d(0, 9, -5);
	glEnd();

	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	texture_toit.define();

	// Toit versant gauche
	glNormal3f(-0.707,0.707,0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3d( 0, 9, -5);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3d(-4, 5, -5);
		glTexCoord2f(2.0f, 1.0f);
		glVertex3d(-4, 5,  5);
		glTexCoord2f(2.0f, 0.0f);
		glVertex3d( 0, 9,  5);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Restaure la matrice de vue
	glPopMatrix();
}

void affiche_arbre(int x, int y, int z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(90, -1, 0, 0);
	
	// Tronc
	setColor(80,55,0);
	glutSolidCone(1, 10,80,100);

	glTranslatef(0, 0, 3);

	//cone 1
	setColor(15, 105, 0);
	glutSolidCone(2, 8, 400, 700);

	glTranslatef(0, 0, 4);

	//cone 2
	setColor(15, 105, 0);
	glutSolidCone(1.5, 6, 10, 50);
	glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////
// Affiche un arbre.
//-----------------------------------------------------------------------------
// Paramètres :
//    xp,yp,zp (in) : position de l'arbre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// Affiche les différents objets de la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////

Steam fumee  = Steam(10, 9, -2, 0.5, &texture_fumee);

void affiche_scene(float dt)
{
	affiche_lumiere();

	affiche_sol();								

	affiche_maison( -4, 0, -9, 110 );
	affiche_maison( 10, 0, 0, 0 );
	affiche_maison( -5, 0, 8, -120 );

	affiche_arbre(0, 0, 0);

	fumee.play(dt);
	fumee.display();

	glutSwapBuffers();							// Affiche la scène à l'écran (affichage en double buffer)
}

float mesure_temps_ecoule()
{
	static long temps_precedent = -1;
	long temps_actuel;
	float dt = 0;

	//Mesure temps actuel
	temps_actuel = glutGet(GLUT_ELAPSED_TIME);

	if(temps_precedent == -1) // verif si c'est le premier appel à la fonction
	{
		temps_precedent = glutGet(GLUT_ELAPSED_TIME);
		dt = 0;
	}
	else // sinon fais la difference avec la valeur précedement stocké
	{
		dt = (float)(temps_actuel - temps_precedent) / 1000.0f;
		temps_precedent = temps_actuel;
	}

	return dt;

}


///////////////////////////////////////////////////////////////////////////////
// Call-back : affichage dans la fenêtre.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_display()
{
	// On efface les pixels de l'image (color buffer) et le Z-Buffer (depth buffer).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// On initialise la matrice de vue avec la matrice identité.
	glLoadIdentity();

	// On applique une translation et une rotation à la scène pour simuler
	// un déplacement de caméra.
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	glLightfv(GL_LIGHT0, GL_POSITION, dir);

	// fumee.play(2);
	// fumee.display();

	//*****************************************************************
	//* A FAIRE :
	//* Re-spécifier la position des sources de lumière avec glLightfv()
	//* pour qu'elles soient aussi affectées par la translation et la
	//* rotation qu'on vient d'appliquer à la scène.
	//*****************************************************************

	float dt = mesure_temps_ecoule();

	// On affiche la scène.
	affiche_scene(dt);

	// On force OpenGL à afficher avant de passer à la suite.
	glFlush();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : fonction appelée lorsqu'on redimensionne la fenêtre.
//-----------------------------------------------------------------------------
// Paramètres :
//    width, height (in) : nouvelles largeur et hauteur de la fenêtre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des événements clavier.
//-----------------------------------------------------------------------------
// Paramètres :
//    key (in) : code ascii de la touche utilisée.
//    x,y (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case KEY_ESC:						// 'ECHAP' :
			exit(1);						// on quitte le programme
			break;
		case 'q':
			dir[0]--;
			glutPostRedisplay();
			break;

		case 'd':
			dir[0]++;
			glutPostRedisplay();
			break;

		case 'e':
		dir[1]++;
		glutPostRedisplay();
		break;

		case 'a':
		dir[1]--;
		glutPostRedisplay();
		break;

		case 's':
		dir[2]++;
		glutPostRedisplay();
		break;

		case 'z':
		dir[2]--;
		glutPostRedisplay();
		break;


	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des touches speciales du clavier.
//-----------------------------------------------------------------------------
// Paramètres :
//    key (in) : code ascii de la touche utilisée.
//    x,y (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
	float speed = 1.0f;						// Vitesse de déplacement de la caméra

	switch (key)
	{
		case GLUT_KEY_UP:					// Flèche vers le haut : 
			zpos += speed;					// on déplace la caméra selon z-
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case GLUT_KEY_DOWN:					// Flèche vers le bas :
			zpos -= speed;					// on déplace la caméra selon z+
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case GLUT_KEY_LEFT:					// Flèche vers la gauche :
			xpos += speed;					// on déplace la caméra selon x-
			glutPostRedisplay();			// et on demande le réaffichage.
			break;

		case GLUT_KEY_RIGHT:				// Flèche vers la droite :
			xpos -= speed;					// on déplace la caméra selon x+
			glutPostRedisplay();			// et on demande le réaffichage.
			break;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion de clics souris.
//-----------------------------------------------------------------------------
// Paramètres :
//    button (in) : code du bouton utilisé.
//    state  (in) : état du bouton.
//    x,y    (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des déplacements de la souris.
//-----------------------------------------------------------------------------
// Paramètres :
//    x,y    (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	angle_x += y - mouse_y;						// Modifie la direction de vue de la caméra
	angle_y += x - mouse_x;						// en fonction de la position de la souris
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();						// Demande le réaffichage
}





///////////////////////////////////////////////////////////////////////////////
// Fonction principale du programme.
//-----------------------------------------------------------------------------
// Paramètres :
//    argc (in) : nombre d'arguments de la ligne de commande.
//    argv (in) : tableau de chaînes de caractères contenant les arguments.
// Retour :
//    Un entier contenant le code de retour du programme.
///////////////////////////////////////////////////////////////////////////////

void timer(int v)
{
glutPostRedisplay();
glutTimerFunc(20, timer, 0);
// Le timer ne fonctionne qu'une fois,
// il faut le relancer
}

int main(int argc, char *argv[])
{
	// Initialisation de paramètres de Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	glutTimerFunc(20, timer, 0);

	// Intitialisation de paramètres d'OpenGL
	initGL();

	// Déclaration des fonctions de call-back.
	glutDisplayFunc(&callback_display);
	glutReshapeFunc(&callback_reshape);
	glutKeyboardFunc(&callback_keyboard);
	glutSpecialFunc(&callback_special);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	// Boucle principale de Glut.
	glutMainLoop();

	// Code de retour
	return 1;
}
