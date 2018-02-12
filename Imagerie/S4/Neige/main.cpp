#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <list>
#include <random>
#include "stb_image.h"
#include "vector3f.h"

using namespace std;

#define WIDTH   800
#define HEIGHT  600

float	xpos = 0, zpos = -70;
int		angle_x = 15, angle_y = 0;
int		mouse_x = 0, mouse_y = 0;


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

Texture texture_sol;
Texture texture_snow;

//////////////////////////////// END_TEXTURE ////////////////////////////////


//////////////////////////////// SNOWFLAKE //////////////////////////////////

class Snowflake
{
	private:
		GLfloat size;
		GLfloat xpos, ypos, zpos;
		GLfloat speed_x, speed_y, speed_z;
    GLfloat ymin=0;

	public:

		inline Snowflake(GLfloat s, GLfloat x, GLfloat y, GLfloat z, GLfloat sx, GLfloat sy, GLfloat sz)
				: size(s), xpos(x), ypos(y), zpos(z), speed_x(sx), speed_y(sy), speed_z(sz) {}

    inline GLfloat getypos() {return ypos;}
    inline GLfloat getymin() {return ymin;}

		void play(GLfloat time);
		void display();
};

void Snowflake::play(GLfloat time)
{
	xpos += time*speed_x;
	ypos += time*speed_y;
	zpos += time*speed_z;
}

void Snowflake::display()
{
	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);

 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 	glEnable(GL_BLEND);

 	//glColor4f(1, 1, 1, ((ypos/100)*6)); // si on veut que les flocons disparaissent peu a peu avant d'atteindre le sol (proportionnel)


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

////////////////////////////// END_SNOWFLAKE ///////////////////////////////

////////////////////////////////// SNOW ////////////////////////////////////

class Snow
{
	private:
		GLfloat xpos, ypos, zpos;
		list<Snowflake> Snowflakes_list;
		GLfloat emission_interval;
		GLfloat time_spend;
		Texture* texture;

	public:
		inline Snow(GLfloat x, GLfloat y, GLfloat z, GLfloat ei, Texture *texture)
			: xpos(x), ypos(y), zpos(z), emission_interval(ei), texture(texture) {}

		void play(GLfloat time);
		void display();
};

void Snow::play(GLfloat time)
{
	time_spend += time;
	if (time_spend > emission_interval)
	{
    // utilisation de l'aléatoire pour la poition et la taille de manière a faire un rendu plus réaliste
		time_spend = 0;
		random_device generator;
	    uniform_int_distribution<int> distribution(60, 100);
    	int res = distribution(generator);
    	GLfloat size = res/100.f;

		uniform_int_distribution<int> distribution2(120, 180);
    	int res2 = distribution2(generator);
    	GLfloat dir = res2/100.f;

    uniform_int_distribution<int> distribution3(-25, 25);
  	int x = distribution3(generator);
  	GLfloat px = x/1.f;

    uniform_int_distribution<int> distribution4(-25, 25);
  	int y = distribution3(generator);
  	GLfloat py = y/1.f;

		Snowflakes_list.push_back(Snowflake(size, px, 20, py, 0, -2, 0));
	}

	list<Snowflake>::iterator i;
	i = Snowflakes_list.begin();
	while(i != Snowflakes_list.end())
	{
		if (i->getypos() <= i->getymin())
			i = Snowflakes_list.erase(i);
		else
			i++;
	}

	for(auto& i : Snowflakes_list)
	{
		i.play(time);
	}
}

void Snow::display()
{
	list<Snowflake>::iterator i;
	i = Snowflakes_list.begin();

	glDepthMask(GL_FALSE);
	texture->define();

	// for(i = Snowflakes_list.begin(); i != Snowflakes_list.end(); i++)
	// {
	// 	i->display();
	// }

	for(auto& i : Snowflakes_list)
	{
		i.display();
	}

	glDepthMask(GL_TRUE);

	// Autre méthode avec un for auto& :

	// for(auto& i : Snowflakes_list)
	// {
	// 	i.display();
	// }
}

///////////////////////////////// END_SNOW /////////////////////////////////

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
	glPopMatrix();
}

GLvoid initGL()
{
	texture_sol.charger("neige.tga");
	texture_snow.charger("particule.png");

	glClearColor(0, 0, 0, 1);
  glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat Light0Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat Light0Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat Light0Spec[4]= {0.2, 0.2, 0.2, 1.0f};

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light0Spec);
	glLightfv(GL_LIGHT0, GL_POSITION, dir);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void affiche_sol()
{
	glEnable(GL_TEXTURE_2D);
	texture_sol.define();

	glBegin(GL_QUADS); // sol de 50 par 50
		glTexCoord2f(0.0f, 0.0f);
		glVertex3d(-25, 0, -25);
		glTexCoord2f(0.0f, 5.0f);
		glVertex3d(-25, 0,  25);
		glTexCoord2f(5.0f, 5.0f);
		glVertex3d( 25, 0,  25);
		glTexCoord2f(5.0f, 0.0f);
		glVertex3d( 25, 0, -25);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

Snow neige  = Snow(10, 9, -3.5, 0.08, &texture_snow);

void affiche_scene(float dt)
{
	affiche_lumiere();
	affiche_sol();

	neige.play(dt);
	neige.display();

	glutSwapBuffers();
}

float mesure_temps_ecoule()
{
	static long temps_precedent = -1;
	long temps_actuel;
	float dt = 0;

	temps_actuel = glutGet(GLUT_ELAPSED_TIME);

	if(temps_precedent == -1)
	{
		temps_precedent = glutGet(GLUT_ELAPSED_TIME);
		dt = 0;
	}
	else
	{
		dt = (float)(temps_actuel - temps_precedent) / 1000.0f;
		temps_precedent = temps_actuel;
	}

	return dt;

}

GLvoid callback_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	glLightfv(GL_LIGHT0, GL_POSITION, dir);

	float dt = mesure_temps_ecoule();

	affiche_scene(dt);
	glFlush();
}

GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}

GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}

GLvoid callback_motion(int x, int y)
{
	angle_x += y - mouse_y;
	angle_y += x - mouse_x;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

void timer(int v)
{
glutPostRedisplay();
glutTimerFunc(20, timer, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	glutTimerFunc(20, timer, 0);
	initGL();

	glutDisplayFunc(&callback_display);
	glutReshapeFunc(&callback_reshape);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutMainLoop();

	return 1;
}
