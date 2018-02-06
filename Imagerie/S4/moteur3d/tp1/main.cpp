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

osg::Group* scene = new osg::Group;
osg::StateSet* state = scene->getOrCreateStateSet();

class EventManager : public osgGA::GUIEventHandler
{
    public:
        virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};

bool EventManager::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    switch(ea.getEventType())
    {
        
        case osgGA::GUIEventAdapter::KEYDOWN: // appui sur une touche
           switch(ea.getKey())
           {
                case 'a':
                    if(state->getMode(1) == osg::StateSetteAttribute::ON)
                        state->setMode( GL_LIGHT1, osg::StateAttribute::OFF);
                    else
                        state->setMode( GL_LIGHT1, osg::StateAttribute::ON);
                    break;
                case 'z':
                    if(state->getMode(2) == osg::StateAttribute::ON)
                        state->setMode( GL_LIGHT2, osg::StateAttribute::OFF);
                    else
                        state->setMode( GL_LIGHT2, osg::StateAttribute::ON);
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
    return false;
}

int main ()
{
    osg::DisplaySettings::instance()->setNumMultiSamples( 4 );

    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(100, 50, 800, 600);
    //viewer.getCamera()->setClearColor(osg::Vec4(1,1,1,1));
    state->setMode( GL_LIGHT0, osg::StateAttribute::OFF );

    //Lumière
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


    //Cube
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
    boxTransform->setPosition(osg::Vec3(-2, 2, 0));
    boxTransform->setScale(osg::Vec3(1, 1, 1));
    boxTransform->setAttitude(osg::Quat(osg::DegreesToRadians(20.0), osg::Vec3(0.0, 0.0, 1.0)));
    boxTransform->addChild(boxGeode);

    //Sphere
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
    sphereTransform->setPosition(osg::Vec3(0, 0, 0));
    sphereTransform->setScale(osg::Vec3(1, 1, 1));
    sphereTransform->setAttitude(osg::Quat(osg::DegreesToRadians(20.0), osg::Vec3(0.0, 0.0, 1.0)));
    sphereTransform->addChild(sphereGeode);

    //Cone
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
    coneTransform->setPosition(osg::Vec3(0, 0, 0));
    coneTransform->setScale(osg::Vec3(1, 1, 1));
    coneTransform->setAttitude(osg::Quat(osg::DegreesToRadians(20.0), osg::Vec3(0.0, 0.0, 1.0)));
    coneTransform->addChild(coneGeode);


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
