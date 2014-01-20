#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Mainmenu : public cocos2d::CCLayer
{
public:
    virtual void onEnter();
    
    void menuCallback(CCObject * pSender);
    
private:
    CCMenu* m_pMainMenu;
};

#endif // __MAINMENU_SCENE_H__
