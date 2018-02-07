// g++ -o main.exe main.cpp -losg -losgDB -losgViewer -losgGA

#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg//Material>
#include <osg/PositionAttitudeTransform>
#include <osgGA/NodeTrackerManipulator>
#include <osg/LightSource>
#include <osgGA/GUIEventHandler>
#include <osgViewer/ViewerEventHandlers>
#include <iostream>

using namespace osg;
using namespace std;

osg::Group* scene = new osg::Group;
osg::StateSet* state = scene->getOrCreateStateSet();

///////////////////// SEARCH_NODE /////////////////////

class SearchNode : public NodeVisitor
{
    public:
        SearchNode(const string& _name)
            :NodeVisitor(NodeVisitor::TRAVERSE_ALL_CHILDREN), name(_name) {}

        virtual void apply(Node& _node)
        {
            if(_node.getName() == name)
                node = &_node;

            traverse(_node);
        }

        Node * getNode() {return node;}

    protected:
        string name;
        Node * node;
};

///////////////////// SEARCH_NODE /////////////////////

//////////////////// EVENT_MANAGER //////////////////// 

class EventManager : public osgGA::GUIEventHandler
{
    public:
        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

    private :
    string name;
};

bool EventManager::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    Vec3f dir = Vec3d{0,0,0};
    static Node* n = nullptr;

    switch(ea.getEventType())
    {
        
        case osgGA::GUIEventAdapter::KEYDOWN: // appui sur une touche
           switch(ea.getKey())
           {
                case 'a':
                    std::cout << "BBBBB" << std::endl;
                    if(state->getMode(GL_LIGHT1) == osg::StateAttribute::ON)
                        state->setMode( GL_LIGHT1, osg::StateAttribute::OFF);
                    else
                        state->setMode( GL_LIGHT1, osg::StateAttribute::ON);
                    break;
                case 'z':
                    if(state->getMode(GL_LIGHT2) == osg::StateAttribute::ON)
                        state->setMode( GL_LIGHT2, osg::StateAttribute::OFF);
                    else
                        state->setMode( GL_LIGHT2, osg::StateAttribute::ON);
                    break;

                case 's': {
                    SearchNode search("sphereT");
                    scene->accept(search);
                    n = search.getNode();
                    break;
                }

                case 'b': {
                    SearchNode search("boxT");
                    scene->accept(search);
                    n = search.getNode();
                    break;
                }

                case 'c': {
                    SearchNode search("coneT");
                    scene->accept(search);
                    n = search.getNode();
                    break;
                }

                case osgGA::GUIEventAdapter::KEY_Up:
                    dir[2]+=1;
                    if (n != nullptr)
                    {
                        Vec3f pos = n->asTransform()->asPositionAttitudeTransform()->getPosition();
                        n->asTransform()->asPositionAttitudeTransform()->setPosition(pos + dir);
                    }
                    break;

                case osgGA::GUIEventAdapter::KEY_Down:
                    dir[2]-=1;
                    if (n != nullptr)
                    {
                        Vec3f pos = n->asTransform()->asPositionAttitudeTransform()->getPosition();
                        n->asTransform()->asPositionAttitudeTransform()->setPosition(pos + dir);
                    }
                    break;

                case osgGA::GUIEventAdapter::KEY_Left:
                    dir[0]-=1;
                    if (n != nullptr)
                    {
                        Vec3f pos = n->asTransform()->asPositionAttitudeTransform()->getPosition();
                        n->asTransform()->asPositionAttitudeTransform()->setPosition(pos + dir);
                    }
                    break;

                case osgGA::GUIEventAdapter::KEY_Right:
                    dir[0]+=1;
                    if (n != nullptr)
                    {
                        Vec3f pos = n->asTransform()->asPositionAttitudeTransform()->getPosition();
                        n->asTransform()->asPositionAttitudeTransform()->setPosition(pos + dir);
                    }
                    break;

                case 'p':
                    dir[1]+=1;
                    if (n != nullptr)
                    {
                        Vec3f pos = n->asTransform()->asPositionAttitudeTransform()->getPosition();
                        n->asTransform()->asPositionAttitudeTransform()->setPosition(pos + dir);
                    }
                    break;

                case 'm':
                    dir[1]-=1;
                    if (n != nullptr)
                    {
                        Vec3f pos = n->asTransform()->asPositionAttitudeTransform()->getPosition();
                        n->asTransform()->asPositionAttitudeTransform()->setPosition(pos + dir);
                    }
                    break;
            }
            break;
    }

    return false;
}

//////////////////// EVENT_MANAGER ////////////////////



