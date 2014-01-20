#include "Splash.h"
#include "mainmenu.h"
#include "game_basic.h"

USING_NS_CC;

Splash::Splash()
:m_pressAnyKey(NULL)
{
    CCSprite* pSplash = CCSprite::create("menu/splash.jpg");
    pSplash->setPosition(VisibleRect::center());
    addChild(pSplash, 0);
    
    m_pressAnyKey = CCLabelTTF::create("PRESS ANY KEY", "Arial", 24);
    m_pressAnyKey->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y + m_pressAnyKey->getContentSize().height * 2));
    addChild(m_pressAnyKey, 1);
    
    schedule(schedule_selector(Splash::updatePressAnyKey), 1.0f);
    
    setTouchEnabled(true);
}

Splash::~Splash()
{}

void Splash::updatePressAnyKey()
{
    m_pressAnyKey->setVisible(!m_pressAnyKey->isVisible());
}

void Splash::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    /*
    CCScene* pScene = CCScene::create();
    CCLayer* pLayer = new Mainmenu();
    pLayer->autorelease();
    
    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
    //*/
    
    CCScene* pNextScene = CCScene::create();
    CCLayer* pNextLayer = new Mainmenu();
    pNextLayer->autorelease();
    
    pNextScene->addChild(pNextLayer);
    
    CCScene* pTransitionScene = CCTransitionCrossFade::create(1.0f, pNextScene);
    
    if(pTransitionScene)
    {
        CCDirector::sharedDirector()->replaceScene(pTransitionScene);
    }
}
