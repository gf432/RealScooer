#ifndef __SHOOTPRACTICE_SCENE_H__
#define __SHOOTPRACTICE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Ball;
class Goal;
class ShootPractice: public CCLayer
{
public:
    ShootPractice();
    virtual ~ShootPractice();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float dt);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void reset();
    
    void resetCallback(CCObject* pSender);
    
private:
    Ball* m_ball;
    Goal* m_goal;
    CCLabelTTF* m_debugLabel;
};

#endif // __SHOOTPRACTICE_SCENE_H__