int main ()
{
    osg::DisplaySettings::instance()->setNumMultiSamples( 4 );

    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(100, 50, 800, 600);
    viewer.getCamera()->setClearColor(osg::Vec4(1,1,1,1));
    state->setMode( GL_LIGHT0, osg::StateAttribute::OFF );

    //////////////////// LIGHTS ////////////////////

    osg::LightSource* light1 = new osg::LightSource;
    light1->getLight()->setLightNum(1);    // GL_LIGHT1
    light1->getLight()->setPosition(osg::Vec4(1,-1, 1,0));    // 0 = directionnel
    light1->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
    light1->getLight()->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
    light1->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
    state->setMode( GL_LIGHT1, osg::StateAttribute::ON );

    osg::LightSource* light2 = new osg::LightSource;
    light2->getLight()->setLightNum(2);    // GL_LIGHT1
    light2->getLight()->setPosition(osg::Vec4(1,-1, 1,1));    // 1 = ponctuelle
    light2->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
    light2->getLight()->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
    light2->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
    state->setMode( GL_LIGHT2, osg::StateAttribute::ON );

    osg::LightSource* lights = new osg::LightSource;
    lights->addChild(light1);
    lights->addChild(light2);

    //////////////////// LIGHTS ////////////////////


    ///////////////////// CUBE /////////////////////

    osg::Box* box = new osg::Box(osg::Vec3(0,0,0),2,3,4);
    osg::ShapeDrawable* boxDrawable = new osg::ShapeDrawable(box);
    osg::Material* boxMaterial = new osg::Material;
    boxMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.0, 0.0, 1.0));
    boxMaterial->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.0, 0.0, 1.0));
    boxMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
    boxMaterial->setShininess(osg::Material::FRONT_AND_BACK, 64);
    boxDrawable->getOrCreateStateSet()->setAttributeAndModes(boxMaterial);
    osg::Geode* boxGeode = new osg::Geode();
    boxGeode->addDrawable(boxDrawable);

    osg::PositionAttitudeTransform* boxTransform = new osg::PositionAttitudeTransform();
    boxTransform->setName("boxT");
    boxTransform->setPosition(osg::Vec3(-2, 2, 0));
    boxTransform->setScale(osg::Vec3(1, 1, 1));
    boxTransform->setAttitude(osg::Quat(osg::DegreesToRadians(20.0), osg::Vec3(0.0, 0.0, 1.0)));
    boxTransform->addChild(boxGeode);

    ///////////////////// CUBE /////////////////////

    //////////////////// SPHERE ////////////////////

    osg::Sphere* sphere = new osg::Sphere(osg::Vec3(3,0,0),1.0);
    osg::ShapeDrawable* sphereDrawable = new osg::ShapeDrawable(sphere);
    osg::Material* sphereMaterial = new osg::Material;
    sphereMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1, 1, 0.0, 1.0));
    sphereMaterial->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(1, 1, 0.0, 1.0));
    sphereMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
    sphereMaterial->setShininess(osg::Material::FRONT_AND_BACK, 64);
    sphereDrawable->getOrCreateStateSet()->setAttributeAndModes(sphereMaterial);
    osg::Geode* sphereGeode = new osg::Geode();
    sphereGeode->addDrawable(sphereDrawable);

    osg::PositionAttitudeTransform* sphereTransform = new osg::PositionAttitudeTransform();
    sphereTransform->setName("sphereT");
    sphereTransform->setPosition(osg::Vec3(0, 0, 0));
    sphereTransform->setScale(osg::Vec3(1, 1, 1));
    sphereTransform->setAttitude(osg::Quat(osg::DegreesToRadians(20.0), osg::Vec3(0.0, 0.0, 1.0)));
    sphereTransform->addChild(sphereGeode);

    //////////////////// SPHERE ////////////////////

    ///////////////////// CONE /////////////////////

    osg::Cone* cone = new osg::Cone(osg::Vec3(3,0,1.2),1,2);
    osg::ShapeDrawable* coneDrawable = new osg::ShapeDrawable(cone);
    osg::Material* coneMaterial = new osg::Material;
    coneMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1, 0.0, 1, 1.0));
    coneMaterial->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.0, 0.5, 1.0));
    coneMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
    coneMaterial->setShininess(osg::Material::FRONT_AND_BACK, 64);
    coneDrawable->getOrCreateStateSet()->setAttributeAndModes(coneMaterial);
    osg::Geode* coneGeode = new osg::Geode();
    coneGeode->addDrawable(coneDrawable);

    osg::PositionAttitudeTransform* coneTransform = new osg::PositionAttitudeTransform();
    coneTransform->setName("coneT");
    coneTransform->setPosition(osg::Vec3(0, 0, 0));
    coneTransform->setScale(osg::Vec3(1, 1, 1));
    coneTransform->setAttitude(osg::Quat(osg::DegreesToRadians(20.0), osg::Vec3(0.0, 0.0, 1.0)));
    coneTransform->addChild(coneGeode);

    ///////////////////// CONE ////////////////////


    osgGA::NodeTrackerManipulator* manip = new osgGA::NodeTrackerManipulator;
    manip->setTrackNode(coneGeode);
    manip->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER);
    viewer.setCameraManipulator(manip);

    EventManager* gestionnaire = new EventManager();
    viewer.addEventHandler(gestionnaire);

    scene->addChild(lights);
    scene->addChild(boxTransform);
        //boxTransform->addChild(boxGeode);
    scene->addChild(sphereTransform);
        //sphereTransform->addChild(sphereGeode);
    scene->addChild(coneTransform);
        //coneTransform->addChild(coneGeode);
    viewer.setSceneData(scene);
    return viewer.run();
}
