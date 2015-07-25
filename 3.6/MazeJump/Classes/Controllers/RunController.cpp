//
//  RunController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "RunController.h"
USING_NS_CC;

RunController* g_pRunControllerInstance = nullptr;
RunController* RunController::getInstance()
{
    if( g_pRunControllerInstance == nullptr )
        g_pRunControllerInstance = new RunController();
    
    return g_pRunControllerInstance;
}
RunController::RunController()
{
    m_pMainLayer        = nullptr;
    m_pTerrainLayer     = nullptr;
    m_pMainCamera       = nullptr;
    m_pMainPlayer       = nullptr;
}
RunController::~RunController()
{
}
bool RunController::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    
    Skybox* m_pSkyBox = Skybox::create("sky4.png", "sky4.png", "sky4.png", "sky4.png", "sky4.png", "sky4.png");
    if(!m_pSkyBox)
        return false;
    m_pSkyBox->setScale(1000);
    m_pSkyBox->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pMainLayer->addChild(m_pSkyBox);
    
    m_pTerrainLayer = TerrainLayer::create();
    if(!m_pTerrainLayer)
        return false;
    m_pTerrainLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pTerrainLayer->setAnchorPoint(Vec2::ZERO);
    m_pMainLayer->addChild(m_pTerrainLayer);
    
    m_pMainPlayer = Runner::create();
    if(!m_pMainPlayer)
        return false;
    m_pMainPlayer->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pMainPlayer->setPositionY(4);
    m_pTerrainLayer->addChild(m_pMainPlayer);
    
    Sprite3D* cloud = Sprite3D::create("manycloud.c3b");
    if(!cloud)
        return false;
    cloud->setCameraMask((unsigned short)CameraFlag::USER1);
    cloud->setPositionZ(m_pMainPlayer->getPositionZ() -200);
    cloud->setPositionY(-80);
    cloud->setScaleX(2.5f);
    cloud->setScaleY(2.5f);
    cloud->setScaleZ(2.5f);
    
    m_pMainLayer->addChild(cloud);
    
    Sprite3D* cloud2 = Sprite3D::create("manycloud.c3b");
    if(!cloud2)
        return false;
    cloud2->setCameraMask((unsigned short)CameraFlag::USER1);
    cloud2->setPositionZ(m_pMainPlayer->getPositionZ() -400);
    cloud2->setPositionY(-80);
    cloud2->setScaleX(2.5f);
    cloud2->setScaleY(2.5f);
    cloud2->setScaleZ(2.5f);
    cloud2->setRotation3D(Vec3(0,180,0));
    m_pMainLayer->addChild(cloud2);
    
    auto size = Director::getInstance()->getVisibleSize();
    m_pMainCamera = Camera::createPerspective(60, size.width/size.height, 1, 5000);
    if(!m_pMainCamera)
        return false;
    Vec3 camPos = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,60.0f*cosf(M_PI/6.0f),60.0f*sinf(M_PI/6.0f));
    Vec3 lookAt = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,0,-30);
    m_pMainCamera->setPosition3D(camPos);
    m_pMainCamera->lookAt(lookAt);
    m_pMainLayer->addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(150, 150, 150));
    m_pMainLayer->addChild(ambLight);
    DirectionLight* directionLight = DirectionLight::create(Vec3(-3, -4, -2), Color3B(158, 158, 158));
    m_pMainLayer->addChild(directionLight);
    
    return true;
}
void RunController::update(float delta)
{
    if(m_pTerrainLayer)
        m_pTerrainLayer->update(delta);
}
void RunController::destroy()
{
    m_pMainLayer->removeAllChildren();
    m_pMainLayer = nullptr;
}
void RunController::cameraTrackPlayer()
{
    if(m_pMainPlayer && m_pMainCamera)
    {
        Vec3 camPos = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,60.0f*cosf(M_PI/6.0f),60.0f*sinf(M_PI/6.0f));;
        Vec3 targetLookAt = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,0,-30);
        EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.4f, camPos));
        m_pMainCamera->runAction(moveTo);
    }
}
void RunController::gameOver()
{
    CCLOG("gameOver");
}