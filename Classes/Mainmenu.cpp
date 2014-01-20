#include "Mainmenu.h"
#include "menu_define.h"
#include "game_basic.h"
#include "ShootPractice.h"

USING_NS_CC;

void Mainmenu::onEnter()
{
    CCLayer::onEnter();
    
    CCSprite* pBackground = CCSprite::create("menu/mainmenu.jpg");
    pBackground->setPosition(VisibleRect::center());
    addChild(pBackground, 0);
    
    m_pMainMenu = CCMenu::create();
    for(int i = 0; i < MAIN_MENU_SIZE; i ++)
    {
        CCLabelTTF* pLabel = CCLabelTTF::create(MAIN_MENU_ITEM[i].c_str(), "Arial", 24);
        CCMenuItemLabel* pItem = CCMenuItemLabel::create(pLabel, this, menu_selector(Mainmenu::menuCallback));
        m_pMainMenu->addChild(pItem, 1000 + i);
        pItem->setPosition( ccp( 0, (0 - (i + 1) * MENU_LINE_SPACE)));
    }
    
    m_pMainMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (MAIN_MENU_SIZE + 1) * (MENU_LINE_SPACE)));
    addChild(m_pMainMenu);
    
    setTouchEnabled(true);
}

void Mainmenu::menuCallback(CCObject * pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 1000;
    if(nIdx == 0)//Practice
    {
        CCScene* pNextScene = CCScene::create();
        CCLayer* pNextLayer = new ShootPractice();
        pNextLayer->autorelease();
        
        pNextScene->addChild(pNextLayer);
        
        CCScene* pTransitionScene = CCTransitionCrossFade::create(1.0f, pNextScene);
        
        if(pTransitionScene)
        {
            CCDirector::sharedDirector()->replaceScene(pTransitionScene);
        }
    }
}

