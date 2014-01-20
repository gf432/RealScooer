#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Splash : public CCLayer
{
public:
    Splash();
    ~Splash();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
private:
    void updatePressAnyKey();
    CCLabelTTF* m_pressAnyKey;
};

#endif // __SPALSH_SCENE_H__
