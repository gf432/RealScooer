//
//  Ball.h
//  RealSoccer
//
//  Created by ck02-216 on 1/8/14.
//
//

#ifndef __RealSoccer__Ball__
#define __RealSoccer__Ball__

#include "cocos2d.h"
#include "Actor.h"

typedef enum tagBallCollisionFlag
{
    kBallCollisionNone,
    kBallCollisionLeftPost,
    kBallCollisionRightPost,
    kBallCollisionCrossbar,
    kBallCollisionSideNet,
    kBallCollisionBackNet,
    kBallCollisionGK
}BallCollisionFlag;

USING_NS_CC;

typedef enum tagBallState
{
    kBallStateIdle,
    kBallStateAim,
    kBallStateMoveInAir,
    kBallStateMoveOnGround,
} BallState;

class Ball : public Actor, public CCTargetedTouchDelegate
{
    BallState m_state;
    
public:
    Ball();
    virtual ~Ball();
    
    bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    virtual void draw();
    
    void drawBallIndicator();
    
    CCRect rect();
    CCRect touchRect();
    bool containsTouchLocation(CCTouch* touch);
    float getRadius() {return m_ballRadius;}
    
    BallCollisionFlag getLastCollisionFlag() {return m_lastCollisionFlag;}
    void setLastCollisionFlag(BallCollisionFlag flag) {m_lastCollisionFlag = flag;}
    
    void setState(BallState state);
    
    void reset();
    
    virtual void update(float dt);
    
    static Ball* create();
    
    CCPoint m_debugMovePoint;
private:
    CCAnimation* m_ballAnimRoll;
    CCSprite* m_ballSpr;
    CCPoint m_touchPoint;
    CCPoint m_indicatorPoint;
    CCRect m_rect;
    CCRect m_touchRect;
    
    CCLabelTTF* m_debugLabel;
    
    float m_ballRadius;
    
    BallCollisionFlag m_lastCollisionFlag;
};

#endif /* defined(__RealSoccer__Ball__) */
