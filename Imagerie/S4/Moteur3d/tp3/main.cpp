#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <random>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/GUIEventHandler>
#include <osg/Camera>
#include <osg/Fog>
#include <osgParticle/PrecipitationEffect>
#include <osg/LightSource>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osgShadow/SoftShadowMap>

using namespace osg;
using namespace osgDB;
using namespace std;
using namespace osgGA;

osgViewer::Viewer viewer;
ref_ptr<Group> scene = new Group;
ref_ptr<StateSet> sceneState = scene->getOrCreateStateSet();
ref_ptr<Switch> switchNode = new Switch;
ref_ptr<osgShadow::ShadowedScene> shadowScene= new osgShadow::ShadowedScene;
bool a=true;


Node* create_ground(float sizex, float sizey)
{
	ref_ptr<Texture2D> texture = new Texture2D;
	texture->setImage(readImageFile("data/snow.jpg"));
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

	ref_ptr<Geode> geode = new Geode;
	geode->addDrawable(quad);
	shadowScene->addChild(geode);
}


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
	shadowScene->addChild(switchNode);
}


void createFog()
{
	ref_ptr<Fog> pFog = new Fog();
	pFog->setMode(Fog::LINEAR); // EXP2 ou LINEAR
	pFog->setColor(Vec4(0.7, 0.7, 0.7, 1));
	//pFog->setDensity(0.05f); // pour EXP2
	pFog->setStart(10); // pour LINEAR
	pFog->setEnd(300); // pour LINEAR

	scene->getOrCreateStateSet()->setAttribute(pFog, StateAttribute::ON);
	scene->getOrCreateStateSet()->setMode(GL_FOG, StateAttribute::ON);
}


void generateParticles(char type, double xdir, double ydir, double zdir, double s, double number)
{
	ref_ptr<osgParticle::PrecipitationEffect> precipNode = new osgParticle::PrecipitationEffect();

	if (type =='r')
		precipNode->rain(number);
	else if (type =='s')
	 	precipNode->snow(number);
	else
		precipNode->snow(number);

	precipNode->setWind(Vec3(xdir,ydir,zdir));
	precipNode->setParticleSpeed(s);

	scene->addChild(precipNode.get());
}

void enableShadow(ref_ptr<LightSource> _light)
{
	//ref_ptr<osgShadow::ShadowMap> sMap = new osgShadow::ShadowMap;
	ref_ptr<osgShadow::SoftShadowMap> sMap = new osgShadow::SoftShadowMap;

	shadowScene->setShadowTechnique(sMap);
	shadowScene->addChild(_light);
	scene->addChild(shadowScene);
	viewer.setSceneData(shadowScene);

	float melange = 0.5;
	sMap->setAmbientBias (osg::Vec2(melange,1.0 - melange));

		//------------------------

		// ref_ptr<osgShadow::ShadowedScene> shadowScene= new osgShadow::ShadowedScene;
		// ref_ptr<osgShadow::SoftShadowMap> sm = new osgShadow::SoftShadowMap;
    //
		// shadowScene->setShadowTechnique(sm.get());
		// shadowScene->addChild(lumiere.get());
		// shadowScene->addChild(scene.get());
		// viewer.setSceneData(shadowScene);
}

void enableLight()
{
	sceneState->setMode(GL_LIGHT0, StateAttribute::OFF);

	ref_ptr<LightSource> light = new LightSource();
	light->getLight()->setLightNum(1); // GL_LGHT1
	light->getLight()->setPosition(Vec4(1, -1, 1, 0)); // 0 = directionnel 1 = ponctuelle
	light->getLight()->setAmbient(Vec4(0.2, 0.2, 0.2, 1.0));
	light->getLight()->setDiffuse(Vec4(1, 1, 1, 1.0));
	light->getLight()->setSpecular(Vec4(1.0, 1.0, 1.0, 1.0));

	sceneState->setMode(GL_LIGHT1, StateAttribute::ON);

	enableShadow(light);
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
			}
			break;
	}
	return false;
}

int main()
{
	viewer.setUpViewInWindow(100, 50, 800, 600);
	//viewer.getCamera()->setClearColor(osg::Vec4(0.7, 0.7, 0.7, 1));
	viewer.addEventHandler(new osgViewer::StatsHandler); // s

	ref_ptr<EventManager> Emanager = new EventManager();
	viewer.addEventHandler(Emanager.get());

	enableLight();
	generate_flock(100,30,30);
	create_ground(30,30);
	createFog();
	generateParticles('s', 0, 0, -1, 0.4, 0.3);

	viewer.setSceneData(scene);
	return viewer.run();
}
