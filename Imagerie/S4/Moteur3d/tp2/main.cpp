// g++ -o main.exe main.cpp -losg -losgDB -losgViewer -losgGA

#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <random>
#include <osg/PositionAttitudeTransform>

using namespace osg;
using namespace osgDB;
using namespace std;

ref_ptr<Group> scene = new Group;
ref_ptr<StateSet> sceneState = scene->getOrCreateStateSet();

Group *generate_flock(int nb_cow, float size_x, float size_y)
{
	ref_ptr<Group> flock = new Group;

	for(int i=0; i< nb_cow; i++)
	{
		ref_ptr<PositionAttitudeTransform> transform = new PositionAttitudeTransform();
		ref_ptr<Node> cow = readNodeFile("data/cow_low.3ds");

		random_device generator;
    uniform_int_distribution<int> distribution1(0, size_x);
  	int x = distribution1(generator);

		uniform_int_distribution<int> distribution2(0, size_y);
  	int y = distribution2(generator);

		uniform_real_distribution<float> distribution3(0.f, 360.f);
  	float r = distribution3(generator);

		transform->setPosition(Vec3(x,y,0));
		transform->setAttitude(Quat(DegreesToRadians(r), Vec3(0.f, 0.f, 1.0)));
		transform->setScale(Vec3(1, 1, 1));
		sceneState->setMode(GL_NORMALIZE, StateAttribute::ON); // pour normaliser et retrouver les effets de lumière

		transform->addChild(cow);
		flock->addChild(transform);
	}
	scene->addChild(flock);
}

int main()
{
	osgViewer::Viewer viewer;
	viewer.setUpViewInWindow(100, 50, 800, 600);

	generate_flock(100,30,30);
	// Node* cow = readNodeFile("data/cow_high.3ds");
  //
	// scene->addChild(cow);
	viewer.setSceneData(scene);
	return viewer.run();
}
