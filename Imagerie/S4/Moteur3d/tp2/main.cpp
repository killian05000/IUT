#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <random>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/GUIEventHandler>
#include <osg/Camera>

using namespace osg;
using namespace osgDB;
using namespace std;
using namespace osgGA;

ref_ptr<Group> scene = new Group;
ref_ptr<StateSet> sceneState = scene->getOrCreateStateSet();
ref_ptr<Switch> switchNode = new Switch;
osgViewer::Viewer viewer;
ref_ptr<Camera> cam1 = new Camera;
ref_ptr<Camera> cam2 = new Camera;
ref_ptr<Camera> cam3 = new Camera;
bool a=true;

Group *generate_flock(int nb_cow, float size_x, float size_y)
{
	ref_ptr<Group> flock = new Group;
	ref_ptr<LOD> lod = new LOD;
	lod->setRangeMode(LOD::DISTANCE_FROM_EYE_POINT);
	ref_ptr<Node> cow_low = readNodeFile("data/cow_low.3ds");
	ref_ptr<Node> cow_mid = readNodeFile("data/cow_mid.3ds");
	ref_ptr<Node> cow_high = readNodeFile("data/cow_high.3ds");
	lod->addChild(cow_high, 0, 10);
	lod->addChild(cow_mid, 10, 20);
	lod->addChild(cow_low, 20, 10000);

	for(int i=0; i< nb_cow; i++)
	{
		ref_ptr<PositionAttitudeTransform> transform = new PositionAttitudeTransform();

		random_device generator;
    uniform_int_distribution<int> distribution1(-size_x/2, size_x/2);
  	int x = distribution1(generator);

		uniform_int_distribution<int> distribution2(-size_y/2, size_y/2);
  	int y = distribution2(generator);

		uniform_real_distribution<float> distribution3(0.f, 360.f);
  	float r = distribution3(generator);

		transform->setPosition(Vec3(x,y,0));
		transform->setAttitude(Quat(DegreesToRadians(r), Vec3(0.f, 0.f, 1.0)));
		transform->setScale(Vec3(1, 1, 1));
		sceneState->setMode(GL_NORMALIZE, StateAttribute::ON); // pour normaliser et retrouver les effets de lumière

		transform->addChild(lod);
		flock->addChild(transform);
	}
	switchNode->addChild(flock);
	scene->addChild(switchNode);
}

Node* create_ground(float sizex, float sizey)
{
	ref_ptr<Texture2D> texture = new Texture2D;
	texture->setImage(readImageFile("data/herbe.jpg"));
	texture->setFilter(Texture::MIN_FILTER, Texture::LINEAR);
	texture->setFilter(Texture::MAG_FILTER, Texture::LINEAR);
	texture->setWrap(Texture::WRAP_S, Texture::REPEAT);
	texture->setWrap(Texture::WRAP_T, Texture::REPEAT);

	ref_ptr<Geometry> quad = createTexturedQuadGeometry(Vec3(-sizex/2, -sizey/2, 0.0), // coin de départ
																											Vec3(sizex, 0.0, 0.0),		 // largeur
																											Vec3(0.0, sizey, 0.0),		 // hauteur
																											0.0, 0.0, 1.0, 1.0);		 // coordonnées de texture gauche/bas/droit/haut

	quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
	quad->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, StateAttribute::ON);

	Geode* geode = new Geode;
	geode->addDrawable(quad);
	scene->addChild(geode);
}

class EventManager : public GUIEventHandler
{
	public:
		virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa);
};

bool EventManager::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
		case GUIEventAdapter::KEYDOWN:
			switch (ea.getKey())
			{
				case 'd':
					if(a)
					{
						switchNode->setAllChildrenOff();
						a=false;
					}
					else
					{
						switchNode->setAllChildrenOn();
						a=true;
					}
					break;

				case 'a':
					viewer.setCamera(cam1);
					break;
				case 'z':
					viewer.setCamera(cam2);
					break;
			}
			break;
	}
	return false;
}

int main()
{
	viewer.setUpViewInWindow(100, 50, 800, 600);
	viewer.addEventHandler(new osgViewer::StatsHandler); // s

	cam1->setClearColor(Vec4(0,0,0,1));
	cam1->setProjectionMatrixAsPerspective(30, 4.0/3.0, 0.1, 100);
	cam1->setViewMatrixAsLookAt(Vec3(0,-10,-10),
															Vec3(0,0,0),
															Vec3(0,0,1));

	cam2->setClearColor(Vec4(0,0,0,1));
	cam2->setProjectionMatrixAsPerspective(30, 4.0/3.0, 0.1, 100);
	cam2->setViewMatrixAsLookAt(Vec3(0,10,10),
															Vec3(0,0,0),
															Vec3(0,0,1));

	ref_ptr<EventManager> Emanager = new EventManager();
	viewer.addEventHandler(Emanager.get());

	generate_flock(100,30,30);
	create_ground(30,30);
	viewer.setSceneData(scene);
	return viewer.run();
}
